export const meta = {
  name: 'g1-app-fable-unproven',
  description: 'Fable agents reconstruct+prove the substantial unproven app-core functions',
  phases: [{ title: 'app-fable', detail: '49 Fable agents: 31 solo big funcs + 18 mid pairs' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const BASE = '/Users/freedomcoder/Projects/G1disasm2'
const NB = 49
function prompt(i) {
  return `Reconstruct C for app-core function(s) of the Even G1 firmware (nRF5340 app core, NCS 2.5.1) and PROVE each byte-identical via the differential-emulation harness. Do the work yourself; do NOT spawn sub-agents; do NOT edit anything under tools/.

export RECON_LEDGER=${SCR}/app_fable_ledger_${i}.json

Your batch = element ${i} of ${SCR}/app_fable_batches.json — a list of {addr, name, ghidra_size, code_hint, inflated}. Read it:
  PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python -c "import json;print(json.dumps(json.load(open('${SCR}/app_fable_batches.json'))[${i}],indent=1))"

CRITICAL — these functions FAILED earlier because Ghidra's size often INCLUDES A TRAILING DATA TABLE folded into the function. \`inflated:true\` means only ~\`code_hint\` bytes are reachable code (via simple control-flow) and the rest (up to ghidra_size) is DATA — e.g. ble_process_put_req is ~242B code + 25KB data table. NOTE: code_hint is a LOWER bound — if the function has a jump table (tbb/tbh), real code extends past code_hint into switch cases, so verify by disassembly; do not blindly truncate at code_hint.

Method (app core uses recon_kit, NOT net_recon_kit):
1. Inspect: PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python tools/recon_kit.py info 0xADDR  (name, callees, decomp, annotated disasm).
2. DETERMINE THE TRUE CODE EXTENT: trace control flow from the entry — follow branches, resolve every tbb/tbh/ldr-pc jump table (read table bytes with tools/extract.py: extract.read/read_u32, decode all case targets), and find where executable code ends and the data table begins (garbage/ascii/pointer words that no path reaches). The true code size = end of the last reachable instruction.
3. Write faithful C for the CODE ONLY (globals as fixed absolute-address volatile pointers using literal VALUES, width/signedness matched; callees as extern oracles in the same order; reproduce every switch case; keep exact loop termination). The trailing data table is NOT code — reference it as an extern if the code reads it.
4. Prove at the TRUE CODE SIZE (not ghidra_size):
   PYTHONSAFEPATH=1 RECON_LEDGER=$RECON_LEDGER ${BASE}/.venv/bin/python -c '
   import sys; sys.path.insert(0,"${BASE}/tools")
   import recon_kit
   src = r"""<C source>"""
   print(recon_kit.prove(0xADDR, TRUE_CODE_SIZE, "NAME", src, nptr=NPTR, trials=300))'
   - pass:True auto-saves recon/verified/src/NAME.c. checked>0 few mismatches = bisect. checked==0 = never returns (kit auto-retries no_return). Use the info name as NAME. Up to ~12 iterations.
5. If \`inflated\`, ALSO emit the trailing data table (bytes from true_code_end..ghidra_size) as a byte-exact rodata C file to ${BASE}/recon/data/rodata_0x<datastart>.c: read via extract.read, emit a const uint8_t[] whose initializer reproduces the bytes EXACTLY, comment it with the owning function. (This recovers the ~data that was hiding the function.)
6. If a proof TIMES OUT (pathological data-dependent loop), do prove(...trials=1); if it passes, report VERIFIED-ON-VALID-INPUT and note "full-fuzz impractical". If still mismatching after real effort, report UNPROVEN with the structural blocker.

Report per address: true_code_size found, PROVEN(trials)/VERIFIED-ON-VALID-INPUT/UNPROVEN(reason), and data-table bytes split off if any.`
}
phase('app-fable')
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`app-fable: ${todo.length} batches over the substantial unproven functions`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `appfab:${i}`, phase: 'app-fable', agentType: 'general-purpose', model: 'fable' })))
log(`app-fable complete: ${results.filter(Boolean).length}/${results.length}`)
return { agents: results.length, returned: results.filter(Boolean).length }
