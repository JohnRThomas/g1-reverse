# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**First real measurement of `display_sensor_parity.md`'s criteria against our
rebuild.** Iteration 13 produced the first LSM6DSO bus traffic but never
evaluated a single criterion; this file is the evaluation.

* Oracle (diff target): `recon/emulator/reports/display_sensor_oracle.json`
  (shipped `app_update.bin` / `netcore_image.bin`), criteria in
  `recon/emulator/reports/display_sensor_parity.md` §5.
* Our build: `/private/tmp/g1-i14b-app/zephyr/zephyr.elf` (iteration 14 final,
  app) + `/private/tmp/g1-i9c-net/zephyr/zephyr.elf` (net, unchanged since
  iteration 9).
* Captured under **identical determinism knobs and identical stimulus** to the
  oracle: global quantum `0.000010`, CC312 seed `0x5340CC3105340CC3`, serial
  core scheduling, 20.0 s virtual-time budget split 6 s (`p1_boot`) + 14 s
  (`p2_render`), `vcentral` sweep + NUS write, `esbslave`, `PlayGesture "don"`.
  Host cost of our run: 100.6 s.
* The `armemul` `TraceFile` hooks on `models/NRF5340_{SPIM,TWIM}.cs` were
  **already present and unmodified** (`git diff --stat` in `../armemul`:
  `NRF5340_SPIM.cs +56`, `NRF5340_TWIM.cs +52`, 0 removed). Nothing had to be
  re-added, and nothing in `armemul` was changed this iteration.

## 1. Reproduce (exact commands)

```sh
cd /Users/freedomcoder/Projects/G1disasm2

# (a) OUR capture -- the oracle capture script, parameterised (iteration 14,
#     additive: with none of the G1_* variables set it behaves exactly as
#     before and captures the SHIPPED images).
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i14b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i9c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_ours_i14b

# (b) build the same JSON from our capture, into a SCRATCH report dir so the
#     committed oracle is never overwritten
PYTHONSAFEPATH=1 .venv/bin/python \
  recon/emulator/scripts/build_display_sensor_oracle.py \
  /tmp/g1_ours_i14b <SCRATCH>/ours_reports

# (c) diff -- PER DEVICE, never the merged twim1 bus hash (three threads share
#     that bus; §2.1 of display_sensor_parity.md documents the nondeterminism)
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i14/diff_parity.py
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i14/firstdiff.py
```

`G1_HOOKS=0` is required because the four `sysbus.cpuapp AddHook` PCs in the
oracle capture (`0x47724`, `0x2bc2c`, `0x2948c`, `0x3727c`) are
**ORIGINAL-image** addresses; our build relocates every one of them.
`G1_CTX_FE8` / `G1_CTX_105A` are the arena-relative equivalents of the
original's `device_ctx+0xfe8` / `+0x105a`
(`g1_ram_arena` = `0x200030a0` in this build, arena origin `0x20002000`).

## 2. Per-criterion table

| id | criterion | verdict | evidence |
|---|---|---|---|
| **S-IMU** | `twim2` LSM6DSO stream hash per phase | **PARTIAL** | `p1_boot` 35 txns vs oracle 1 089; first **3** transactions byte-identical, first difference at txn **#3** (below). `p2_render` **0** txns (oracle 1 200). |
| **S-ALS** | `opt3001_ambient_light` stream hash | **PARTIAL (prefix-exact)** | `p1_boot` 7 txns vs 33; **all 7 byte-identical to the oracle's first 7**, then ours stops. `p2_render` 0 vs 80. |
| **S-PMIC** | `npm1300_charger_fuelgauge` stream hash | **PARTIAL** | `p1_boot` 54 txns vs 270; diverges at txn **#0**. `p2_render` 0 vs 508. |
| **S-NFC** | `st25dv_nfc_eeprom` + `st25dv_system_port` | **PARTIAL / NOT-EXERCISED** | system port `p1_boot` 6 txns vs 22, **all 6 byte-identical**, then stops. NFC EEPROM (`0x53`) **0** txns vs 25 — never touched. |
| **S-ADC** | `saadc` whole-run stream hash | **PARTIAL (prefix-exact)** | 5 register accesses vs 998; **all 5 byte-identical to the oracle's first 5** (`EVENTS_END` clear+read, `EVENTS_CALIBRATEDONE` clear+read, `INTENSET ← 0x12`), then the 2.25 Hz conversion cycle never runs. |
| **S-KEYS** | `gpiote0` whole-run stream hash; `gpiote1` count == 0 | **PASS** | `gpiote0` **stream_sha256 identical**, 25 accesses = 25; `CONFIG[7]=0x22901`, `CONFIG[6]=0x22A01`, `INTENSET` `0x80000000`/`0x80`/`0x40` all reproduced. `gpiote1` accesses **0 == 0**. |
| **S-MIC** (negative) | `pdm0` == exactly 2 writes, no ENABLE/START | **PASS** | `pdm0` **stream_sha256 identical**: `PSEL.CLK ← 0x2D`, `PSEL.DIN ← 0x2E`, and nothing else. No `ENABLE`, no `TASKS_START`, no DMA. |
| **gyro** (negative) | `CTRL2_G` stays 0 / gyro never enabled | **PASS** | `sysbus.twim2.lsm6dso GyroscopeEnabled` = **False** at end of the 20 s run (accel `AccelerometerEnabled` = True). |
| **S-ESB** | ESB sync reaches 0x02, display-on 0x01, PTX > 0 | **FAIL (not reached)** | `radio TransmittedFrames` = 0, `esbslave MasterFramesSeen` = 0, both context bytes read `0x00`. Our build still emits no radio traffic (E4 blocker). |
| **G-1** | `framebuffer.p2_render.sha256` | **FAIL (not reached)** | ours `0c5cc90b…` (all-zero panel, 0 lit px) vs oracle `b26c73b3…`, 1 098 lit px. |
| **G-2** | `framebuffer.p1_boot.sha256` | **FAIL (not reached)** | ours `0c5cc90b…` (0 lit px) vs oracle `1d617c65…`, 656 lit px. |
| **G-3** | `spim_a` ordered byte stream per phase | **FAIL (not reached)** | ours **0** SPI transactions in both phases (oracle 764 / 2 881). |
| **G-4** | *(localiser only)* first differing row | **n/a** | our framebuffer is uniformly zero; no row localises anything. |
| **G-5** | panel init: `0x9F`→`0x4010`, three-band 153 600 B clear, five `0xC0` words, `0x46`/`0x31` pairs `0F 04` / `00 04` | **UNTESTED (no SPI traffic at all)** | `sysbus.spim_a.jbd FrameCounter` = 0, `JournalCount` = 0, journal empty. Not a single opcode reached the panel model, so there is nothing to compare. `spi_read_id` / `jdb_panel_init` / `panel_on` / `panel_resume` are absent from the execution trace. |
| **G-6** | `spim_b` transaction count == 0 | **PASS (vacuous)** | ours 0 == oracle 0 — but our build drives *neither* SPI backend, so this passes for the wrong reason. Recorded as passing, flagged as uninformative until G-3 produces traffic. |

## 3. First differences, with classification

### S-IMU — LSM6DSO on `twim2` (first divergence at transaction #3)

```
#0  oracle W 0x6B 0100   ours W 0x6B 0100     FUNC_CFG_ACCESS(0x01) <- 0x00
#1  oracle W 0x6B 0F     ours W 0x6B 0F       WHO_AM_I(0x0F) address
#2  oracle R 0x6B 6C     ours R 0x6B 6C       -> 0x6C, accepted
#3  oracle W 0x6B 18     ours W 0x6B 0180  <<< FIRST DIFFERENCE
#4  oracle R 0x6B E0     ours W 0x6B 46
#5  oracle W 0x6B 18E2   ours R 0x6B 0000
#6  oracle W 0x6B 62     ours W 0x6B 0100
```

After the identical WHO_AM_I handshake the original does a read-modify-write of
**`CTRL9_XL` (0x18)**: read `E0`, write back `E2`, then `0x62 ← 00` — the stock
`lsm6dso_init_chip` sequence. Ours instead writes **`FUNC_CFG_ACCESS(0x01) ←
0x80`**, i.e. `lsm6dso_mem_bank_set` switching into the *embedded-functions*
bank, and then reads register `0x46` (`FSM_ENABLE_A`) — a bank the original
never enters in this scenario.

**Classification: recon defect** (not an unrelocated pin, not "not yet
reached"). Corroborated by the execution traces: the golden trace's only
`lsm6dso_*` symbol is `lsm6dso_init_chip` (37 entries) and it contains
**no** `lsm6dso_mem_bank_set` / `lsm6dso_fsm_enable_get` / `lsm6dso_attr_set`
entries at all, whereas ours runs `lsm6dso_mem_bank_set` 16×,
`lsm6dso_fsm_enable_get` 16×, `lsm6dso_attr_set` 8× and only 6×
`lsm6dso_init_chip`. Our `imu_fusion_init` (reconstructed in iteration 13)
reaches the sensor through a `dev_api_call_slot0(dev, 3|7, …)` attr-set path
that pulls in the FSM/bank helpers; the original's path does not. The concrete
next step is to re-derive `lsm6dso_init_chip` (0x2e5xx family) and the
`dev_api_call_slot0` dispatch against the shipped disassembly.

### S-PMIC — nPM1300 on `twim1` @0x6B (first divergence at transaction #0)

```
#0  oracle W 0x6B 060206   ours W 0x6B 040F   <<< FIRST DIFFERENCE
#1  oracle W 0x6B 061600   ours R 0x6B 00
#2  oracle W 0x6B 060C00   ours W 0x6B 0410
#3  oracle W 0x6B 061100   ours R 0x6B 17
```

The original opens with a **bank-0x06 register-write burst**
(`0x0602 ← 06`, `0x0616 ← 00`, `0x060C ← 00`, `0x0611 ← 00` …, the GPIO /
ship-mode block); ours opens with **bank-0x04 register reads** (`0x040F`,
`0x0410`). Same device, same addressing, different init routine ordering.
**Classification: recon defect (init-sequence ordering)** — both firmwares are
talking to the PMIC correctly at the bus level, so this is not a pin or a
device-model problem.

### S-ALS, S-NFC (system port), S-ADC — prefix-exact, then stop

These three are **byte-identical for every transaction our build makes** and
then simply stop while the oracle continues:

* OPT3001: identical through `MANUFACTURER_ID(0x7E)→5449`,
  `DEVICE_ID(0x7F)→3001`, `CONFIG(0x01)` read `C810`, `CONFIG ← CE10`.
  The oracle's txn #7 (`W 7E`, the second manufacturer-ID read that begins the
  polling loop) never happens in ours.
* ST25DV system port (`0x57`): identical through the 6th transaction
  (`W 0017` / `R 24`); the oracle's txn #6 (the 19-byte `0x0009…` config write)
  never happens.
* SAADC: identical through `INTENSET ← 0x12`; none of the 45 conversion cycles
  (`CH3.PSELP ← 4`, `RESULT.PTR`, `TASKS_START/SAMPLE`) ever run.

**Classification: not-yet-reached.** The init half is reproduced exactly; the
periodic half is gated behind threads that our boot never gets to
(`periodic_check_run`, `adc_nfc_run`, `check_work_mode` are all present in the
golden trace and absent from ours). This is the same starvation that produces
**zero** `p2_render` traffic on every I²C device — see §4.

### S-NFC EEPROM (`0x53`) — not exercised

Zero transactions vs the oracle's 25 (`W 2004` first). The ST25DV user-memory
path (`st25dv_*`, `adc_nfc_run`) never executes.
**Classification: not-yet-reached.**

## 4. Why every device goes silent after `p1_boot`

Our `p2_render` phase has **0 transactions on every I²C device** and 0 SPI
transactions. The cause is measured, not assumed: the app core executes
**195 865 770 instructions in 2.0 s** against the golden trace's **12 629 795**
— a 15× overrun — and the profile is dominated by one loop:

| function | our entries / instr @2.0 s | golden entries / instr |
|---|---:|---:|
| `display_thread_handler` | 2 918 551 / 26 996 542 | 178 / 2 033 |
| `k_msgq_get` | 2 918 551 / 25 537 257 | 182 / 1 597 |
| `wake_display_thread_on_reflash` | 729 636 / 4 377 810 | 43 / 258 |
| `memset` (+`memset_bytes`) | 729 885 / 74 571 528 | — |

`display_thread_handler` (original 0x49090) computes its `k_msgq_get` timeout as
`(clamp0(g_dashboard_display_level) * 0x8000 + 999) / 1000` ticks — our emitted
frame is instruction-for-instruction the original's, including the `smlal` /
`__aeabi_uldivmod` pair — and `g_dashboard_display_level` (original
`0x20002544`, correctly bound to `g1_ram_arena + 0x544`) is **0** in our build,
so the timeout is `K_NO_WAIT` and the thread free-runs, clearing the canvas
every iteration and starving every sensor thread. The only writer of that
global, `set_dashboard_display_level_clamped` (0x48b44), never executes in
*either* trace, so the non-zero value the original has must arrive from the
settings store or from a `.data` initialiser we have not reproduced. **That is
the next first divergence.**

## 5. Honest summary

* **3 criteria pass outright**: S-KEYS, S-MIC (negative), gyro (negative) — all
  three by exact stream-hash / model-flag equality, not by inspection.
* **1 passes vacuously**: G-6 (`spim_b` == 0), because our build drives no SPI
  display backend at all.
* **5 are partial**: S-IMU, S-ALS, S-PMIC, S-NFC, S-ADC. Three of those five
  (S-ALS, S-NFC system port, S-ADC) are **byte-exact for every transaction we
  emit** — the divergence is that we stop, not that we are wrong. Two (S-IMU,
  S-PMIC) diverge inside the init sequence itself and are genuine recon
  defects with a named first-differing register.
* **G-1/G-2/G-3/G-5 are not reached**: our firmware produced **zero** display
  SPI transactions in 20 s of virtual time, so the panel-init comparison the
  oracle pins (the `0x9F`→`0x4010` probe, the three-band 153 600 B clear, the
  five `0xC0` words, the `0F 04` / `00 04` brightness pairs) has nothing to be
  compared against. Reported as *untested*, not as *failed*.
* **S-ESB fails**: `radio TransmittedFrames` = 0.
