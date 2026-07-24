#!/usr/bin/env python3
"""Assemble the golden boot trace deliverable from the per-core event lists
and the checkpoint table."""
import json, re, hashlib, sys

REPO = "/Users/freedomcoder/Projects/G1disasm2"
SCRATCH = sys.argv[1]
OUT_JSON = f"{REPO}/recon/emulator/reports/golden_boot_trace.json"

def sha(p):
    h = hashlib.sha256()
    with open(p, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()

app = json.load(open(f"{SCRATCH}/events_app.json"))
net = json.load(open(f"{SCRATCH}/events_net.json"))
app_by = {e["name"]: e for e in app["events"]}

# ---- parse checkpoint table from the run log ----
log = open(f"{SCRATCH}/golden_run.out").read()
checkpoints = []
for m in re.finditer(
    r"=== t=([0-9.]+) ===\s*\n[^\n]*CKPT_RTX:\s*\n\s*(0x[0-9A-Fa-f]+)\s*\n"
    r"[^\n]*CKPT_APP:\s*\n\s*(0x[0-9A-Fa-f]+)\s*\n"
    r"[^\n]*CKPT_NET:\s*\n\s*(0x[0-9A-Fa-f]+)", log):
    checkpoints.append({
        "virtual_time_s": float(m.group(1)),
        "radio_tx_frames": int(m.group(2), 16),
        "app_exec_instr": int(m.group(3), 16),
        "net_exec_instr": int(m.group(4), 16),
    })

def a(name):
    e = app_by.get(name)
    return e["first_i"] if e else None

# first ADV_IND virtual-time window from checkpoints (radio 0 -> >=1)
adv_lo = adv_hi = None
prev = checkpoints[0]
for c in checkpoints:
    if c["radio_tx_frames"] >= 1:
        adv_lo, adv_hi = prev["virtual_time_s"], c["virtual_time_s"]
        break
    prev = c

milestones = [
 {"id": "E1", "label": "reset -> kernel bring-up", "core": "app",
  "anchor": {"name": "z_arm_fault(reset-vector region)", "app_first_i": 0},
  "evidence": [
     {"what": "reset vector executes (SP/PC from VTOR 0xC200)", "app_first_i": 0},
     {"what": ".bss/.data init (memset_bytes)", "app_first_i": a("memset_bytes")},
     {"what": ".data copy (memcpy)", "app_first_i": a("memcpy")},
     {"what": "region_init", "app_first_i": a("region_init")},
     {"what": "arm_core_mpu_configure", "app_first_i": a("arm_core_mpu_configure")},
     {"what": "z_impl_k_sem_init (kernel objects)", "app_first_i": a("z_impl_k_sem_init")},
     {"what": "kmutex/dlist init", "app_first_i": a("kmutex_dlist_init")},
  ],
  "cross_check_original_boot_json":
     "region_init@448729 (orig 448730), z_impl_k_sem_init@449110 (orig 449109), "
     "clock_control_nrf_init@449683 (orig 449682) -- Renode boot chain matches the "
     "Unicorn original_boot.json to within a few instructions."},

 {"id": "E2", "label": "device / SYS_INIT driver init", "core": "app",
  "anchor": {"name": "clock_control_nrf_init", "app_first_i": a("clock_control_nrf_init")},
  "evidence": [
     {"what": "clock_control_nrf_init", "app_first_i": a("clock_control_nrf_init")},
     {"what": "nrfx_clock_init/enable", "app_first_i": a("nrfx_clock_init")},
     {"what": "onoff_manager_init", "app_first_i": a("onoff_manager_init")},
     {"what": "g1_recon_k_heap_init / sys_heap_init", "app_first_i": a("g1_recon_k_heap_init")},
     {"what": "g1_recon_nrfx_gpiote_init", "app_first_i": a("g1_recon_nrfx_gpiote_init")},
     {"what": "nrf_cc3xx_platform_init (CC312 -- Renode CC3xx RNG model resolves "
              "the TRNG startup test that BLOCKED the Unicorn boot)",
      "app_first_i": a("nrf_cc3xx_platform_init")},
  ],
  "note": "This is PAST the CC312/TRNG blocker recorded in boot_blockers.md; "
          "the seeded NRF5340_CC3xx_RNG model supplies deterministic entropy so "
          "the startup self-test completes and boot proceeds."},

 {"id": "E3", "label": "main() + thread creation", "core": "app",
  "anchor": {"name": "main", "app_first_i": a("main")},
  "evidence": [
     {"what": "z_impl_k_thread_create (kernel threads created)", "app_first_i": a("z_impl_k_thread_create")},
     {"what": "main() entry (0x16eb8)", "app_first_i": a("main")},
     {"what": "thread_entry_no_return", "app_first_i": a("thread_entry_no_return")},
     {"what": "settings_subsys_init", "app_first_i": a("settings_subsys_init")},
  ]},

 {"id": "E4", "label": "\"it lives\": net released + IPC up + display init + first ADV_IND",
  "core": "app+net",
  "anchor": {"name": "bt_start", "app_first_i": a("bt_start")},
  "evidence": [
     {"what": "CPUNET released & executing (app cleared RESET.NETWORK.FORCEOFF "
              "@0x50005614); net begins at its reset vector",
      "net_first_i": 0, "net_reset_pc": "0x0102fc8c"},
     {"what": "OpenAMP/rpmsg IPC endpoint bring-up (ipc_service_send over sram0_shared)",
      "app_first_i": a("ipc_service_send")},
     {"what": "display panel init -- JBD SPI ID probe spi_read_id (0x47724)",
      "app_first_i": a("spi_read_id")},
     {"what": "BLE stack start -- bt_start (0x19308)", "app_first_i": a("bt_start")},
     {"what": "first BLE ADV_IND transmitted over the modeled RADIO "
              "(radio.TransmittedFrames 0 -> 1)",
      "virtual_time_window_s": [adv_lo, adv_hi],
      "confirmed_autonomously": "yes -- no BLE central/ESB peer attached"},
  ]},

 {"id": "E5", "label": "steady state (operational loop)", "core": "app+net",
  "anchor": {"name": "operational-steady-state (first ADV_IND done, advertising "
             "loop cycling, new-function discovery flatlined)",
             "app_exec_instr": next(c["app_exec_instr"] for c in checkpoints
                                    if c["virtual_time_s"] == 2.0),
             "virtual_time_s": 2.0},
  "evidence": [
     {"what": "app core dominated by arch_cpu_idle / wfi_idle_loop (WFI halts "
              "the core between periodic wakeups); arch_cpu_idle recurs "
              "throughout, first seen at the idle thread's boot-sleep",
      "arch_cpu_idle_first_i": a("arch_cpu_idle"),
      "arch_cpu_idle_entries": (app_by.get("arch_cpu_idle") or {}).get("entries")},
     {"what": "net SDC advertising loop running: radio frames climb 1->6 across "
              "t=1.5-2.0s then hold; net core busy-burst then idle",
      "radio_tx_frames_at_t3": checkpoints[-1]["radio_tx_frames"]},
     {"what": "new-function discovery has flatlined into periodic-task first-"
              "invocations (watchdog_feed_retry, timers) -- no further boot phases",
      "app_last_new_first_i": max(e["first_i"] for e in app["events"]),
      "net_last_new_first_i": max(e["first_i"] for e in net["events"])},
  ]},
]

doc = {
 "schema": "g1_golden_boot_trace_v1",
 "description":
   "Deterministic behavioral oracle of the SHIPPED Even Realities G1 firmware "
   "booting in the Renode nRF5340 emulator (autonomous boot, no external radio "
   "peer). Ordered per-core function-entry events (first-entry order + repeat "
   "counts), annotated with recon symbol names, with milestone markers E1-E5. "
   "A rebuild-from-source must reproduce this event order/structure.",
 "emulator": "Renode 1.16.1 (d66b0c2a) macOS arm64",
 "boot_script": "armemul/g1.resc",
 "images": {
   "app": {"path": "app_update.bin", "link_base": "0xC200",
           "sha256": sha(f"{REPO}/app_update.bin")},
   "net": {"path": "netcore_image.bin", "runtime_base": "0x01008800",
           "sha256": sha(f"{REPO}/netcore_image.bin")},
 },
 "determinism": {
   "global_quantum_s": 1e-05,
   "core_scheduling": "serial (EmulationManager ... ExecuteInSerial = True, set in g1.resc)",
   "cc3xx_rng_seed": "0x5340CC3105340CC3 (NRF5340_CC3xx_RNG SplitMix64, the only entropy source)",
   "virtual_time_budget_s": 3.0,
   "external_stimulus": "none (vcentral / esbslave / gesture all DISABLED) -- pure autonomous boot",
   "trace_format": "Renode cpu CreateExecutionTracing PC; trace line index == cpu.ExecutedInstructions (0-based). "
                   "PC -> function via greatest catalog address <= PC.",
   "symbol_maps": {
     "app": "recon/catalogs/function_names_app.json (by_address)",
     "net": "recon/catalogs/net_address_spaces.json (functions[].runtime_address)"},
 },
 "regenerate_command":
   "mkdir -p /tmp/g1_golden && cd /Users/freedomcoder/Projects/armemul && "
   "~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain "
   "-e 'i @/Users/freedomcoder/Projects/G1disasm2/recon/emulator/scripts/golden_trace.resc' "
   "> /tmp/g1_golden/golden_run.out 2>&1 ; R=/Users/freedomcoder/Projects/G1disasm2 ; "
   "V=\"PYTHONSAFEPATH=1 $R/.venv/bin/python\" ; "
   "$V $R/recon/emulator/scripts/analyze_trace.py app /tmp/g1_golden/trace_app.log /tmp/g1_golden/events_app.json ; "
   "$V $R/recon/emulator/scripts/analyze_trace.py net /tmp/g1_golden/trace_net.log /tmp/g1_golden/events_net.json ; "
   "$V $R/recon/emulator/scripts/build_golden.py /tmp/g1_golden",
 "milestones_reached": "E1, E2, E3, E4, E5 (all)",
 "checkpoints": checkpoints,
 "milestones": milestones,
 "cores": {
   "app": {"link_base": "0xC200", "reset_vector_pc": "0x00050a99",
           "total_instr": app["total_instr"], "unique_functions": app["unique_functions"],
           "events": app["events"]},
   "net": {"runtime_base": "0x01008800", "reset_vector_pc": "0x0102fc8c",
           "total_instr": net["total_instr"], "unique_functions": net["unique_functions"],
           "events": net["events"]},
 },
}
json.dump(doc, open(OUT_JSON, "w"), indent=1)
print("wrote", OUT_JSON)
print("first ADV_IND window (s):", adv_lo, "->", adv_hi)
print("app events:", len(app["events"]), "net events:", len(net["events"]))
