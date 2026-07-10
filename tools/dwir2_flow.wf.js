export const meta = {
  name: 'g1-assemble-1to3',
  description: 'Fable agents: reconcile wiring (1), assemble type headers (2), recover board/DTS/pinctrl (3)',
  phases: [{ title: 'assemble', detail: 'wiring reconciliation + D2 headers + D4 board recovery' }],
}
const SCR = '/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/bf259b2e-0c97-4e04-ae79-84a08ccae34e/scratchpad'
const BASE = '/Users/freedomcoder/Projects/G1disasm2'

const TASKS = [
  { label: 'wiring-reconcile', out: 'recon/wiring/',
    body: `STEP 1 — reconcile RTOS wiring. Merge every recon/modules/*/wiring.md into a single recon/wiring/app_objects.c: all K_THREAD_DEFINE / K_MSGQ_DEFINE / K_SEM_DEFINE / K_MUTEX_DEFINE / K_TIMER_DEFINE with their exact params, grouped by subsystem, each cited to its source function. Then CROSS-CHECK against the WS2 kernel-object inventory ${SCR}/ws2_reliable.json (k_msgq/k_sem/k_mutex/k_work instances by address): write recon/wiring/GAPS.md listing any WS2 object with NO matching definition (a wiring gap to chase) and any definition with no WS2 object. Report counts by type and the gap list.` },
  { label: 'headers-d2', out: 'recon/headers/',
    body: `STEP 2 — assemble the complete type headers so code + data compile. Into recon/headers/ produce: (a) g1_types.h collecting device_info_t (from recon/application/app/src/device_info.h), the 3 recovered app structs (recon/application/app/src/recovered_structs.h), and even_protocol.h; (b) ipc_sync.h — the shared app<->net IPC message structs (the *_sync_pkg / master_sync_pkg.panel_data_pkg family referenced by ipc_core/esb_sync — reconstruct their layout from the accessing functions in recon/named/ and the field offsets); (c) zephyr_objects.h — typedefs/externs for the Zephyr kernel object types used (k_msgq, k_sem, etc., names only — real defs come from Zephyr). Make them self-consistent (guards, includes). Report the structs assembled and any unresolved field.` },
  { label: 'board-gpio', out: 'recon/board/',
    body: `STEP 3a — recover PIN assignments for GPIO/buttons/LEDs and the projector-related control lines. Use ${SCR}/refgraph_app.json to find functions with data_refs into the nRF GPIO/pinctrl region (0x50000000 P0, 0x50000300 P1, 0x50842500-ish for nRF5340) and read the proven bodies in recon/named/ (e.g. button_init references g_gpio0_dev/g_gpio1_dev). Extract the exact PSEL/pin numbers written. Write recon/board/pins_gpio.md: peripheral -> pin (Px.yy) -> direction/pull, with the source function cited. Report pins recovered.` },
  { label: 'board-buses', out: 'recon/board/',
    body: `STEP 3b — recover the SPI / I2C / QSPI / PWM / UART peripheral instances and their pins. Use ${SCR}/refgraph_app.json + the WS2 flash device objects and recon/named/ driver-init functions (jbd panel over SPI, opt3007 + IMU over I2C, mx25r64 over QSPI). Identify which SPIM/TWIM/PWM/UARTE instance each device uses and the SCK/MOSI/MISO/CS or SDA/SCL pins from the pinctrl register writes. Write recon/board/pins_buses.md and a draft recon/board/g1_board.overlay devicetree fragment (nodes + pinctrl) for nrf5340dk_nrf5340_cpuapp. Report devices + buses mapped.` },
  { label: 'kconfig', out: 'recon/board/',
    body: `STEP 3c — finalize the app-core prj.conf. Start from the validated /Users/freedomcoder/ncs251/refapp/prj.conf, then reconcile against the actual subsystems in recon/modules/ (BLE peripheral+central+ANCS, NVS/settings, PDM audio, ESB, SPI display, sensors, IPC). Write recon/board/prj.conf with a comment per option citing the module/evidence that requires it, and note any option you are unsure about. Report the final option set.` },
]

phase('assemble')
const results = await parallel(TASKS.map((t) => () =>
  agent(`You work on the recovered Even G1 app-core firmware sources. Do the work yourself; do NOT spawn sub-agents; read-only on recon/verified, recon/named, tools; write only under ${t.out}. Env: PYTHONSAFEPATH=1 ${BASE}/.venv/bin/python ; workdir ${BASE}.\n\n${t.body}`,
    { label: t.label, phase: 'assemble', agentType: 'general-purpose', model: 'fable' })))
log(`assemble 1-3 complete: ${results.filter(Boolean).length}/${results.length}`)
return { agents: results.length, returned: results.filter(Boolean).length }
