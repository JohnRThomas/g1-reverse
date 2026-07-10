export const meta = {
  name: 'g1-global-naming-net',
  description: 'Sonnet agents name the unnamed net-core globals from evidence packets + proven bodies',
  phases: [{ title: 'name-net-globals', detail: 'net-core global naming, 12 batches' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const BASE = '/Users/freedomcoder/Projects/G1disasm2'

const SCHEMA = {
  type: 'object', required: ['names'],
  properties: { names: { type: 'array', items: {
    type: 'object', required: ['addr', 'name', 'confidence', 'rationale'],
    properties: {
      addr: { type: 'string' }, name: { type: 'string' }, ctype: { type: 'string' },
      confidence: { type: 'string', enum: ['high', 'med', 'low'] },
      is_library: { type: 'boolean' }, upstream_file: { type: 'string' },
      rationale: { type: 'string' },
    } } } },
}

function prompt(i) {
  return `You NAME reverse-engineered global variables of the Even G1 smart-glasses firmware — NETWORK CORE (nRF5340 CPUNET, the 802.15.4/ESB radio + Nordic controller, NCS 2.5.1). Do the work yourself; do NOT spawn sub-agents. Output JSON only.

Environment: PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python ; workdir ${BASE}.

Your batch = element ${i} of ${SCR}/global_name_batches_net.json ; read .globals (evidence packets):
  PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python -c "import json;print(json.dumps(json.load(open('${SCR}/global_name_batches_net.json'))[${i}]['globals'],indent=1))"

Net-core specifics: globals live in shared SRAM (0x2000xxxx) or net-core SRAM (0x21000xxx). The net core has FEW logging strings and NO module map, so nearby_strings is often empty — you must lean on the ACCESS PATTERN in the proven source.

Method per global:
  1. LIBRARY STATIC: if a nearby string is a "WEST_TOPDIR/..." path or a Nordic controller/ESB/OpenAMP message, name it after that upstream role (is_library=true, upstream_file=path). Net-core library is mostly: Nordic SoftDevice Controller (sdc), ESB (esb.c), MPSL, OpenAMP/rpmsg (ipc), nrf 802.15.4 radio driver.
  2. Read the actual access — grep the address and read the body:
       grep -l 0xADDR ${BASE}/recon/net/src/*.c   then read the file(s).
     Pattern -> role: ==0 gate = flag; += = counter; memcpy/index = buffer/array; k_sem/k_msgq/k_thread-shaped struct at the base = kernel object; a pointer stored on connect/init = handle. The IPC/rpmsg shared-memory structs (master_sync_pkg / panel_data_pkg family) and ESB sync state are the app-relevant ones — name those specifically.
  3. snake_case; prefix app globals with g_ ; buffers _buf, counts _cnt. Be specific. If genuinely unknown, name g_net_<addr-suffix>, confidence low, rationale "insufficient evidence".

Return ONLY the names array — one entry per global, every addr covered.`
}

phase('name-net-globals')
const NB = 12
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`net global-naming: ${todo.length} batches`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `gnnet:${i}`, phase: 'name-net-globals', agentType: 'general-purpose', model: 'sonnet', schema: SCHEMA })
    .then((r) => ({ batch: i, names: (r && r.names) || [] }))))
let total = 0; const out = {}
for (const r of results.filter(Boolean)) for (const n of (r.names || [])) { out[n.addr] = n; total++ }
log(`net global-naming: ${total} names across ${results.filter(Boolean).length} batches`)
return { batches: results.length, named: total }
