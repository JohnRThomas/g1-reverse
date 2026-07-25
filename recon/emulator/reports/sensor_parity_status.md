# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**Second measurement of `display_sensor_parity.md`'s criteria against our
rebuild** (iteration 15; the first was iteration 14). Iteration 15 removed the
`display_thread_handler` free-run that starved every sensor thread, so the
numbers below supersede the iteration-14 table.

* Oracle (diff target): `recon/emulator/reports/display_sensor_oracle.json`
  (shipped `app_update.bin` / `netcore_image.bin`), criteria in
  `recon/emulator/reports/display_sensor_parity.md` §5.
* Our build: **`/private/tmp/g1-i15e-app/zephyr/zephyr.elf`** (iteration 15
  final, app) + `/private/tmp/g1-i9c-net/zephyr/zephyr.elf` (net, unchanged
  since iteration 9).
* Captured under **identical determinism knobs and identical stimulus** to the
  oracle: global quantum `0.000010`, CC312 seed `0x5340CC3105340CC3`, serial
  core scheduling, 20.0 s virtual-time budget split 6 s (`p1_boot`) + 14 s
  (`p2_render`), `vcentral` sweep + NUS write, `esbslave`, `PlayGesture "don"`.
  Host cost of our run: 39 s.
* `armemul` is **untouched** this iteration (the two opt-in `TraceFile` hooks on
  `models/NRF5340_{SPIM,TWIM}.cs` were already present from the oracle capture).

## 1. Reproduce (exact commands)

```sh
cd /Users/freedomcoder/Projects/G1disasm2

# (a) OUR capture -- the oracle capture script, parameterised (iteration 14,
#     additive: with none of the G1_* variables set it behaves exactly as
#     before and captures the SHIPPED images).
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i15e-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i9c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_ours_i15e

# (b) build the same JSON from our capture, into a SCRATCH report dir so the
#     committed oracle is never overwritten
PYTHONSAFEPATH=1 .venv/bin/python \
  recon/emulator/scripts/build_display_sensor_oracle.py \
  /tmp/g1_ours_i15e <SCRATCH>/i15/rep_i15e

# (c) diff -- PER DEVICE, never the merged twim1 bus hash (three threads share
#     that bus; §2.1 of display_sensor_parity.md documents the nondeterminism)
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i14/diff_parity.py \
  <SCRATCH>/i15/rep_i15e/display_sensor_oracle.json
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i15/firstdiff.py
```

`G1_HOOKS=0` is required because the four `sysbus.cpuapp AddHook` PCs in the
oracle capture (`0x47724`, `0x2bc2c`, `0x2948c`, `0x3727c`) are
**ORIGINAL-image** addresses; our build relocates every one of them.
`G1_CTX_FE8` / `G1_CTX_105A` are the arena-relative equivalents of the
original's `device_ctx+0xfe8` / `+0x105a` (`g1_ram_arena` = `0x200030a0` in
this build, unchanged from iteration 14, arena origin `0x20002000`).

## 2. Per-criterion table (iteration 15 final, `g1-i15e-app`)

| id | criterion | verdict | vs iter 14 | evidence |
|---|---|---|---|---|
| **S-IMU** | `twim2` LSM6DSO stream hash per phase | **PARTIAL** | **35 → 969 txns** | `p1_boot` 969 txns vs oracle 1 089; first **3** transactions byte-identical, first difference still at txn **#3** (below). `p2_render` **0** txns (oracle 1 200). |
| **S-ALS** | `opt3001_ambient_light` stream hash | **PARTIAL (prefix-exact)** | unchanged | `p1_boot` 7 txns vs 33; **all 7 byte-identical to the oracle's first 7**, then ours stops. `p2_render` 0 vs 80. |
| **S-PMIC** | `npm1300_charger_fuelgauge` stream hash | **PARTIAL** | **54 → 85 txns** | `p1_boot` 85 txns vs oracle 291 (270 after the RLE collapse the first-difference view uses); still diverges at txn **#0**. `p2_render` 0 vs 508. |
| **S-NFC** | `st25dv_nfc_eeprom` + `st25dv_system_port` | **PARTIAL / NOT-EXERCISED** | unchanged | system port `p1_boot` 6 txns vs 22, **all 6 byte-identical**, then stops. NFC EEPROM (`0x53`) **0** txns vs 25 — never touched. |
| **S-ADC** | `saadc` whole-run stream hash | **PARTIAL (prefix-exact)** | unchanged | 5 register accesses vs 998; **all 5 byte-identical to the oracle's first 5** (`EVENTS_END` clear+read, `EVENTS_CALIBRATEDONE` clear+read, `INTENSET ← 0x12`), then the 2.25 Hz conversion cycle never runs. The run also logs `<err> adc_nrfx_saadc: Selected ADC gain is not valid` — a separate, newly visible devicetree/driver defect. |
| **S-KEYS** | `gpiote0` whole-run stream hash; `gpiote1` count == 0 | **PASS** | unchanged | `gpiote0` **stream_sha256 identical**, 25 accesses = 25. `gpiote1` accesses **0 == 0**. |
| **S-MIC** (negative) | `pdm0` == exactly 2 writes, no ENABLE/START | **PASS** | unchanged | `pdm0` **stream_sha256 identical**: `PSEL.CLK ← 0x2D`, `PSEL.DIN ← 0x2E`, and nothing else. |
| **gyro** (negative) | `CTRL2_G` stays 0 / gyro never enabled | **PASS** | unchanged | `sysbus.twim2.lsm6dso GyroscopeEnabled` = **False** at end of the 20 s run, matching the oracle. **Caveat:** `AccelerometerEnabled` is now **False** too (oracle **True**, iteration 14 ours **True**) — see §4. The negative criterion still holds, but it is now less informative. |
| **S-ESB** | ESB sync reaches 0x02, display-on 0x01, PTX > 0 | **FAIL (not reached)** | unchanged | `radio TransmittedFrames` = 0 (oracle 0x230), `esbslave MasterFramesSeen` = 0 (oracle 0x175), both context bytes read `0x00` (oracle `0x01` / `0x02`). |
| **G-1** | `framebuffer.p2_render.sha256` | **FAIL (not reached)** | unchanged | ours `0c5cc90b…` (all-zero panel, 0 lit px) vs oracle `b26c73b3…`, 1 098 lit px. |
| **G-2** | `framebuffer.p1_boot.sha256` | **FAIL (not reached)** | unchanged | ours `0c5cc90b…` (0 lit px) vs oracle `1d617c65…`, 656 lit px. |
| **G-3** | `spim_a` ordered byte stream per phase | **FAIL (not reached)** | unchanged | ours **0** SPI transactions in both phases (oracle 764 / 2 881). |
| **G-4** | *(localiser only)* first differing row | **n/a** | — | our framebuffer is uniformly zero; no row localises anything. |
| **G-5** | panel init: `0x9F`→`0x4010`, three-band 153 600 B clear, five `0xC0` words, `0x46`/`0x31` pairs `0F 04` / `00 04` | **UNTESTED (no SPI traffic at all)** | unchanged | `sysbus.spim_a.jbd FrameCounter` = 0 (oracle 0x2A1 / 0xD61), `JournalCount` = 0 (oracle 0x400), journal empty. **`jdb_panel_init`, `panel_init`, `spi_master_init` and `projector_reset_sequence` DO now execute** (iteration 15 §15.3), but `nrfx_spim_xfer` polls a SPIM instance whose `p_reg` is neither `spim_a` nor `spim_b` — measured with `sysbus LogPeripheralAccess`, **zero register accesses on both**. Nothing reached the panel model, so there is still nothing to compare. |
| **G-6** | `spim_b` transaction count == 0 | **PASS (vacuous)** | unchanged | ours 0 == oracle 0 — but our build drives *neither* SPI backend, so this passes for the wrong reason. |

Score: **3 PASS** (S-KEYS, S-MIC negative, gyro negative), **1 vacuous PASS**
(G-6), **5 PARTIAL** (S-IMU, S-ALS, S-PMIC, S-NFC, S-ADC), **1 FAIL** (S-ESB),
**3 NOT REACHED** (G-1, G-2, G-3), **1 UNTESTED** (G-5). Unchanged in
composition from iteration 14; the movement is *inside* S-IMU and S-PMIC.

## 3. First differences, with classification

### S-IMU — LSM6DSO on `twim2` (first divergence still at transaction #3)

```
#0  oracle W 0x6B 0100   ours W 0x6B 0100     FUNC_CFG_ACCESS(0x01) <- 0x00
#1  oracle W 0x6B 0F     ours W 0x6B 0F       WHO_AM_I(0x0F) address
#2  oracle R 0x6B 6C     ours R 0x6B 6C       -> 0x6C, accepted
#3  oracle W 0x6B 18     ours W 0x6B 0180  <<< FIRST DIFFERENCE
#4  oracle R 0x6B E0     ours W 0x6B 46
#5  oracle W 0x6B 18E2   ours R 0x6B 0000
#6  oracle W 0x6B 62     ours W 0x6B 0100
```

Identical to iteration 14's finding: after the WHO_AM_I handshake the original
does a read-modify-write of **`CTRL9_XL` (0x18)** (read `E0`, write `E2`, then
`0x62 ← 00`), while ours writes **`FUNC_CFG_ACCESS ← 0x80`** and reads `0x46`
(`FSM_ENABLE_A`) in the embedded-functions bank the original never enters.
What **changed** is the volume: 35 → **969** transactions, because the IMU
fusion thread is no longer starved. The wrong sequence now simply repeats.

**Classification: recon defect** (unchanged). Our `imu_fusion_init` reaches the
sensor through a `dev_api_call_slot0(dev, 3|7, …)` attr-set path that pulls in
`lsm6dso_mem_bank_set` / `lsm6dso_fsm_enable_get` / `lsm6dso_attr_set`; the
golden trace's only `lsm6dso_*` symbol is `lsm6dso_init_chip`. Not fixed this
iteration — it was not on the E4 critical path and the four defects that were
(iteration 15 §15.1–15.4) consumed the budget. Concrete next step unchanged:
re-derive `lsm6dso_init_chip` (0x2e5xx family) and the `dev_api_call_slot0`
dispatch against the shipped disassembly.

### S-PMIC — nPM1300 on `twim1` @0x6B (first divergence still at transaction #0)

```
#0  oracle W 0x6B 060206   ours W 0x6B 040F   <<< FIRST DIFFERENCE
#1  oracle W 0x6B 061600   ours R 0x6B 00
#2  oracle W 0x6B 060C00   ours W 0x6B 0410
#3  oracle W 0x6B 061100   ours R 0x6B 17
```

The original opens with a **bank-0x06 register-write burst** (`0x0602 ← 06`,
`0x0616 ← 00`, `0x060C ← 00`, `0x0611 ← 00` …, the GPIO / ship-mode block);
ours opens with **bank-0x04 register reads** (`0x040F`, `0x0410`). Same device,
same addressing, different init routine ordering.
**Classification: recon defect (init-sequence ordering)** — unchanged from
iteration 14. What **changed**: 54 → **85** transactions, and the *charger*
half of the PMIC init now actually runs (iteration 15 §15.3 fixed the
`-EINVAL`: `panel_temp_calibration_init` went from 4 entries / 63 instructions
to 20 / 197, against golden's 38 / 398). The remaining gap inside that function
is the next PMIC target.

### S-ALS, S-NFC (system port), S-ADC — prefix-exact, then stop

Byte-identical for every transaction our build makes, then they stop while the
oracle continues:

* OPT3001: identical through `MANUFACTURER_ID(0x7E)→5449`,
  `DEVICE_ID(0x7F)→3001`, `CONFIG(0x01)` read `C810`, `CONFIG ← CE10`.
  The oracle's txn #7 (`W 7E`, the second manufacturer-ID read that begins the
  polling loop) never happens in ours.
* ST25DV system port (`0x57`): identical through the 6th transaction
  (`W 0017` / `R 24`); the oracle's txn #6 (the 19-byte `0x0009…` config write)
  never happens.
* SAADC: identical through `INTENSET ← 0x12`; none of the conversion cycles
  (`CH3.PSELP ← 4`, `RESULT.PTR`, `TASKS_START/SAMPLE`) ever run.

**Classification: not-yet-reached** — but the *reason* has changed. In
iteration 14 they were starved by the display free-run. In iteration 15 the
periodic threads are reachable (`periodic_check_run` executed 9 times in
`g1-i15b` against golden's 32) and then the whole app blocks in the
`nrfx_spim_xfer` `EVENTS_END` poll (§4).

### S-NFC EEPROM (`0x53`) — not exercised

Zero transactions vs the oracle's 25 (`W 2004` first). The ST25DV user-memory
path (`st25dv_*`, `adc_nfc_run`) never executes.
**Classification: not-yet-reached.**

## 4. Why every device still goes silent after `p1_boot`

The iteration-14 cause (the `display_thread_handler` free-run) is **fixed and
measured gone**: `display_thread_handler` fell from 2 918 551 entries to 82,
`k_msgq_get` from 2 918 551 to 82, `wake_display_thread_on_reflash` from
729 636 to 19, and app instructions at 2.0 s from 195 865 770 to 10 157 310
(`g1-i15b`) against the golden trace's 12 629 795. Root cause: the whole
shipped `.data` section below 0x20003e29 was never loaded into the RAM arena —
see `our_boot_bringup.md` §15.1.

The **new** blocker in the final build is a busy-wait, not a free-run:

| function | ours @2.0 s (entries / instr) | golden |
|---|---:|---:|
| `nrfx_spim_xfer` | 247 / **187 696 414** | 170 / 3 774 |
| `nrfx_spim_init` | 3 / 24 | 3 / 24 |
| `spim_select_instance_by_mode` | **absent** | 2 / 42 |
| `nrfx_spim_uninit` | **absent** | 8 / 43 |
| `projector_send_cmd_immediate` | **absent** | 90 / 360 |

The hot PCs are `ldr r3,[r4,#0x118] ; cmp r3,#0 ; beq .-6` — polling
`EVENTS_END` after writing `TASKS_START`. `spim_select_instance_by_mode`
(0x26338), the function that installs the SPIM base (`mode == 3 → 0x5000c000`
= `spim_b`, `mode == 4 → 0x5000a000` = `spim_a`), never runs in our build, so
the `nrfx_spim_t` handed to `nrfx_spim_xfer` still has an uninitialised
`p_reg`. That is the next first divergence and it is what keeps `p2_render`
empty on every device, `IMU_ACCEL_ENABLED` at `False`, and G-1/G-2/G-3/G-5
unreachable.

For reference, the intermediate build `g1-i15b-app` (free-run fix + `sqrtf_hw`
fix only, without the three E4-path fixes) reaches **917 unique functions /
10 157 310 instructions / 0 resets at 2.0 s** — the best aggregate of the
iteration. `g1-i15e-app` is kept as the final build anyway because its three
extra fixes are each proven against the shipped disassembly (one byte-exactly)
and each turns on a golden-trace function; see `our_boot_bringup.md` §15
"On the final-build regression".

## 5. Honest summary

* **3 criteria pass outright**: S-KEYS, S-MIC (negative), gyro (negative) — by
  exact stream-hash / model-flag equality, not by inspection.
* **1 passes vacuously**: G-6 (`spim_b` == 0), because our build drives no SPI
  display backend at all.
* **5 are partial.** Three of the five (S-ALS, S-NFC system port, S-ADC) are
  **byte-exact for every transaction we emit** — the divergence is that we
  stop, not that we are wrong. Two (S-IMU, S-PMIC) diverge inside the init
  sequence itself and are genuine recon defects with a named first-differing
  register; both moved substantially this iteration (S-IMU 35 → 969
  transactions, S-PMIC 54 → 85) without their first-difference index changing.
* **G-1/G-2/G-3/G-5 are still not reached**: **zero** display SPI transactions
  in 20 s of virtual time, so the panel-init comparison the oracle pins (the
  `0x9F`→`0x4010` probe, the three-band 153 600 B clear, the five `0xC0` words,
  the `0F 04` / `00 04` brightness pairs) has nothing to be compared against.
  Reported as *untested*, not as *failed*. Progress is real but partial:
  `jdb_panel_init`, `panel_init`, `spi_master_init` and
  `projector_reset_sequence` execute for the first time.
* **S-ESB fails**: `radio TransmittedFrames` = 0.
