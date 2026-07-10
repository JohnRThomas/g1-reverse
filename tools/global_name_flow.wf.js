export const meta = {
  name: 'g1-global-naming',
  description: 'Agents name the unnamed app-core globals from precomputed evidence packets',
  phases: [{ title: 'name-globals', detail: 'one agent per module slice, evidence-driven naming' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const BASE = '/Users/freedomcoder/Projects/G1disasm2'

const SCHEMA = {
  type: 'object',
  required: ['names'],
  properties: {
    names: {
      type: 'array',
      items: {
        type: 'object',
        required: ['addr', 'name', 'confidence', 'rationale'],
        properties: {
          addr: { type: 'string', description: 'the 0x... address from the packet' },
          name: { type: 'string', description: 'proposed C identifier, snake_case, prefix g_ for app globals' },
          ctype: { type: 'string', description: 'refined C type if you can improve on the packet' },
          confidence: { type: 'string', enum: ['high', 'med', 'low'] },
          is_library: { type: 'boolean', description: 'true if this is a Zephyr/NCS library static (name it per upstream)' },
          upstream_file: { type: 'string', description: 'e.g. nrf/subsys/bluetooth/gatt_dm.c, if library' },
          rationale: { type: 'string', description: 'one sentence: the evidence that justifies the name' },
        },
      },
    },
  },
}

function prompt(i) {
  return `You NAME reverse-engineered global variables of the Even G1 smart-glasses firmware (nRF5340 app core, Zephyr/NCS 2.5.1). Do the work yourself; do NOT spawn sub-agents. Read-only on everything; you output JSON only.

Environment: PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python ; workdir ${BASE}.

Your batch = element ${i} of ${SCR}/global_name_batches_app.json ; it has a .module label and .globals (each an evidence packet). Read it:
  PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python -c "import json;b=json.load(open('${SCR}/global_name_batches_app.json'))[${i}];print('MODULE:',b['module']);print(json.dumps(b['globals'],indent=1))"

Each packet has: addr, ctype (from casts), written (is it ever assigned), n_source_reads, ref_funcs (functions that touch it — human names where known, else FUN_xxxx), module, nearby_strings (strings those functions reference).

Naming method, in order of reliability:
  1. LIBRARY STATIC: if nearby_strings contain a "WEST_TOPDIR/..." path or clearly-Zephyr messages (e.g. gatt_dm.c, "Not enough memory for service attribute"), this global is a Zephyr/NCS library static. Name it after its role in that upstream file (set is_library=true, upstream_file=the path). These are high-confidence.
  2. ACCESSOR: if ref_funcs are get_X/set_X/is_X style, the global IS X.
  3. STRING-ADJACENT STATE: a flag/counter/buffer read right before a debug_print of a specific message — name from that message's subject (e.g. read before "battery low" -> g_battery_low_*).
  4. For ambiguous ones, OPEN THE PROVEN SOURCE to see the exact access: grep the address in recon/named/*.c and read the function body:
       grep -l 0xADDR ${BASE}/recon/named/*.c   then read the file.
     The access pattern (index stride = array; ==0 gate = flag; += = counter; memcpy dst = buffer) plus the surrounding logic names it.

Rules: snake_case; prefix app globals with g_ ; buffers end _buf, counts _cnt, flags reflect polarity; keep it specific not generic (avoid g_flag1). If you truly cannot tell, name it g_<module>_<addr-suffix> and mark confidence low with rationale "insufficient evidence".

Return ONLY the structured names array — one entry per global in your batch, every addr covered.`
}

phase('name-globals')
const NB = 29
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`global-naming: ${todo.length} module batches`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `gname:${i}`, phase: 'name-globals', agentType: 'general-purpose', model: 'sonnet', schema: SCHEMA })
    .then((r) => ({ batch: i, names: (r && r.names) || [] }))))
// consolidate
const fs_out = {}
let total = 0
for (const r of results.filter(Boolean)) {
  for (const n of (r.names || [])) { fs_out[n.addr] = n; total++ }
}
log(`global-naming: collected ${total} names across ${results.filter(Boolean).length} batches`)
return { batches: results.length, named: total, names: fs_out }
