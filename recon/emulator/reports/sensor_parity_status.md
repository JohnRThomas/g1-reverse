# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**Fourth measurement of `display_sensor_parity.md`'s criteria against our
rebuild** (iteration 17; previous measurements were iterations 14, 15 and 16).
Iteration 17 **removed the `t ≈ 0.104 s` reset** that iteration 16 introduced,
so every sensor stream that the reset had cut off came back — and then some.
The graphics half is unchanged in verdict but its cause is now **named and
reproducible** rather than inferred: the oracle's pixel windows are all
downstream of the BLE link, and our BLE link dies on a **net-core**
`rpmsg_get_endpoint` spin (§4).

* Oracle (diff target): `recon/emulator/reports/display_sensor_oracle.json`
  (shipped `app_update.bin` / `netcore_image.bin`), criteria in
  `recon/emulator/reports/display_sensor_parity.md` §5.
* Our build: **`/private/tmp/g1-i17d-app/zephyr/zephyr.elf`** (iteration 17
  final, app) + `/private/tmp/g1-i9c-net/zephyr/zephyr.elf` (net, **unchanged
  since iteration 9** — this is now the blocker, see §4).
* Captured under **identical determinism knobs and identical stimulus** to the
  oracle: global quantum `0.000010`, CC312 seed `0x5340CC3105340CC3`, serial
  core scheduling, 20.0 s virtual-time budget split 6 s (`p1_boot`) + 14 s
  (`p2_render`), `vcentral` sweep + NUS write, `esbslave`, `PlayGesture "don"`.
* `armemul` is **untouched** this iteration.

## 1. Reproduce (exact commands)

```sh
cd /Users/freedomcoder/Projects/G1disasm2

# (a) OUR capture -- the oracle capture script, parameterised
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i17d-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i9c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_ours_i17d

# (b) build the same JSON from our capture, into a SCRATCH report dir
PYTHONSAFEPATH=1 .venv/bin/python \
  recon/emulator/scripts/build_display_sensor_oracle.py \
  /tmp/g1_ours_i17d <SCRATCH>/i17/rep_i17d

# (c) diff -- PER DEVICE, never the merged twim1 bus hash
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i14/diff_parity.py \
  <SCRATCH>/i17/rep_i17d/display_sensor_oracle.json
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i17/firstdiff.py

# (d) G-3 / G-5: ordered spim_a transaction diff vs the oracle trace
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i16/g5diff.py \
  <SCRATCH>/g1_oracle/spim_a.p1.trace /tmp/g1_ours_i17d/spim_a.p1.trace
```

`G1_HOOKS=0` is required because the four `sysbus.cpuapp AddHook` PCs in the
oracle capture are **ORIGINAL-image** addresses; our build relocates them.
`G1_CTX_FE8` / `G1_CTX_105A` are the arena-relative equivalents of the
original's `device_ctx+0xfe8` / `+0x105a` (`g1_ram_arena` = `0x200030a0` in this
build, arena origin `0x20002000` — unchanged since iteration 14).

> **Our capture dies at t = 5.093 s, inside `p1_boot`.** The app core takes a
> `ZEPHYR FATAL ERROR 4` there (§4) and Renode's nRF5340 platform has no reset
> macro, so both cores halt. **That is why every `p2_render` column below is
> zero**, and why the end-of-run `spim_a.jbd FrameCounter` reads 0. The ordered
> transaction logs (`*.p1.trace`) are the authority for §2's rows. The 2.0 s
> boot runs (`/tmp/g1_i17d`, `/tmp/g1_i17d2`) are **reset-free**.

## 2. Per-criterion table (iteration 17 final, `g1-i17d-app`)

| id | criterion | verdict | vs iter 16 | evidence |
|---|---|---|---|---|
| **S-IMU** | `twim2` LSM6DSO stream hash per phase | **PARTIAL** | **25 → 983 txns** (recovered, and past iter 15's 969) | `p1_boot` 983 txns vs oracle 1,089; first **3** transactions byte-identical, first difference still at txn **#3**. `p2_render` 0 (oracle 1,200). |
| **S-ALS** | `opt3001_ambient_light` stream hash | **PARTIAL (prefix-exact)** | **7 → 14 txns** | `p1_boot` 14 txns vs 33; **all 14 byte-identical to the oracle's first 14**, now including `CONFIG ← CE10` (the item iteration 16 listed as unreached), then ours stops. `p2_render` 0 vs 80. |
| **S-PMIC** | `npm1300_charger_fuelgauge` stream hash | **PARTIAL** | **85 → 199 txns** | `p1_boot` 199 raw / 186 RLE vs oracle 291 / 270; still diverges at txn **#0** (`W 060206` vs `W 040F`). `p2_render` 0 vs 508. |
| **S-NFC** | `st25dv_nfc_eeprom` + `st25dv_system_port` | **PARTIAL — now EXERCISED** | **EEPROM 0 → 11 txns**; system port 6 → 12 | NFC EEPROM (0x53) **11** txns vs 25, **first 6 byte-identical**, first difference at **#6** (`W 200200` vs ours `W 200258`). System port (0x57) **12** vs 22, **first 10 byte-identical**, first difference at **#10** (`W 0001` vs ours `W 000101`). The ops-table fix (`our_boot_bringup.md` §17.1) is what turned this path on. |
| **S-ADC** | `saadc` whole-run stream hash | **PARTIAL (prefix-exact)** | **5 → 17 accesses**; new named defect | first **5** register accesses byte-identical (`EventsEnd`, `EventsCalibrateDone`, `INTENSET ← 0x12`), first difference at **#5**: the oracle writes `CH[3].CONFIG` (0x548 ← 0x20000) while ours goes straight to `CH[0].PSELP`. The UART confirms it: `<err> adc_nrfx_saadc: Channel 3 not configured`. 17 vs 998. |
| **S-KEYS** | `gpiote0` whole-run stream hash; `gpiote1` count == 0 | **PASS** | unchanged | `gpiote0` **stream_sha256 identical**, 25 accesses = 25. `gpiote1` **0 == 0**. |
| **S-MIC** (negative) | `pdm0` == exactly 2 writes, no ENABLE/START | **PASS** | unchanged | `pdm0` **stream_sha256 identical**, 2 == 2. |
| **gyro** (negative) | `CTRL2_G` stays 0 / gyro never enabled | **PASS (weak)** | unchanged | `GyroscopeEnabled` = **False**, matching the oracle (also False). **Caveat unchanged:** `AccelerometerEnabled` is also **False** in both, so the criterion holds but is not discriminating. |
| **S-ESB** | ESB sync reaches 0x02, display-on 0x01, PTX > 0 | **FAIL (not reached)** | unchanged | `radio TransmittedFrames` = 0 (oracle 0x230), `esbslave MasterFramesSeen` = 0 (oracle 0x175), `vcentral Connected` = **False** (oracle True), both context bytes `0x00` (oracle `0x01` / `0x02`). Root cause now named — §4. |
| **G-1** | `framebuffer.p2_render.sha256` | **FAIL** | unchanged | ours `0c5cc90b…`, **0 lit px**; oracle `b26c73b3…`, **1,098 lit px**. |
| **G-2** | `framebuffer.p1_boot.sha256` | **FAIL** | unchanged | ours `0c5cc90b…`, 0 lit px; oracle `1d617c65…`, 656 lit px. |
| **G-3** | `spim_a` ordered byte stream per phase | **FAIL (truncation only)** | **33 → 34 txns; prefix still exact** | `p1_boot` ours sha `f40cbd5d…` vs oracle `b64599b1…`, **34 vs 764** transactions. **All 34 shared transactions are byte-identical**; the divergence is pure truncation at index 34. `p2_render` 0 vs 2,881. |
| **G-4** | *(localiser only)* first differing row | **localised (unchanged)** | our framebuffer bytes are **identical to iteration 16's** | first differing row y = 267, first differing pixel x = 178 (oracle `ffffff`, ours `000000`) — the top-left of the oracle's lit bbox (178,267)–(449,287). Not re-derived this iteration: the sha is bit-identical, so the result carries over. |
| **G-5** | panel init: `0x9F`→`0x4010`, three-band 153 600 B clear, five `0xC0` words, `0x46`/`0x31` pairs `0F 04` / `00 04` | **PASS** | **PASS, and now complete** | all four enumerated elements byte-exact, **plus** the trailing `0xB9 FF` at index 33 that iteration 16 was cut off before. The whole `display_sensor_parity.md` §3.1 block is reproduced. |
| **G-6** | `spim_b` transaction count == 0 | **PASS** | unchanged | ours 0 == oracle 0, hash EQ, and we genuinely drive `spim_a`. |

Score: **5 PASS** (S-KEYS, S-MIC, gyro-negative, **G-5**, G-6), **5 PARTIAL**
(S-IMU, S-ALS, S-PMIC, S-NFC, S-ADC), **4 FAIL** (S-ESB, G-1, G-2, G-3) —
the same headline distribution as iteration 16, but every PARTIAL moved
substantially forward and **S-NFC is exercised for the first time**.

## 3. What the reset fix bought (`p1_boot` transaction volumes)

| device | oracle | `g1-i15e` | `g1-i16b` | **`g1-i17d`** |
|---|---:|---:|---:|---:|
| `twim2` LSM6DSO (0x6B) | 1,089 | 969 | 25 | **983** |
| `twim1` nPM1300 (0x6B) | 291 | 85 | 85 | **199** |
| `twim1` OPT3001 (0x45) | 33 | 7 | 7 | **14** |
| `twim1` ST25DV system port (0x57) | 22 | 6 | 6 | **12** |
| `twim1` ST25DV NFC EEPROM (0x53) | 25 | 0 | 0 | **11** |
| `saadc` register accesses (whole run) | 998 | — | 5 | **17** |
| `spim_a` | 764 | 0 | 33 | **34** |

The iteration-16 regression is fully reversed and every stream is at or past
its best-ever value. See `our_boot_bringup.md` §17.1–17.4 for the four fixes:
the NFC ops table (three folded leaves + a `DEVICE_DT_GET` class), the
`misc_dev_api_transfer_op12` collapsed-stack-object defect, the archive-aware
symbol gate, and the atomic restore of `g_screen_render_table`.

## 4. The current blocker — a NET-core `rpmsg_get_endpoint` spin

A dedicated 6.0 s app-core probe with the UART captured (`/tmp/g1_i17d6`) shows
the stop precisely, at **t = 5.093 s** — exactly when `ancs_main`'s
`50 × 100 ms` readiness poll expires and it calls `bt_enable`:

```
[00:00:05.093,139] <err> ipc_service: Endpoint not registered
[00:00:05.093,139] <err> bt_hci_driver: Failed to send (err -2)
ASSERTION FAIL [buf] @ WEST_TOPDIR/zephyr/subsys/net/buf.c:467
<err> os: >>> ZEPHYR FATAL ERROR 4: Kernel panic on CPU 0
<err> fatal_error: Resetting system
```

`ipc_service_send()` returns `-ENOENT` when `ept->instance == NULL`, i.e. the
HCI endpoint was never bound. The cause is on the other core:

```
CPUNET @2.0 s, top by instruction count
  rpmsg_get_endpoint      7 entries   53,146,996 instr   <<< 99.3 % of the core
  memset                 70 entries      137,530
  uarte_nrfx_poll_out  2904 entries       31,218
```

`rpmsg_get_endpoint` is upstream OpenAMP `rpmsg.c`
(`modules/open-amp/open-amp/lib/libopen_amp.a(rpmsg.c.obj)` @0x103d048 in the
net map), a `metal_list_for_each` over `rdev->endpoints`. **It never
terminates.** So the net core never completes its side of the endpoint bind,
the app's HCI endpoint stays unregistered, `bt_enable` fails, nothing
advertises, and `vcentral` never connects.

### Why that stops the painting

The oracle's own `spim_a.p1.trace` settles it: there is **no SPI activity
between tick 1.21e8 (0.121 s) and 3.92e9 (3.92 s)**. The transactions we do not
emit are all downstream of the BLE link, in this order:

```
ORACLE spi_read_id                       (t ~ 0.12 s)   <- we reach this
ORACLE display_START action=0            (t ~ 0.12 s)   <- we reach this
ORACLE display_START action=1            (after BLE connect)
ORACLE BLIT notify_display_mode screen=10  x many       <- the pixel windows
```

Transactions 34–65 are a **second full panel init** and 66+ are the pixel
windows (219-byte `0x02` chunks). Our display driver reproduces the oracle
byte-for-byte for everything it is asked to do — `nrfx_spim_xfer` 170 / 3,774,
`nrfx_spim_uninit` 8 / 43, `spi_master_trans_data_tx_rx` 68 / 714 and
`panel_init` 20 / 52 all **match golden exactly** — it is simply never asked to
paint.

**The net core has not been rebuilt since iteration 9.** Its `rdev->endpoints`
list head is very likely the CPUNET counterpart of the app-core defect
iteration 15 root-caused (a shipped `.data`/`.bss` object our build never
initialises), which makes "give the net core the iteration-15 `.data`
treatment" the obvious next step.

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

Unchanged from iterations 14–16: the original does a read-modify-write of
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

### S-NFC — new, and newly visible

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

* **The `t ≈ 0.104 s` reset is fixed.** The 2.0 s boot is reset-free at
  **996 unique functions / 11,684,715 instructions** (golden 12,629,795) — the
  best figures this project has recorded.
* **5 criteria pass outright**: S-KEYS, S-MIC (negative), gyro (negative),
  **G-5**, and G-6 — all by exact stream-hash / byte-sequence equality.
* **G-5 is now complete**: the entire §3.1 panel-init block, including the
  trailing `0xB9 FF`, is byte-identical. G-3 fails **only by truncation** —
  all 34 transactions we emit match.
* **G-1/G-2 still fail with 0 lit pixels.** No pixels were painted. The reason
  is established, not guessed: every oracle transaction after index 33 is
  downstream of the BLE link, and our BLE link dies at 5.093 s on a **net-core
  `rpmsg_get_endpoint` spin**.
* **Every PARTIAL improved**, and S-NFC went from *not exercised* to two
  named first-differing registers.
* **The single highest-value next fix is the net core** (§4): it is unchanged
  since iteration 9, it burns 99.3 % of its instructions in one non-terminating
  list walk, and it is the only thing between the current build and the
  painting path.
