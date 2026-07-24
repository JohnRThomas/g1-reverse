# Build-from-sources → Emulator boot-parity plan

## OWNER GOAL (set 2026-07-24, supersedes scope below where they conflict)
1. **Compile the firmware and achieve FUNCTIONAL PARITY** — proven by testing and
   comparison against the actual original firmware. **The parity bar (owner-set):
   the firmware must RENDER THE IMAGE and OPERATE ALL SENSORS correctly, with
   graphics working as in the original firmware.** E4 "it lives" is only an
   intermediate gate; the acceptance target is **E6 = graphics + sensor parity**:
   - **Graphics**: our build's display output must match the original's — the same
     JBD panel init/command sequence, the same framebuffer/pixel payloads over SPI,
     the same brightness/gear handling. Diffed pixel-exact against the original
     (see `recon/emulator/reports/display_sensor_parity.md` + the captured oracle).
   - **Sensors**: every sensor the original drives must be driven identically —
     IMU (LSM6DSO), ambient light (OPT3001/OPT3007), touch/capacitive keys, battery/
     charger (nPM1300), microphone (PDM), and the ESB L/R sync path — same bus
     transactions, same interpretation of readings.
   The golden Renode function-entry trace remains the boot oracle; graphics/sensor
   parity adds a **peripheral-transaction oracle** (SPI/I2C/PDM/radio traffic).
2. **Rely on library functions — drop their recovered versions.** Displace every
   recovered reconstruction of SDK/Zephyr/nrfxlib/newlib/etc. code to the real
   library, gaining stability and correct typing for free. Rationale hardened by
   iteration 5: hand-reconstructions of stock code carry defects the parity harness
   CANNOT see (it emulates at original addresses, where wrong-but-accidentally-
   working codegen still passes). Tracked as task G2;
   see `recon/ownership/library_displacement_{candidates.json,report.md}`.
3. **Then refactor into a well-structured production-grade project** (task G3):
   cohesive modules, real headers/types replacing absolute-address pins, proper
   naming and build organization.


**Goal (scoped 2026-07-24):** Build the CPUAPP+CPUNET firmware from the
reconstructed sources and make it boot on the Renode emulator (`../armemul`)
the same way the shipped images do — to acceptance tier **E4 ("it lives")**,
**both cores concurrently**.

## The key reframe
Prior work optimized **per-function parity** (byte/semantic faithfulness) and
**byte-match** of the assembled image. Emulator boot is a different, system-level
gate: **behavioral boot-parity** — our build, loaded into Renode, must traverse
the same boot/init/thread milestones and reach the same runtime behavior as the
shipped image. It does NOT require byte-identical `.text`.

## Ground truth confirmed
- **Renode** at `~/tools/Renode.app/Contents/MacOS/renode` (`RENODE` env var).
- **Original boots past E4 already**: `armemul/scripts/g1-selfdrive.sh` drives the
  shipped image boot → real ADV_IND → CONNECT_IND → GATT/NUS write →
  `ble_process_req_dispatch` → `trigger_screen_state_change` (display START) →
  ESB L+R sync. CC312/TRNG blocker is resolved in Renode. This script is the
  behavioral **acceptance harness**; its trace is the **golden oracle**.
- **Loaders**: `g1.resc` loads raw bins (app→`0x0000C000`,VTOR`0xC200`;
  net→`0x01008800`,VTOR there; FICR/UICR seeded). `nrf5340.resc` `LoadELF`s a
  `zephyr.elf` — so our build output loads directly:
  `renode -e '$app_elf=@build/zephyr/zephyr.elf; i @nrf5340.resc'`.
- **Build toolchain present**: `~/ncs251` (Zephyr 3.4.99), `west` on PATH.
- **Cohesive build shell** `recon/application/{app,net}` compiles+links+packages
  cleanly (no undefined/dup symbols) BUT uses a **temporary `main`**, has **3
  unnamed thread-entry roots**, `wiring/app_objects.c` is evidence-only (not a
  build input), and final section placement is unresolved.

## Gaps between "compiles" and "boots like original"
1. No real entrypoint/init graph (temporary main; 3 missing thread roots).
2. Init-array ordering (SYS_INIT/DEVICE levels+priorities) not reconstructed
   into the build — recoverable from the image's `__init_*`/`__device_*` tables.
3. Boot-path correctness residue: ~40+ confirmed CFG false-proofs unredone; not
   yet intersected with the boot-trace function set.
4. Image shaping: emit app@0xC200 / net@0x01008800; app must clear
   `RESET.NETWORK.FORCEOFF` (0x50005614) to release net.
5. No deterministic golden milestone log to diff against.

## Phased plan (critical path)
- **P0 — Golden boot oracle** (free): run shipped app+net in Renode to fixed
  budget; capture ordered milestone/function-entry log → `golden_boot_trace.json`.
  Tiers: E1 reset→kernel, E2 device init, E3 main+threads, **E4** net released +
  rpmsg IPC up + first BLE advert + display init, E5 steady-state.
- **P1 — Boot-path correctness closure** (free compute + agents): finish CFG
  sweep; intersect FAILs with boot-trace set; redo boot-path FAILs first
  (`cfg_verify`).
- **P2 — Real init/thread graph** — SCOPE REDUCED by P2-prep findings
  (`boot_init_graph.md`, verified 2026-07-24): **neither core has ANY app-owned
  `SYS_INIT`/`DEVICE` entry and NO static `K_THREAD_DEFINE`.** All 48 app + 26 net
  init entries are stock Zephyr/nrfxlib/SoC (emitted by the SDK from Kconfig+DT).
  Every Even-specific bring-up runs inside `main()`, which spawns app threads
  **dynamically via `k_thread_create`**. So P2 = three steps, not a novel graph:
  1. **Install the real mains** (drop the temporary main): app `main` @0x16eb8
     (recon/app/src/main.c, cfg_verify PASS cases=12); net `g1_cpunet_main`
     @0x0102a720 (runtime 0x0102af20). Both already reconstructed + verified.
  2. **No hand-written SYS_INIT/DEVICE** — reproduce the init arrays via correct
     `prj.conf`+`.overlay`, gated against level counts (app 17/1/28/2 + 26 devices;
     net 15/1/10 + 7 devices).
  3. **Pin the dynamic `k_thread_create` sites** inside the reconstructed main
     trees (entry/prio/stack/args): 16 app threads, 3 net (main + esbm + esbs).
     The 3 previously-missing app thread roots are resolved+PASS.
  Follow-up (does NOT block E4; SDK-region, not app-owned): 2 unresolved net POST
  init entries (runtime 0x0102e434, 0x01034934) need per-fn disassembly before a
  byte-exact net `.text` compare.
- **P3 — Image shaping**: partition layout app@0xC200/net@0x01008800; wire
  FORCEOFF release; add `.resc` that LoadELFs our build like `g1.resc`.
- **P4 — Differential bring-up** (iterate E1→E5, both cores): load our build,
  diff vs golden, fix FIRST divergence each round — classify as recon defect
  (→cfg_verify) / wiring gap (→init/priority) / config (→Kconfig/overlay) —
  rebuild, re-run. rpmsg handshake + net release + first advert + display init
  are the E4 milestones.
- **P5 — Parity report + fallback**: milestone diff vs original; unreconstructable
  leaves ship as byte-exact blobs so the system still boots.

## Acceptance
Our build, loaded into Renode, passes `g1-selfdrive.sh` through the display-START
/ ESB-sync gate — the same points the shipped image reaches.
