export const meta = {
  name: 'g1-net-opus-tail',
  description: 'Opus agents crack the net-core hard-tail (large jump-table/dispatcher functions)',
  phases: [{ title: 'net-opus', detail: '8 Opus agents, 3 large net-core functions each' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const NB = 5
function prompt(i) {
  return `Read /Users/freedomcoder/Projects/G1disasm2/tools/NET_PLAYBOOK.md and follow it. Do the work yourself; do NOT spawn sub-agents; do NOT edit anything under tools/.

export RECON_LEDGER=${SCR}/net_opus_ledger_${i}.json

Your batch = element ${i} of ${SCR}/net_opus_batches.json:
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python -c "import json;print(' '.join(json.load(open('${SCR}/net_opus_batches.json'))[${i}]))"

These are the HARD TAIL — the 3 largest still-unproven net-core functions (340–5332 bytes). Prior Sonnet passes could not reach bit-exact parity on them. Spend real effort per function; you have a large budget. Techniques for these specific failure modes:

- **Jump-table / switch dispatch**: a \`tbb/tbh [pc, rN]\` or \`ldr pc,[pc,rN,lsl#2]\` means a switch. Read the table bytes from the image (net_extract.read / read_u32) right after the branch, decode every case target, and reproduce the switch in C with the SAME case values and fallthrough. The harness seeds r0-r3; make sure every reachable case is expressible.
- **Callee-dependent loops**: loops whose trip count comes from a callee return. Callees are modeled as identical oracles, so mirror the call order exactly and keep the loop structure; do not "simplify" the termination.
- **Large state machines / packet parsers**: preserve every field offset, mask width (ldrb/ldrh/ldr), and signedness exactly; globals = fixed absolute-address volatile pointers using the literal VALUE shown in the annotated disasm.
- If \`prove\` returns checked>0 with mismatches, the logic differs on some seed — narrow by shrinking trials and inspecting which branch diverges; if checked==0 it never returned (supervisor loop) — the kit auto-retries no_return, trust it.
- Give each function up to ~10 attempts. Only after genuine effort, mark UNPROVEN with a concrete structural reason (e.g. "12-way tbh switch, case 0x1039abc reads unmodeled peripheral FIFO").

Use net_recon_kit (not recon_kit). Report: total, PROVEN count, UNPROVEN list with concrete one-line reasons.`
}
phase('net-opus')
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`net-opus: ${todo.length} batches of hard-tail funcs`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `netop:${i}`, phase: 'net-opus', agentType: 'general-purpose', model: 'opus' })))
const ok = results.filter(Boolean).length
log(`net-opus complete: ${ok}/${results.length} agents returned`)
return { agents: results.length, returned: ok }
