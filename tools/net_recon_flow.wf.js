export const meta = {
  name: 'g1-net-recon',
  description: 'Sonnet agents reconstruct + parity-prove the net-core application functions',
  phases: [{ title: 'net-recon', detail: '24 Sonnet agents, ~29 net-core app functions each' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const NB = 24
function prompt(i) {
  return `Read /Users/freedomcoder/Projects/G1disasm2/tools/NET_PLAYBOOK.md and follow it EXACTLY. Do the work yourself; do NOT spawn sub-agents; do NOT edit anything under tools/.

export RECON_LEDGER=${SCR}/net_ledger_${i}.json

Your batch = element ${i} of ${SCR}/net_recon_batches.json — read its addresses:
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python -c "import json;print(' '.join(json.load(open('${SCR}/net_recon_batches.json'))[${i}]))"

Reconstruct and parity-prove every address per the net playbook (use net_recon_kit, not recon_kit). Report: total, PROVEN count, UNPROVEN list with one-line reasons.`
}
phase('net-recon')
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`net-recon: ${todo.length} batches`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `net:${i}`, phase: 'net-recon', agentType: 'general-purpose', model: 'sonnet' })))
const ok = results.filter(Boolean).length
log(`net-recon complete: ${ok}/${results.length} agents returned`)
return { agents: results.length, returned: ok }
