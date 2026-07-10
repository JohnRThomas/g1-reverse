export const meta = {
  name: 'g1-net-fable2-inflated',
  description: 'Fable agents: net-core unproven funcs with data-inflation-aware reconstruction',
  phases: [{ title: 'net-fable2', detail: '4 Fable agents, inflation-aware code/data split' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const BASE = '/Users/freedomcoder/Projects/G1disasm2'
const NB = 4
function prompt(i) {
  return `Read ${BASE}/tools/NET_PLAYBOOK.md, then reconstruct+prove ONE net-core function (nRF5340 CPUNET, NCS 2.5.1). Do the work yourself; do NOT spawn sub-agents; do NOT edit tools/.

export RECON_LEDGER=${SCR}/net_fable2_ledger_${i}.json

Your batch = element ${i} of ${SCR}/net_fable2_batches.json — {addr,name,ghidra_size,code_hint,inflated}:
  PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python -c "import json;print(json.dumps(json.load(open('${SCR}/net_fable2_batches.json'))[${i}][0],indent=1))"

CRITICAL — if \`inflated:true\`, Ghidra's size INCLUDES A TRAILING DATA TABLE folded into the function: only ~\`code_hint\` bytes are reachable code, the rest is DATA. code_hint is a LOWER bound (jump tables extend real code past it into switch cases) — verify by disassembly, don't blindly truncate.

Use net_recon_kit (NOT recon_kit). Net image base 0x01008000; bytes via net_extract (extract.read/read_u32).
1. Inspect: PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python tools/net_recon_kit.py info 0xADDR
2. Find the TRUE code extent: trace control flow from entry, resolve every tbb/tbh/ldr-pc jump table (read table bytes from the image, decode all case targets), find where code ends and the data table begins.
3. Write faithful C for the CODE ONLY (globals as fixed absolute-address volatile pointers using literal VALUES; callees extern in same order; reproduce every switch case; exact loop termination).
4. Prove at the TRUE CODE SIZE:
   PYTHONSAFEPATH=1 RECON_LEDGER=$RECON_LEDGER ${BASE}/.venv/bin/python -c '
   import sys; sys.path.insert(0,"${BASE}/tools")
   import net_recon_kit
   src = r"""<C source>"""
   print(net_recon_kit.prove(0xADDR, TRUE_CODE_SIZE, "NAME", src, nptr=NPTR, trials=300))'
   pass:True saves recon/net/src/NAME.c. checked==0 -> auto no_return retry. Up to ~12 iterations.
5. If inflated, emit the trailing data table (true_code_end..ghidra_size) as a byte-exact rodata C file to ${BASE}/recon/net/data/rodata_0x<datastart>.c (create dir if needed): const uint8_t[] reproducing extract.read bytes EXACTLY, commented with the owning function.
6. If proof times out (pathological loop): prove trials=1; if it passes report VERIFIED-ON-VALID-INPUT. Else UNPROVEN with the structural blocker.

Report: true_code_size, PROVEN(trials)/VERIFIED-ON-VALID-INPUT/UNPROVEN(reason), data bytes split.`
}
phase('net-fable2')
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`net-fable2: ${todo.length} inflation-aware net functions`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `netf2:${i}`, phase: 'net-fable2', agentType: 'general-purpose', model: 'fable' })))
log(`net-fable2 complete: ${results.filter(Boolean).length}/${results.length}`)
return { agents: results.length, returned: results.filter(Boolean).length }
