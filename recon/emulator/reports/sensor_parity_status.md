# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**Fifth measurement of `display_sensor_parity.md`'s criteria against our
rebuild** (iteration 18; previous measurements were iterations 14, 15, 16 and
17). Iteration 18 fixed the **CPUNET blocker** named in iteration 17: the
`rpmsg_get_endpoint` spin is gone (net instructions at 2.0 s fall from
**53,529,158 to 412,379**) and the app core's `ipc_service: Endpoint not
registered` / `bt_hci_driver: Failed to send (err -2)` pair no longer appears in
the 6.0 s UART log — measured, not inferred (1 occurrence in
`/tmp/g1_i17d6/uart_app.log`, **0** in `/tmp/g1_i18e6/uart_app.log`).

**The graphics and sensor numbers below are, however, UNCHANGED from iteration
17, and that is reported plainly rather than dressed up.** The app binary is
unchanged (`g1-i17d-app`), and the app core still resets at exactly
**t = 5.093 s**, before any BLE connection — now on a *different*, deeper
assertion (§4). No pixel was painted.

* Oracle (diff target): `recon/emulator/reports/display_sensor_oracle.json`
  (shipped `app_update.bin` / `netcore_image.bin`), criteria in
  `recon/emulator/reports/display_sensor_parity.md` §5.
* Our build: **`/private/tmp/g1-i17d-app/zephyr/zephyr.elf`** (app, unchanged
  since iteration 17) + **`/private/tmp/g1-i18e-net/zephyr/zephyr.elf`** (net,
  rebuilt this iteration — see `our_boot_bringup.md` §18).
* Captured under **identical determinism knobs and identical stimulus** to the
  oracle: global quantum `0.000010`, CC312 seed `0x5340CC3105340CC3`, serial
  core scheduling, 20.0 s virtual-time budget split 6 s (`p1_boot`) + 14 s
  (`p2_render`), `vcentral` sweep + NUS write, `esbslave`, `PlayGesture "don"`.
  **No memory was poked**; the harness drove the same BLE stimulus the oracle
  capture used.
* `armemul` is **untouched** this iteration.

## 1. Reproduce (exact commands)

```sh
cd /Users/freedomcoder/Projects/G1disasm2

# (a) OUR capture -- the oracle capture script, parameterised
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i17d-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i18e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_ours_i18e

# (b) build the same JSON from our capture, into a SCRATCH report dir
PYTHONSAFEPATH=1 .venv/bin/python \
  recon/emulator/scripts/build_display_sensor_oracle.py \
  /tmp/g1_ours_i18e <SCRATCH>/i18/rep_i18e

# (c) diff -- PER DEVICE, never the merged twim1 bus hash
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i14/diff_parity.py \
  <SCRATCH>/i18/rep_i18e/display_sensor_oracle.json
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i18/firstdiff.py

# (d) G-3 / G-5: ordered spim_a transaction diff vs the oracle trace
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i16/g5diff.py \
  <SCRATCH>/g1_oracle/spim_a.p1.trace /tmp/g1_ours_i18e/spim_a.p1.trace
```

`G1_HOOKS=0` is required because the four `sysbus.cpuapp AddHook` PCs in the
oracle capture are **ORIGINAL-image** addresses; our build relocates them.
`G1_CTX_FE8` / `G1_CTX_105A` are the arena-relative equivalents of the
original's `device_ctx+0xfe8` / `+0x105a` (`g1_ram_arena` = `0x200030a0` in this
build, arena origin `0x20002000` — unchanged since iteration 14).

> **Our capture still dies at t = 5.093 s, inside `p1_boot`.** The app core
> takes a `ZEPHYR FATAL ERROR 4` there (§4) and Renode's nRF5340 platform has no
> reset macro, so both cores halt. **That is why every `p2_render` column below
> is zero**, and why the end-of-run `spim_a.jbd FrameCounter` reads 0. The
> ordered transaction logs (`*.p1.trace`) are the authority for §2's rows. The
> 2.0 s boot run (`/tmp/g1_i18e`) is **reset-free on both cores**.

## 2. Per-criterion table (iteration 18, `g1-i17d-app` + `g1-i18e-net`)

| id | criterion | verdict | vs iter 17 | evidence |
|---|---|---|---|---|
| **S-IMU** | `twim2` LSM6DSO stream hash per phase | **PARTIAL** | unchanged (983 txns) | `p1_boot` 983 txns vs oracle 1,089; first **3** transactions byte-identical, first difference still at txn **#3**. `p2_render` 0 (oracle 1,200). |
| **S-ALS** | `opt3001_ambient_light` stream hash | **PARTIAL (prefix-exact)** | unchanged (14 txns) | `p1_boot` 14 txns vs 33; **all 14 byte-identical to the oracle's first 14**, then ours simply stops. `p2_render` 0 vs 80. |
| **S-PMIC** | `npm1300_charger_fuelgauge` stream hash | **PARTIAL** | unchanged (199 txns) | `p1_boot` 199 raw / 186 RLE vs oracle 291 / 270; still diverges at txn **#0** (`W 060206` vs ours `W 040F`). `p2_render` 0 vs 508. |
| **S-NFC** | `st25dv_nfc_eeprom` + `st25dv_system_port` | **PARTIAL** | unchanged | NFC EEPROM (0x53) **11** txns vs 25, **first 6 byte-identical**, first difference at **#6** (`W 200200` vs ours `W 200258`). System port (0x57) **12** vs 22, **first 10 byte-identical**, first difference at **#10** (`W 0001` vs ours `W 000101`). |
| **S-ADC** | `saadc` whole-run stream hash | **PARTIAL (prefix-exact)** | unchanged (17 accesses) | first **5** register accesses byte-identical (`EventsEnd`, `EventsCalibrateDone`, `INTENSET ← 0x12`), first difference at **#5**: the oracle writes `CH[3].CONFIG` (0x548 ← 0x20000) while ours goes straight to `CH[0].PSELP`. The UART confirms it: `<err> adc_nrfx_saadc: Channel 3 not configured`. 17 vs 998. |
| **S-KEYS** | `gpiote0` whole-run stream hash; `gpiote1` count == 0 | **PASS** | unchanged | `gpiote0` **stream_sha256 identical**, 25 accesses = 25. `gpiote1` **0 == 0**. |
| **S-MIC** (negative) | `pdm0` == exactly 2 writes, no ENABLE/START | **PASS** | unchanged | `pdm0` **stream_sha256 identical**, 2 == 2. |
| **gyro** (negative) | `CTRL2_G` stays 0 / gyro never enabled | **PASS (weak)** | unchanged | `GyroscopeEnabled` = **False**, matching the oracle (also False). **Caveat unchanged:** `AccelerometerEnabled` is also **False** in both, so the criterion holds but is not discriminating. |
| **S-ESB** | ESB sync reaches 0x02, display-on 0x01, PTX > 0 | **FAIL (not reached)** | unchanged | `radio TransmittedFrames` = 0 (oracle 0x230), `esbslave MasterFramesSeen` = 0 (oracle 0x175), `vcentral Connected` = **False** (oracle True), `vcentral ConnectIndsSent` = 0, both context bytes `0x00` (oracle `0x01` / `0x02`). The net-core half of the root cause is fixed (§4); the app-core half is not. |
| **G-1** | `framebuffer.p2_render.sha256` | **FAIL** | unchanged | ours `0c5cc90b…`, **0 lit px**; oracle `b26c73b3…`, **1,098 lit px**. |
| **G-2** | `framebuffer.p1_boot.sha256` | **FAIL** | unchanged | ours `0c5cc90b…`, **0 lit px**; oracle `1d617c65…`, **656 lit px**. |
| **G-3** | `spim_a` ordered byte stream per phase | **FAIL (truncation only)** | unchanged (34 txns) | `p1_boot` ours sha `f40cbd5d…` vs oracle `b64599b1…`, **34 vs 764** transactions. **All 34 shared transactions are byte-identical**; the first difference is at index **34**, where the oracle emits `0x66 tx=66` and we emit nothing. `p2_render` 0 vs 2,881. |
| **G-4** | *(localiser only)* first differing row | **localised (unchanged)** | our framebuffer bytes are **bit-identical to iterations 16 and 17** (`0c5cc90b…`) | first differing row **y = 267**, first differing pixel **x = 178** (oracle `ffffff`, ours `000000`) — the top-left of the oracle's lit bbox (178,267)–(449,287). Not re-derived this iteration: the sha is bit-identical, so the result carries over. |
| **G-5** | panel init: `0x9F`→`0x4010`, three-band 153 600 B clear, five `0xC0` words, `0x46`/`0x31` pairs `0F 04` / `00 04` | **PASS** | unchanged | all four enumerated elements byte-exact, including the trailing `0xB9 FF` at index 33. The whole `display_sensor_parity.md` §3.1 block is reproduced. |
| **G-6** | `spim_b` transaction count == 0 | **PASS** | unchanged | ours 0 == oracle 0, hash EQ, and we genuinely drive `spim_a`. |

Score: **5 PASS** (S-KEYS, S-MIC, gyro-negative, G-5, G-6), **5 PARTIAL**
(S-IMU, S-ALS, S-PMIC, S-NFC, S-ADC), **4 FAIL** (S-ESB, G-1, G-2, G-3) —
**identical to iteration 17 in every cell.** Iteration 18's work was entirely on
the net core and moved the boot blocker one call deeper (§4) without yet
reaching the BLE link that gates the painting path.

## 3. `p1_boot` transaction volumes (unchanged: same app binary, same reset time)

| device | oracle | `g1-i15e` | `g1-i16b` | `g1-i17d` | **iter 18** |
|---|---:|---:|---:|---:|---:|
| `twim2` LSM6DSO (0x6B) | 1,089 | 969 | 25 | 983 | **983** |
| `twim1` nPM1300 (0x6B) | 291 | 85 | 85 | 199 | **199** |
| `twim1` OPT3001 (0x45) | 33 | 7 | 7 | 14 | **14** |
| `twim1` ST25DV system port (0x57) | 22 | 6 | 6 | 12 | **12** |
| `twim1` ST25DV NFC EEPROM (0x53) | 25 | 0 | 0 | 11 | **11** |
| `saadc` register accesses (whole run) | 998 | — | 5 | 17 | **17** |
| `gpiote0` register accesses (whole run) | 25 | — | 25 | 25 | **25** (hash EQ) |
| `pdm0` register accesses (whole run) | 2 | — | 2 | 2 | **2** (hash EQ) |
| `spim_a` | 764 | 0 | 33 | 34 | **34** |
| `spim_b` | 0 | 0 | 0 | 0 | **0** (hash EQ) |

Every `p2_render` column is **0** in all of our builds, because the app core
resets inside `p1_boot`.

## 4. The blocker moved: the CPUNET half is FIXED, the app-core half is not

### 4.1 What iteration 18 fixed (net core)

Iteration 17 reported the net core burning **53,146,996 of 53,529,158
instructions (99.3 %)** in a non-terminating `metal_list_for_each` inside
`rpmsg_get_endpoint`, so the app's HCI endpoint never bound. That is fixed:

| | iter 17 (`g1-i9c-net`) | **iter 18 (`g1-i18e-net`)** |
|---|---:|---:|
| net instructions @2.0 s | 53,529,158 | **412,379** |
| net unique functions @2.0 s | 467 | **466** |
| top consumer | `rpmsg_get_endpoint` 53,146,996 | `memset` 139,562 (`rpmsg_get_endpoint` not in the top 12) |
| `ipc_service: Endpoint not registered` in the 6 s app UART | **1** | **0** |
| SoC resets @2.0 s | 0 | **0** |

**The iteration-17 hypothesis (an uninitialised shipped `.data` list head) was
wrong.** Dumped at 2.0 s, `rdev->endpoints` was a correct, self-consistent list
head; the damage was to a node *inside* the list. Two Renode watchpoints named
the writer as the reconstruction of `z_add_timeout`, whose `timeout_list` pin
0x21000750 lands inside `_sw_isr_table` in the cohesive link — the CPUNET
counterpart of the **app-core RAM-pin collision class** (iterations 10/11), not
of the `.data` class. Five defects were fixed; full evidence, measurements and
bisect ledger are in `our_boot_bringup.md` §18.

### 4.2 The app core's new first divergence — same instant, one call deeper

```
                                            (iteration 17)
[00:00:05.093,139] <err> ipc_service: Endpoint not registered
[00:00:05.093,139] <err> bt_hci_driver: Failed to send (err -2)
ASSERTION FAIL [buf] @ WEST_TOPDIR/zephyr/subsys/net/buf.c:467

                                            (iteration 18 — those two <err>
                                             lines are GONE)
ASSERTION FAIL [net_buf_simple_headroom(buf) >= len]
               @ WEST_TOPDIR/zephyr/subsys/net/buf_simple.c:301
<err> os: Faulting instruction address (r15/pc): 0x0007b45c   r14/lr: 0x0005f1a3
<err> os: >>> ZEPHYR FATAL ERROR 4: Kernel panic on CPU 0
<err> fatal_error: Resetting system
```

Resolved against `g1-i17d-app`: `0x0007b45c = assert_post_action+0xc`,
`0x0005f1a3 = net_buf_simple_push+0x27`, callers `bt_rpmsg_send` (0x0005fd58)
and `ble_work_thread` (0x0001f52c). `bt_rpmsg_send` prepends the one-byte H:4
packet indicator with `net_buf_push_u8()` and the buffer it is handed has **no
headroom**, although `CONFIG_BT_HCI_RESERVE = 1` and `CONFIG_BT_RPMSG = 1` are
both set in the app build's `autoconf.h`. The TX buffer therefore does not come
from a `BT_BUF_RESERVE`-reserving allocation. That is an **app-core** defect and
the next thing to fix.

### 4.3 Why that still stops the painting

Unchanged and still the operative fact: the oracle's own `spim_a.p1.trace` has
**no SPI activity between tick 1.21e8 (0.121 s) and 3.92e9 (3.92 s)**, and every
transaction after index 33 is downstream of the BLE link:

```
ORACLE spi_read_id                         (t ~ 0.12 s)   <- we reach this
ORACLE display_START action=0              (t ~ 0.12 s)   <- we reach this
ORACLE display_START action=1              (after BLE connect)
ORACLE BLIT notify_display_mode screen=10  x many         <- the pixel windows
```

Transactions 34–65 are a **second full panel init** and 66+ are the pixel
windows (219-byte `0x02` chunks). Our display driver reproduces the oracle
byte-for-byte for everything it is asked to do — `nrfx_spim_xfer` 170 / 3,774,
`nrfx_spim_uninit` 8 / 43, `spi_master_trans_data_tx_rx` 68 / 714 and
`panel_init` 20 / 52 all **match golden exactly** — it is simply never asked to
paint.

## 5. First differences that are genuine recon defects

### S-IMU — LSM6DSO on `twim2` (first divergence still at transaction #3)

```
#0  oracle W 0x6B 0100   ours W 0x6B 0100     FUNC_CFG_ACCESS(0x01) <- 0x00
#1  oracle W 0x6B 0F     ours W 0x6B 0F       WHO_AM_I(0x0F) address
#2  oracle R 0x6B 6C     ours R 0x6B 6C       -> 0x6C, accepted
#3  oracle W 0x6B 18     ours W 0x6B 0180  <<< FIRST DIFFERENCE
#4  oracle R 0x6B E0     ours W 0x6B 46
#5  oracle W 0x6B 18E2   ours R 0x6B 0000
```

Unchanged from iterations 14–18: the original does a read-modify-write of
**`CTRL9_XL` (0x18)** inside `lsm6dso_init_chip`, while ours writes
**`FUNC_CFG_ACCESS ← 0x80`** and reads `0x46` (`FSM_ENABLE_A`) in an
embedded-functions bank the original never enters, via `mem_bank_set` /
`fsm_enable_get` / `attr_set`. **Classification: recon defect. Not fixed this
iteration.**

### S-PMIC — nPM1300 on `twim1` @0x6B (first divergence still at transaction #0)

```
#0  oracle W 0x6B 060206   ours W 0x6B 040F   <<< FIRST DIFFERENCE
#1  oracle W 0x6B 061600   ours R 0x6B 00
#2  oracle W 0x6B 060C00   ours W 0x6B 0410
```

The original opens with a **bank-0x06 register-write burst** (GPIO / ship-mode);
ours opens with **bank-0x04 register reads**. **Classification: recon defect
(init-sequence ordering). Not fixed this iteration.**

### S-NFC — first-difference registers (unchanged since iteration 17)

```
st25dv_nfc_eeprom (0x53)
  #5  oracle R 0x53 00       ours R 0x53 00
  #6  oracle W 0x53 200200   ours W 0x53 200258   <<< FIRST DIFFERENCE
st25dv_system_port (0x57)
  #9   oracle R 0x57 00      ours R 0x57 00
  #10  oracle W 0x57 0001    ours W 0x57 000101   <<< FIRST DIFFERENCE
```

Both are read-modify-write sequences where the value we write back differs.
**Classification: recon defect, newly reachable.** These are the first-ever
measurements of this device pair beyond the handshake.

### S-ADC — new named defect

The oracle configures **`CH[3]`** (`0x548 ← 0x20000`) before touching `CH[0]`;
we skip it and the driver logs `adc_nrfx_saadc: Channel 3 not configured`.
**Classification: recon defect (missing channel configuration).**

## 6. Honest summary

* **The CPUNET blocker is fixed and measured.** `rpmsg_get_endpoint` no longer
  spins (53,529,158 → **412,379** net instructions at 2.0 s), the HCI endpoint
  binds, and `ipc_service: Endpoint not registered` is gone from the 6.0 s UART
  log (1 occurrence before, **0** after). Both cores boot reset-free through
  2.0 s.
* **The iteration-17 root-cause hypothesis was wrong and is corrected here.**
  It was not a missing net `.data` image; it was a raw original-image RAM pin
  (`timeout_list` = 0x21000750) landing inside `_sw_isr_table`, plus three
  `k_thread` objects landing inside `backend_data_0`. No
  `gen_net_data_image.py` was written, because the evidence said it would not
  have helped.
* **BLE still does NOT advertise or connect.** `radio TransmittedFrames` = 0,
  `vcentral Connected` = False, `esbslave MasterFramesSeen` = 0. The boot now
  stops on an **app-core** `net_buf_simple_push` headroom assertion inside
  `bt_rpmsg_send` at the same t = 5.093 s (§4.2).
* **No pixel was painted, and no graphics or sensor number changed.** G-1/G-2
  remain 0 lit px vs the oracle's 656 / 1,098; G-3 remains 34 of 764
  transactions with the whole 34-transaction prefix byte-identical and the first
  difference at index 34; G-5 and G-6 still **PASS**. The framebuffer sha is
  bit-identical to iterations 16 and 17, so G-4's localisation (row y = 267,
  pixel x = 178) carries over unchanged rather than being re-derived.
* **Score unchanged: 5 PASS / 5 PARTIAL / 4 FAIL.** Iteration 18 bought no
  parity cell; it bought the blocker that gated all of them being moved one
  call deeper, onto the app core.
* **Next**: the `bt_rpmsg_send` headroom defect (§4.2), then the 49 remaining
  live-referenced CPUNET RAM-pin collisions and the unreconstructed ESB worker
  entry at analysis 0x0102b204 (`our_boot_bringup.md` §18.8).
