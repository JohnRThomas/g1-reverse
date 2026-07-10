export const meta = {
  name: 'g1-data-wiring',
  description: 'Fable agents: advance modules via the reference graph + recover data/structs from the image',
  phases: [
    { title: 'modules', detail: 'one agent per subsystem, graph-driven API + wiring' },
    { title: 'data',    detail: 'one agent per rodata batch, extract typed const tables' },
  ],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const MODULES = ['ancs_notify','system','audio','misc','flash_store','display','gui_text','battery',
                 'ble_proto','dashboard','analytics','esb_sync','touch_key','imu_motion','ipc_core',
                 'quicknote','onboarding','translate']
const NDATA = 12

function modPrompt(m) {
  return `You ADVANCE the "${m}" module of the Even G1 smart-glasses firmware (nRF5340 app core) using the authoritative Ghidra reference graph. Do the work yourself; do NOT spawn sub-agents. Read-only on recon/verified, recon/named, tools; write only under recon/modules/${m}/.

Environment: PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python ; workdir /Users/freedomcoder/Projects/G1disasm2.

Graph-driven inputs:
  - ${SCR}/module_units.json  -> ["${m}"] gives: api (functions called from OTHER modules = the real public API), entry_points (thread mains / callbacks with no in-module caller), n_owned_data.
  - ${SCR}/refgraph_app.json  -> per function: exact calls, data_refs, callers. Use it to (a) fix the header's public/internal split, (b) deduce each remaining FUN_xxxx's purpose from its concrete callers+callees+data, (c) find the module's threads/msgqs/sems.
  - ${SCR}/topic_groups.json  -> ["${m}"] the member functions.
  - recon/named/*.c and recon/verified/src/*.c  -> the proven bodies.

Produce/refine in recon/modules/${m}/:
  1. ${m}.h  — public prototypes = ONLY the graph's api set (mark the rest static/internal); include a doc-comment on the subsystem.
  2. README.md — responsibility, key functions (name — role), owned data/structs, and ENTRY POINTS.
  3. wiring.md — the RTOS objects this module DEFINES, read out of its init functions: for each thread K_THREAD_DEFINE(entry, stack, prio); each msgq K_MSGQ_DEFINE(name, msg_size, count); each sem/mutex/work — with the exact params from the k_*_init calls in the proven code (cite the function + address). This is the input to the wiring reconstruction.

Report: api count, remaining FUN_ purposes deduced, RTOS objects the module defines.`
}

function dataPrompt(i) {
  return `You RECOVER static data (const rodata tables) of the Even G1 app core firmware from the image. Do the work yourself; do NOT spawn sub-agents. Write only under recon/data/.

Environment: PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python ; workdir /Users/freedomcoder/Projects/G1disasm2.
Byte reads: from tools/extract.py -> extract.read(va, n) / extract.read_u32(va)  (app core, link base 0xC200).

Your batch = element ${i} of ${SCR}/data_units.json (a list of {base, span, naddr} rodata objects). Read it:
  PYTHONSAFEPATH=1 .venv/bin/python -c "import json;print(json.load(open('${SCR}/data_units.json'))[${i}])"

For each rodata object:
  - Inspect who reads it and how, via ${SCR}/refgraph_app.json (which functions have this base in data_refs) and their proven bodies in recon/named/ — the access pattern (index stride, element width, signedness) tells you the element type and count.
  - Extract the bytes with extract.read(base, span) and emit a typed C definition to recon/data/rodata_<base>.c:
      a const array (uint8_t/uint16_t/uint32_t/int16_t...) OR a const struct if it is a config/table-of-structs, with a comment naming it by purpose (e.g. gamma_curve, cmd_dispatch_table, panel_init_seq) inferred from the readers.
  - VERIFY byte-exactness: your emitted initializer must reproduce extract.read(base, span) exactly.
Skip anything that is actually code or a jump table (note it). Do NOT modify recon/verified, recon/named, or tools.

Report: objects recovered, total bytes, and any notable tables (curves, dispatch tables, sequences, structs) identified.`
}

phase('modules')
const modThunks = MODULES.map((m) => () =>
  agent(modPrompt(m), { label: `mod:${m}`, phase: 'modules', agentType: 'general-purpose', model: 'fable' }))
phase('data')
const dataThunks = Array.from({ length: NDATA }, (_, i) => () =>
  agent(dataPrompt(i), { label: `data:${i}`, phase: 'data', agentType: 'general-purpose', model: 'fable' }))

// interleave so both waves share the concurrency slots
const inter = []
const mx = Math.max(modThunks.length, dataThunks.length)
for (let i = 0; i < mx; i++) { if (modThunks[i]) inter.push(modThunks[i]); if (dataThunks[i]) inter.push(dataThunks[i]) }
const results = await parallel(inter)
const ok = results.filter(Boolean).length
log(`data+wiring complete: ${ok}/${results.length} agents returned`)
return { agents: results.length, returned: ok }
