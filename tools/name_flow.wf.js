export const meta = {
  name: 'g1-semantic-naming',
  description: 'Opus agents deduce semantic names for proven functions + globals per coupled subsystem',
  phases: [{ title: 'name', detail: '50 Opus agents, ~40 functions each, code-semantics + community findings' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const NB = 50

function prompt(i) {
  return `You are an expert firmware reverse engineer. DEDUCE SEMANTIC NAMES for a coupled group of already-parity-proven functions of the Even G1 smart-glasses firmware (nRF5340, NCS 2.5.1). This is naming/analysis ONLY — do NOT modify any proven code. Do the work yourself; do NOT spawn sub-agents.

Environment: PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python ; workdir /Users/freedomcoder/Projects/G1disasm2.

Your batch = element ${i} of ${SCR}/name_batches.json. Read its topic hint + addresses:
  PYTHONSAFEPATH=1 .venv/bin/python -c "import json;b=json.load(open('${SCR}/name_batches.json'))[${i}];print(b['topic']);print(' '.join(b['addrs']))"
(The topic hint is a COARSE guess from call-graph propagation — correct it from the actual code.)

For EACH address:
  1. Inspect: PYTHONSAFEPATH=1 .venv/bin/python tools/recon_kit.py info 0xADDR  (decompilation, disasm, callees, literal-pool globals). Also read the proven source recon/verified/src/<name>.c if present.
  2. Deduce a descriptive snake_case FUNCTION NAME + a one-line purpose, from what the code actually does: which globals it reads/writes, which (named) callees it invokes, its control flow, and any format/log strings it references (strings are the strongest signal — grep debug_strings.txt / debug_r1_strings.txt for the address's strings).
  3. NAME the globals / struct fields it touches. Cross-reference:
       - recon/application/app/src/device_info.h (device_info_t @ 0x200069FC),
       - recon/application/app/src/recovered_structs.h (the 3 big app structs, placeholder fields f_XX),
       - recon/application/app/src/even_protocol.h (BLE service-ID registry).
  4. COMMUNITY FINDINGS (OPTIONAL, time-box to ONE fetch max — do NOT get stuck here): the code + strings are your PRIMARY signal. Only if a BLE/protocol function is unclear, you MAY do a single WebFetch (ToolSearch "select:WebFetch") of one specific raw doc from the MIT project github.com/kalanihelekunihi/evenRealities-openCFW (e.g. docs/protocols/services.md) to map a service ID / command opcode to a name. Use the FACTS only; do not copy text. If a fetch is slow or unhelpful, skip it and name from the code.

Write your results to ${SCR}/name_out_${i}.json as:
  {"topic_corrected": "...", "functions": {"0xADDR": {"name": "...", "purpose": "..."}, ...},
   "globals": {"0xADDR": {"name": "...", "type": "...", "struct_field": "g_obj_XXXX.field or device_info.XXX or null"}, ...}}
Only include names you are reasonably confident in; leave genuinely opaque ones out (better no name than a wrong one). Do NOT modify recon/verified/**, tools/**, or any proven .c.

Report: topic (corrected), #functions named, #globals named, and any subsystem-level insight.`
}

phase('name')
// only run batches whose name_out_<i>.json does not yet exist (idempotent resume)
const todo = (args && args.todo) || Array.from({ length: NB }, (_, i) => i)
log(`naming ${todo.length} remaining batches on sonnet`)
const results = await parallel(todo.map((i) => () =>
  agent(prompt(i), { label: `name:${i}`, phase: 'name', agentType: 'general-purpose', model: 'sonnet' })))
const ok = results.filter(Boolean).length
log(`naming complete: ${ok}/${results.length} agents returned`)
return { agents: results.length, returned: ok }
