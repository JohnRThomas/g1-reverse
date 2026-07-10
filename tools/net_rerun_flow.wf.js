export const meta = {
  name: 'g1-net-rerun',
  description: 'Sonnet agents finish the net-core tail (dropped/hard batches)',
  phases: [{ title: 'net-rerun', detail: '9 Sonnet agents, ~9 net-core tail functions each' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const NB = 9
function prompt(i) {
  return `Read /Users/freedomcoder/Projects/G1disasm2/tools/NET_PLAYBOOK.md and follow it EXACTLY. Do the work yourself; do NOT spawn sub-agents; do NOT edit anything under tools/.

export RECON_LEDGER=${SCR}/net_rerun_ledger_${i}.json

Your batch = element ${i} of ${SCR}/net_rerun_batches.json — read its addresses:
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python -c "import json;print(' '.join(json.load(open('${SCR}/net_rerun_batches.json'))[${i}]))"

Reconstruct and parity-prove every address per the net playbook (use net_recon_kit, not recon_kit). These are tail functions — some are large dispatchers or jump-table driven; give each a genuine attempt, and if still unproven after ~6 tries mark it UNPROVEN with a concrete one-line reason. Report: total, PROVEN count, UNPROVEN list with one-line reasons.`
}
phase('net-rerun')
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`net-rerun: ${todo.length} batches`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `netre:${i}`, phase: 'net-rerun', agentType: 'general-purpose', model: 'sonnet' })))
const ok = results.filter(Boolean).length
log(`net-rerun complete: ${ok}/${results.length} agents returned`)
return { agents: results.length, returned: ok }
