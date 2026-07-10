export const meta = {
  name: 'g1-net-fable-tail',
  description: 'Fable agents crack the last net-core hard functions, one per agent',
  phases: [{ title: 'net-fable', detail: '5 Fable agents, 1 large net-core function each' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const NB = 5
function prompt(i) {
  return `Read /Users/freedomcoder/Projects/G1disasm2/tools/NET_PLAYBOOK.md and follow it. Do the work yourself; do NOT spawn sub-agents; do NOT edit anything under tools/.

export RECON_LEDGER=${SCR}/net_fable_ledger_${i}.json

Your batch = element ${i} of ${SCR}/net_fable_batches.json (a SINGLE function — give it your full attention):
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python -c "import json;print(json.load(open('${SCR}/net_fable_batches.json'))[${i}][0])"

This is one of the 5 HARDEST remaining net-core functions (508-1054 bytes) — prior Opus and Sonnet passes could not reach bit-exact parity. It is almost certainly a jump-table dispatcher, a callee-dependent loop, or a packet-parser state machine. Techniques:
- Dump the FULL annotated disasm (net_recon_kit info 0xADDR). Find every tbb/tbh [pc,rN] or ldr pc,[pc,...] — read the switch table bytes straight from the image (net_extract.read/read_u32) and reproduce EVERY case with its exact target and fallthrough.
- Callees are identical oracles: mirror call order exactly; never simplify loop termination that depends on a callee return.
- Preserve every field offset, mask width (ldrb/ldrh/ldr), and signedness; globals = fixed absolute-address volatile pointers using the literal VALUE in the disasm annotations.
- If prove() shows checked>0 with a few mismatches, bisect: shrink trials, find which seed/branch diverges, fix that branch only. If checked==0 it never returns — trust the kit's no_return retry.
- You have a large budget for this ONE function: iterate up to ~15 times. Only then mark UNPROVEN with a precise structural reason.

Use net_recon_kit (not recon_kit). Report: the address, PROVEN or UNPROVEN, and if unproven the exact structural blocker.`
}
phase('net-fable')
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`net-fable: ${todo.length} hardest functions, 1 per agent`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `netfab:${i}`, phase: 'net-fable', agentType: 'general-purpose', model: 'fable' })))
const ok = results.filter(Boolean).length
log(`net-fable complete: ${ok}/${results.length} agents returned`)
return { agents: results.length, returned: ok }
