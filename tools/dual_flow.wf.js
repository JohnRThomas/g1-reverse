export const meta = {
  name: 'g1-dual-flow',
  description: 'Reconstruct remaining app functions (20 agents) + symbolize proven functions (20 agents), in parallel',
  phases: [
    { title: 'reconstruct', detail: '20 agents, ~39 unproven functions each, parity-proven' },
    { title: 'symbolize',  detail: '20 agents, rename callees + map globals on proven .c files' },
  ],
}

const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const N = 20

function reconPrompt(i) {
  return `Read /Users/freedomcoder/Projects/G1disasm2/tools/RECON_PLAYBOOK.md and follow it EXACTLY. Do the work YOURSELF; do NOT spawn sub-agents; do NOT edit anything under tools/.

Your batch is element ${i} of ${SCR}/recon_batches.json — read it:
  PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python -c "import json;print(' '.join(json.load(open('${SCR}/recon_batches.json'))[${i}]))"

export RECON_LEDGER=${SCR}/ledger_WF_recon_${i}.json

Reconstruct and parity-prove every address in your batch per the playbook (globals as volatile absolute-address pointers; callees as extern; match arithmetic/branches/loops exactly; always call recon_kit.prove even for expected-UNPROVEN so it logs). Report: total, PROVEN count, UNPROVEN list with one-line reasons. Do NOT paste source.`
}

function symPrompt(i) {
  return `You are SYMBOLIZING already-parity-proven reconstructions (making them readable). Do the work YOURSELF; do NOT spawn sub-agents; do NOT edit anything under tools/ or the frozen harness. Operate ONLY on proven files (never on files another agent is reconstructing).

Environment: PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python ; workdir /Users/freedomcoder/Projects/G1disasm2.

Your batch is element ${i} of ${SCR}/sym_batches.json (a list of .c basenames in recon/app/src/). Read it:
  PYTHONSAFEPATH=1 .venv/bin/python -c "import json;print('\\n'.join(json.load(open('${SCR}/sym_batches.json'))[${i}]))"

Inputs you may use:
  - ${SCR}/symbol_map.json : { "0xADDR": "real_name", ... } for renaming FUN_xxxx/sub_xxxx callees (the hex in the FUN_/sub_ name IS the address; map it).
  - recon/application/app/src/device_info.h : recovered global-state struct; its base RAM address is 0x200069FC (device_info_t, size 0x18E0). A referenced RAM address in [0x200069FC, 0x200082DC) is device_info_t + (addr-0x200069FC) -> name the field by matching the offset to device_info.h.
  - The NCS 2.5.1 source at /Users/freedomcoder/ncs251 (grep for struct layouts / Zephyr device APIs) and even_protocol.h for BLE service IDs.

Skip any file that already exists in recon/app/src_sym/ (already done). For each remaining file recon/app/src/NAME.c produce recon/app/src_sym/NAME.c:
  1. Rename every FUN_xxxxx / sub_xxxxx callee to its real name via symbol_map.json (leave truly-unknown ones as-is).
  2. Replace device_info_t absolute addresses with a documented reference to the field (e.g. /* device_info.current_app_id */), keeping the numeric address in a comment so parity is preserved.
  3. Recognize Zephyr driver-vtable dispatch (obj->api->method) and comment it as the equivalent Zephyr call (flash_erase/flash_read/etc.).
  4. Keep the code semantically identical (do NOT change logic) — this is renaming/annotation only. Preserve the parity header comment.
  5. For RAM addresses NOT in device_info_t, append a one-line note to ${SCR}/unknown_globals_${i}.txt: "0xADDR referenced_by NAME access_width" so we can cluster/identify them later.

Report: files symbolized, callees renamed, device_info fields mapped, and count of unknown globals logged. Do NOT paste full source.`
}

const reconThunks = Array.from({ length: N }, (_, i) => () =>
  agent(reconPrompt(i), { label: `recon:${i}`, phase: 'reconstruct', agentType: 'general-purpose' }))
const symThunks = Array.from({ length: N }, (_, i) => () =>
  agent(symPrompt(i), { label: `symbolize:${i}`, phase: 'symbolize', agentType: 'general-purpose' }))

// INTERLEAVE the two flows so the ~8 concurrent slots are shared fairly
// (recon0, sym0, recon1, sym1, ...) instead of recon monopolizing them.
const interleaved = []
for (let i = 0; i < N; i++) { interleaved.push(reconThunks[i], symThunks[i]) }

const results = await parallel(interleaved)
const ok = results.filter(Boolean).length
log(`dual-flow complete: ${ok}/${results.length} agents returned`)
return { agents: results.length, returned: ok }
