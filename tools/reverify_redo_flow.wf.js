export const meta = {
  name: 'g1-reverify-redo',
  description: 'Agents re-verify proven funcs with the fixed harness and redo the false proofs',
  phases: [{ title: 'reverify-redo', detail: '28 agents: batch re-verify + reconstruct any false proofs' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const BASE = '/Users/freedomcoder/Projects/G1disasm2'
function prompt(i) {
  return `You re-verify reconstructed Even G1 firmware functions against the FIXED parity harness and REDO any that are now false proofs. Do the work yourself; do NOT spawn sub-agents; do NOT edit tools/.

Background: the harness's make_args was just fixed to seed small/boundary argument values. Functions that dispatch on a small-range arg (switch/enum/opcode/flag) were previously "proven" without their real cases ever being tested — some reconstructions are wrong on those cases. Your job: find which of your batch are now-failing, and reconstruct them correctly.

Env: PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python ; workdir ${BASE}.

STEP 1 — re-verify your batch (this runs the fixed harness on each saved reconstruction):
  PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python tools/reverify.py batch ${i}
It prints "<name> PASS/FAIL" per function and a final "FAILS(n): core:name core:name ...". PASS = the proof holds, leave it. FAIL = false proof, redo it.

STEP 2 — for each FAIL (format core:name), get its address from ${SCR}/reverify_agent_batches.json[${i}] (match name -> addr,core), then reconstruct CORRECTLY:
  - app core: use recon_kit ; net core: use net_recon_kit (base 0x01008000).
  - Inspect from /tmp: PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python ${BASE}/tools/<kit>.py info 0xADDR. The kit emits readable aliases and their raw/address back-map; use known readable callees in bodies but retain catalog NAME as proof identity.
  - The bug is almost always in SWITCH/DISPATCH handling: find the tbb/tbh/ldr-pc jump table or the cmp-arg,#k branches. Read the jump-table bytes from the image (extract.read/read_u32 or net_extract), decode EVERY case target, and reproduce every case's logic exactly — not just the default path. Match globals (absolute-address volatile ptrs, literal values), callee order, masks, signedness.
  - Prove (the fixed harness now exercises the cases):
    PYTHONSAFEPATH=1 RECON_LEDGER=${SCR}/redo_ledger_${i}.json ${BASE}/.venv/bin/python -c '
    import sys; sys.path.insert(0,"${BASE}/tools")
    import recon_kit   # or net_recon_kit
    src = r"""<C source>"""
    print(recon_kit.prove(0xADDR, SIZE, "NAME", src, nptr=NPTR, trials=300))'
  - pass:True overwrites the false proof with the correct one (auto-saves). Iterate up to ~12 times per function.
  - If a function's real code is huge/data-inflated or a pathological loop, and you cannot get a clean pass, report it UNPROVEN with the reason (it will be handled separately) — do NOT leave a knowingly-wrong reconstruction in place; note it clearly.

Report: batch total, PASS count, FAIL count, and per redone function: FIXED(trials) or STILL-UNPROVEN(reason).`
}
phase('reverify-redo')
const NB = 28
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`reverify-redo: ${todo.length} batches`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `rvredo:${i}`, phase: 'reverify-redo', agentType: 'general-purpose', model: 'sonnet' })))
log(`reverify-redo complete: ${results.filter(Boolean).length}/${results.length}`)
return { agents: results.length, returned: results.filter(Boolean).length }
