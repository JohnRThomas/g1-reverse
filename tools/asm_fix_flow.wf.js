export const meta = {
  name: 'g1-asm-typefix',
  description: 'Sonnet agents fix the last non-compiling symbolized sources (type reconciliation)',
  phases: [{ title: 'typefix', detail: '6 agents, ~6 files each, make them compile without changing semantics' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const BASE = '/Users/freedomcoder/Projects/G1disasm2'
const CC = '/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc'

function prompt(i) {
  return `You fix reconstructed+symbolized C sources of the Even G1 firmware so they COMPILE, WITHOUT changing behavior. These files are already parity-proven byte-exact; your edits must be semantics-preserving (retype, revert bad substitutions, add typedefs) — NEVER change logic. Do the work yourself; do NOT spawn sub-agents.

Env: workdir ${BASE}. Compile check (must return exit 0 with no error):
  ${CC} -c -Os -mcpu=cortex-m33 -mthumb -ffreestanding -w -I recon/symbols <file> -o /tmp/chk.o

Your batch = element ${i} of ${SCR}/asm_fix_batches.json — a list of {file, err}. Read it:
  PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python -c "import json;print(json.dumps(json.load(open('${SCR}/asm_fix_batches.json'))[${i}],indent=1))"

For each file, compile it, read the error, and fix by the pattern:
1. "invalid operands to binary &/-///+" with a 'char *' operand: the symbolizer WRONGLY replaced a numeric address with a STRING literal. Each substitution carries its original value in a trailing /*=0xADDR*/ comment. Revert that ONE token from the string literal back to the numeric 0xADDR (keep the /*=..*/), because here the address is used as a number, not a string. Only revert the token(s) involved in the arithmetic.
2. "expected '=', ',', ';' ... before '.' token" or "before '->'": a global was substituted as ((uintptr_t)&sym) but the code accesses a member (.field / ->field). Retype so member access works: cast the address to the right struct pointer at the use site, or change the extern's type. Use the /*=0xADDR*/ to identify it. Prefer a local cast like ((struct foo *)(uintptr_t)&sym)->field that preserves the exact access.
3. "unknown type name 'X'": add a local 'typedef uint32_t X;' (or the width the code implies) at the top, OR normalize X to the stdint type. Do not shadow stdint names.
4. "conflicting types": a local typedef or extern prototype disagrees with the header — drop the redundant local declaration (the header's wins) if identical, else reconcile the type.
5. If the file is a LIBRARY function (e.g. _vfprintf_r, dtoa, __*, newlib/Zephyr internals) that slipped into the set: do NOT try to make it build; instead move it to ${BASE}/recon/symbolized/_excluded_lib/ (create dir) and note it — it is provided by newlib/Zephyr, not reconstructed.

After each fix, re-run the compile check and confirm exit 0. Keep the /*=0xADDR*/ provenance comments intact. Do not touch recon/verified or tools.

Report: per file — FIXED (what you changed in one phrase) or EXCLUDED-LIBRARY or STILL-FAILING (exact remaining error).`
}
phase('typefix')
const NB = 6
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`asm typefix: ${todo.length} batches`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `typefix:${i}`, phase: 'typefix', agentType: 'general-purpose', model: 'sonnet' })))
log(`asm typefix complete: ${results.filter(Boolean).length}/${results.length}`)
return { agents: results.length, returned: results.filter(Boolean).length }
