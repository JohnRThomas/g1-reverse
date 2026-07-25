# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**Tenth measurement of `display_sensor_parity.md`'s criteria against our
rebuild** (iteration 23; previous measurements were iterations 14–22).

## READ THIS FIRST — iteration 23: still 0 lit pixels, but the ESB gate was
## re-diagnosed and three provable net-core defects were fixed

**NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the
oracle's **656** (`p1_boot`) / **1,098** (`p2_render`); `spim_a` is **34 / 764**
and **0 / 2,881**; no `0x02` pixel-window transaction was emitted.  Verdict
cells are **5 PASS / 5 PARTIAL / 4 FAIL**, unchanged since iteration 17, and
**no per-device volume regressed**.

Three things did change, all measured (`our_boot_bringup.md` §23):

1. **The ESB symptom iteration 22 reported was a HARNESS asymmetry, not a
   firmware defect.**  `device_info[2..4]` (esb_channel / master / slave addr)
   are written only by the factory pairing command `get_assign_channel_info`
   @0x31fd8, gated on the test-mode flag — a lone offline glass never runs it.
   `armemul/g1.resc` therefore *provisions* them with a hook at
   `runtime_info_sync` **for the shipped oracle**, while `g1-ours.resc`
   deliberately omits that hook.  Every ours-vs-oracle capture since iteration
   14 compared an **unprovisioned** device to a **provisioned** one.  New
   additive, opt-in `armemul/g1-ours-paired.resc` restores the symmetry
   (identical writes, identical values, same firmware function, our PC), and
   the app UART changes from `esb_channel 255 esb_master_addr 00
   esb_slave_addr 00` to **`esb_channel 34 esb_master_addr 41 esb_slave_addr
   42`**, with the net id-1 handler receiving `b0=0 b4=65 b5=66`.
2. **The app's own `struct bt_conn_cb` was missing from the `bt_conn_cb`
   iterable section**, so `ancs_connected` never ran and `g_ancs_conn` stayed 0.
   The shipped section `[0x87fec, 0x88058)` holds three 0x24-byte entries and
   entry 0 is `{ancs_connected, ancs_disconnected, ancs_security_changed}`; our
   image had only the SDK's mcumgr entry, and `--gc-sections` had dropped all
   three callbacks (no symbol for any of them in the iteration-22 ELF).  New
   `recon/application/app/src/g1_bt_conn_cb_objects.c` emits the entry with the
   stock `BT_CONN_CB_DEFINE`.  **Measured:** the section now has 2 entries,
   `ancs_connected` executes once at t ≈ 1.47 s and `g_ancs_conn` reads
   **0x2002C838**.
3. **The CPUNET ESB radio path advanced four stages** — `clock-transition cb →
   transport_start → radio_configure → ESB enable (FUN_010333b4) →
   mode_state_init` — after three fixes: a clock-callback pointer left at an
   ORIGINAL-image address, two unreconstructed Ghidra-gap RADIO trampolines
   (`FUN_01032ba4`/`FUN_01032be4`, plus their shared packer `FUN_01032b4c`),
   and a **dropped register argument** in `FUN_01032764` (the harness blind
   spot: the caller relies on r1 living through the call).
   `esbslave MasterFramesSeen` is still **0** vs the oracle's **0x175**.

**Correction to iteration 22's second named gate.**  `ble_is_connected` still
prints 0, and on the MASTER leg that is *correct*: the flag additionally
requires `ctx[0x6de] & 1`, which is the **peer lens's** connection flag carried
inside the ESB segmented-frame staging window.  The unregistered callback was
a real defect and is fixed; the counter it was named by is ESB-gated.

### The first divergence for iteration 24

`FUN_010333b4` writes its RADIO callback slot only for `saved[0] ∈ {0,1}`;
measured, neither branch is taken, so the ESB **configuration struct** that
`FUN_0102b31c` hands it does not carry the mode byte the shipped firmware has.
One function upstream of where the chain now stops.

## 1. Reproduce (exact commands, iteration 23)

```sh
cd /Users/freedomcoder/Projects/G1disasm2

# $rtinfo_pc must be OUR build's runtime_info_sync:
#   arm-zephyr-eabi-nm zephyr.elf | grep -w runtime_info_sync   -> 0x00015b9c
printf '$rtinfo_pc=0x00015b9c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i23/ours-paired-i23.resc

G1_RESC=/private/tmp/g1-i23/ours-paired-i23.resc \
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i23-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i23

PYTHONSAFEPATH=1 .venv/bin/python \
  recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i23 /private/tmp/g1-i23/ours_reports
```

`g1-ours-paired.resc` is **additive and opt-in**: it includes `g1-ours.resc`
unchanged and adds only the factory ESB pairing provisioning that
`armemul/g1.resc` already gives the shipped oracle (see the READ-THIS-FIRST
item 1).  Without it the comparison is unprovisioned-vs-provisioned.

`G1_HOOKS=0` is required because the four `sysbus.cpuapp AddHook` PCs in the
oracle capture are **ORIGINAL-image** addresses; our build relocates them.
`G1_CTX_FE8` / `G1_CTX_105A` are `device_ctx + 0xfe8` / `+ 0x105a`; the app RAM
map of `g1-i22b-app` is byte-identical to `g1-i21b-app` and `g1-i20a-app`
(252,885 B, `g1_ram_arena` at 0x20003100, `_end` at 0x2003fbd5), so the
iteration-20 probe addresses remain correct.

## 2. Per-criterion table (iteration 23, `g1-i23a-app` + `g1-i23-net`; the
## iteration-22 evidence cells below are unchanged unless noted)

| id | criterion | verdict | vs iter 20 | evidence |
|---|---|---|---|---|
| **S-IMU** | `twim2` LSM6DSO stream hash per phase | **PARTIAL** | unchanged | `p1_boot` **1,027** vs 1,089, first difference at txn **#3** (oracle `W 18`, ours `W 0180`).  `p2_render` **700** vs 1,200, **all 700 byte-identical**, first difference is the truncation at **#700** (oracle's next is `W 28`). |
| **S-ALS** | `opt3001_ambient_light` stream hash | **PARTIAL (prefix-exact)** | unchanged | `p1_boot` **14** vs 33, all 14 byte-identical, first difference at **#14** (oracle `W 7E`).  `p2_render` **0** vs 80. |
| **S-PMIC** | `npm1300_charger_fuelgauge` stream hash | **PARTIAL** | **+1 txn in `p2`** | `p1_boot` **232** vs 291, first difference at **#0** (oracle `W 060206`, ours `W 040F`).  `p2_render` **370** vs 508 (iter 20: 369), first difference at **#0** (oracle `W 070401 ×2`, ours `×3`). |
| **S-NFC** | `st25dv_nfc_eeprom` + `st25dv_system_port` | **PARTIAL** | unchanged | EEPROM (0x53) **11** vs 25, first difference at **#6** (oracle `W 200200`, ours `W 2002B8`).  System port (0x57) **12** vs 22, first difference at **#10** (oracle `W 0001`, ours `W 000101`).  Both `p2_render` **0** (oracle 7 / 4). |
| **S-ADC** | `saadc` whole-run stream hash | **PARTIAL (prefix-exact)** | unchanged | first **5** register accesses byte-identical, first difference at **#5**: oracle writes `CH[3].CONFIG` (0x548 ← 0x20000), ours goes straight to `CH[0].PSELP`.  **71** vs 998.  UART confirms `<err> adc_nrfx_saadc: Channel 3 not configured`. |
| **S-KEYS** | `gpiote0` whole-run stream hash; `gpiote1` count == 0 | **PASS** | unchanged | `gpiote0` **stream_sha256 identical** (25 == 25); `gpiote1` **0 == 0**. |
| **S-MIC** (negative) | `pdm0` == exactly 2 writes, no ENABLE/START | **PASS** | unchanged | `pdm0` **stream_sha256 identical**, 2 == 2. |
| **gyro** (negative) | `CTRL2_G` stays 0 / gyro never enabled | **PASS (weak)** | unchanged | `IMU_GYRO_ENABLED` False in both; `IMU_ACCEL_ENABLED` True in both. |
| **S-ESB** | ESB sync reaches 0x02, display-on 0x01, PTX > 0 | **FAIL** | **BLE half passes; ESB now provisioned + 4 stages deeper (iter 23)** | `esbslave MasterFramesSeen` **0** vs 0x175, `AcksInjected` **0** vs 0x175, `AnnounceResponsesInjected` **0** vs 0x15B, `ESB_SYNC_ctx_105a` **0x01** vs 0x02, `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01.  But `vcentral Connected` **True == True**, `ConnectIndsSent` **1 == 1**, `DataEventsAnswered` **530** vs 533, `radio TransmittedFrames` **186** vs 560 — all four were 0/False in iterations 14–21. |
| **G-1** | `framebuffer.p2_render.sha256` | **FAIL** | unchanged | ours `0c5cc90b07…`, **0 lit px / 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px / 2,752 windows**. |
| **G-2** | `framebuffer.p1_boot.sha256` | **FAIL** | unchanged | ours `0c5cc90b07…`, **0 lit px / 3 pixel windows**; oracle `1d617c65a6…`, **656 lit px / 673 windows**. |
| **G-3** | `spim_a` ordered byte stream per phase | **FAIL (truncation only)** | unchanged (34 txns) | `p1_boot` **34 vs 764**; **all 34 shared transactions byte-identical**; first difference at index **34**, oracle `{"op":"0x66","kind":"command","n_tx":1,"n_rx":1}`, ours `<end>`.  `p2_render` **0 vs 2,881**, first difference index **0** (oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265,…}`). |
| **G-4** | *(localiser only)* first differing row | **localised (unchanged)** | our framebuffer bytes are bit-identical to iterations 16–21 (`0c5cc90b07…`) | first differing row **y = 267**, first differing pixel **x = 178** (oracle `ffffff`, ours `000000`) — top-left of the oracle's lit bbox (178,267)–(449,287).  Not re-derived: the sha is bit-identical, so the result carries over. |
| **G-5** | panel init: `0x9F`→`0x4010`, three-band 153 600 B clear, five `0xC0` words, `0x46`/`0x31` pairs `0F 04` / `00 04` | **PASS** | unchanged | all four enumerated elements byte-exact at the same indices, including the trailing `0xB9 FF` at index 33. |
| **G-6** | `spim_b` transaction count == 0 | **PASS** | unchanged | `stream_sha256` EQ, 0 == 0 in both phases, and we genuinely drive `spim_a`. |

Score: **5 PASS** (S-KEYS, S-MIC, gyro-negative, G-5, G-6), **5 PARTIAL**
(S-IMU, S-ALS, S-PMIC, S-NFC, S-ADC), **4 FAIL** (S-ESB, G-1, G-2, G-3) —
**identical verdict cells to iterations 17–21.**  What iteration 22 bought is
not a verdict but the first four BLE counters ever to match the oracle, plus a
reset-free 20 s capture.

## 3. Transaction volumes

| device / phase | oracle | iter 19 | iter 20 | iter 21 | **iter 22** |
|---|---:|---:|---:|---:|---:|
| LSM6DSO (0x6B) `p1_boot` | 1,089 | 1,027 | 1,027 | 551 | **1,027** |
| LSM6DSO (0x6B) `p2_render` | 1,200 | 456 | 700 | not measured | **700** |
| nPM1300 (0x6B) `p1_boot` | 291 | 232 | 232 | 97 | **232** |
| nPM1300 (0x6B) `p2_render` | 508 | 233 | 369 | not measured | **370** |
| OPT3001 (0x45) `p1_boot` | 33 | 14 | 14 | 14 | **14** |
| ST25DV system port (0x57) `p1_boot` | 22 | 12 | 12 | 6 | **12** |
| ST25DV NFC EEPROM (0x53) `p1_boot` | 25 | 11 | 11 | 0 | **11** |
| `saadc` accesses (whole run) | 998 | 53 | 71 | not measured | **71** |
| `gpiote0` accesses (whole run) | 25 | 25 | 25 | not measured | **25** (hash EQ) |
| `pdm0` accesses (whole run) | 2 | 2 | 2 | not measured | **2** (hash EQ) |
| `spim_a` `p1_boot` | 764 | 34 | 34 | 34 | **34** |
| `spim_a` `p2_render` | 2,881 | 0 | 0 | not measured | **0** |
| `spim_b` (both phases) | 0 | 0 | 0 | 0 | **0** (hash EQ) |

### 3.1 Iteration 23 (`g1-i23a-app` + `g1-i23-net`, paired provisioning)

Every volume in the table above is **reproduced exactly** — LSM6DSO 1,027 /
700, nPM1300 232 / 370, OPT3001 14 / 0, ST25DV 12 and 11, saadc 71, gpiote0 25
(hash EQ), pdm0 2 (hash EQ), spim_a 34 / 0, spim_b 0 (hash EQ), JBD
FrameCounter 0x3 / 0x3, JournalCount 0x22, framebuffer **0 / 0 lit px**.  BLE
counters moved slightly with the radio-model cadence: `RADIO_TX` **0xBD** vs
oracle 0x230, `VC_DATA_EVENTS` **0x216** vs 0x215, `VC_CONNECTED` True == True,
`VC_CONNECT_INDS` 1 == 1.  ESB: `MasterFramesSeen` / `AcksInjected` /
`AnnounceResponsesInjected` all **0** vs 0x175 / 0x175 / 0x15B;
`ESB_SYNC_ctx_105a` **0x01** vs 0x02; `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01.
| `JBD FrameCounter` `p1` / `p2` | 0x2A1 / 0xD61 | — | 0x3 / 0x3 | 0x0 / – | **0x3 / 0x3** |
| framebuffer lit px `p1` / `p2` | 656 / 1,098 | 0 / 0 | 0 / 0 | 0 / – | **0 / 0** |

## 4. What moved this iteration

### 4.1 The recovered printf engine is retired, not debugged

`our_boot_bringup.md` §22.1 re-measured all twenty members of the newlib-nano
formatting closure against
`arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a`: **7,124
distinguishing bytes, zero disagreements**, whole sections including the tails
past Ghidra's extent.  Even did not modify printf.  The proof the displacement
is semantically right is the firmware's own log line — `Advertising
Even G1_R_FFFFFF successfully started` — with the exact sixteen-character
string the recovered `_svfprintf_r` could not produce (it returned 131 and left
the buffer empty).

**Method note that generalises:** `tools/parity` / `tools/cfg_verify` passed
`printf_parse_format` because they emulate at the ORIGINAL address with the
ORIGINAL callees as order-keyed oracles, so a flattened control-flow
reconstruction can still reproduce the traced side effects.  Byte identity
against the pinned SDK is a strictly stronger gate for anything the SDK owns.

### 4.2 Three of `bt_le_adv_start`'s four operands were pointing at the
### original image

`rodata_8839c` (the `struct bt_le_adv_param`) was still an identity pin, and
0x0008839c in OUR image holds the ASCII `_types.h`, so `options` read
0x682e7365 and `valid_adv_param()` returned -EINVAL.  The two `struct bt_data`
arrays at 0x20002350 / 0x20002358 have pointer-bearing `.data` initialisers
that the RAM-arena restore drops, so `sd[0].type` advertised as 0x00 instead of
`BT_DATA_NAME_COMPLETE` and `ad[0]` was an empty AD structure instead of the
flags byte.  All three emitted byte-exactly in
`recon/application/app/src/g1_bt_adv_objects.c` and bound in
`recon/symbols/g1_app_globals.ld` (full evidence in §22.6).

### 4.3 Why the painting still does not happen

Unchanged in kind, moved in cause.  The oracle's own `spim_a.p1.trace` has no
SPI activity between 0.121 s and 3.92 s and every transaction after index 33 is
downstream of the L+R lens sync.  In iterations 14–21 the gate was BLE; it is
now **ESB**: `esb_channel` = 255, `esb_master_addr`/`esb_slave_addr` = 00,
`esbslave MasterFramesSeen` = 0, so `ESB_SYNC_ctx_105a` stops at 1 and
`DISPLAY_ON_ctx_fe8` never becomes 1.  Our display driver still reproduces the
oracle byte-for-byte for everything it is asked to do; it is still never asked
to paint.

---

## Everything below this line is the ITERATION 20 measurement, kept for provenance

Iteration 20 root-caused and fixed the iteration-19 blocker.  It was **not** in
the raw-literal class that iteration 19 nominated: it was a **wrong-indirection
defect in the recovered `net_buf_unref` (`FUN_0102ff94`)**, which dereferenced
`pool->alloc` once where the shipped code dereferences it twice and therefore
called `pool->alloc->max_alloc_size` — measured as `blx r3` with **r3 = 0x44 =
CONFIG_BT_BUF_EVT_RX_SIZE** — instead of `pool->alloc->cb->unref`.  With that
and one wrong library adoption on the app core repaired, **both cores run 8.0 s
with zero fatal errors at the same time**, and the app core's `bt_enable()`
completes the entire HCI handshake.

* Oracle (diff target): `recon/emulator/reports/display_sensor_oracle.json`
  (shipped `app_update.bin` / `netcore_image.bin`), criteria in
  `recon/emulator/reports/display_sensor_parity.md` §5.
* Our build: **`/private/tmp/g1-i20a-app/zephyr/zephyr.elf`** +
  **`/private/tmp/g1-i20c-net/zephyr/zephyr.elf`** (the final `g1-i20d-net`
  differs only in comment placement; `zephyr.bin` is byte-identical, verified
  with `cmp` — see `our_boot_bringup.md` §"Regenerate (iteration 20)").
* Captured under **identical determinism knobs and identical stimulus** to the
  oracle: global quantum `0.000010`, CC312 seed `0x5340CC3105340CC3`, serial
  core scheduling, 20.0 s virtual-time budget split 6 s (`p1_boot`) + 14 s
  (`p2_render`), `vcentral` sweep + NUS write, `esbslave`, `PlayGesture "don"`.
  **No memory was poked.**
* `armemul` is **untouched** this iteration.

## 1. Reproduce (exact commands)

```sh
cd /Users/freedomcoder/Projects/G1disasm2

# (a) OUR capture -- the oracle capture script, parameterised
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i20a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i20c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i20

# (b) build the same JSON from our capture, into a SCRATCH report dir
PYTHONSAFEPATH=1 .venv/bin/python \
  recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i20 <SCRATCH>/g1-i20/ours_reports

# (c) diff -- PER DEVICE, never the merged twim1/twim2 bus hash, plus the
#     ordered per-device RLE first-difference index
```

`G1_HOOKS=0` is required because the four `sysbus.cpuapp AddHook` PCs in the
oracle capture are **ORIGINAL-image** addresses; our build relocates them.

**The context probes are correct for the first time since iteration 14.**
`G1_CTX_FE8` / `G1_CTX_105A` are `device_ctx + 0xfe8` / `+ 0x105a`, and the
context base was measured directly this iteration with a Renode hook inside
`bt_start` (`BTSTART_STATE di=0x2003FBE0`), giving **0x20040BC8** and
**0x20040C3A**.  They now read plausible values (`DISPLAY_ON_ctx_fe8` = `0x00`,
`ESB_SYNC_ctx_105a` = `0x01`) instead of iterations 14–19's stale `0x7C`.

> **Our capture is no longer truncated by a reset.**  In iterations 16–18 the
> app core reset at t = 5.093 s; in iteration 19 the net core reset at
> t = 5.0942 s and Renode's nRF5340 platform reset the SoC with it.  In
> iteration 20 **neither core resets in an 8 s boot and no `SYSRESETREQ` is
> issued during the 20 s capture**, so every `p2_render` column below is real
> measurement rather than a zero produced by a dead machine.

## 2. Per-criterion table (iteration 20, `g1-i20a-app` + `g1-i20c-net`)

| id | criterion | verdict | vs iter 19 | evidence |
|---|---|---|---|---|
| **S-IMU** | `twim2` LSM6DSO stream hash per phase | **PARTIAL** | **improved** (983 → 1,027 `p1`; 0 → **700** `p2`) | `p1_boot` **1,027** vs oracle 1,089; first **3** transactions byte-identical, first difference at txn **#3** (oracle `W 18`, ours `W 0180`). `p2_render` **700** vs 1,200, and **all 700 are byte-identical** — the first difference is the truncation at **#700** (oracle's next is `W 28`). |
| **S-ALS** | `opt3001_ambient_light` stream hash | **PARTIAL (prefix-exact)** | unchanged | `p1_boot` **14** vs 33; all 14 byte-identical, then ours stops (oracle's #14 is `W 7E`). `p2_render` **0** vs 80. |
| **S-PMIC** | `npm1300_charger_fuelgauge` stream hash | **PARTIAL** | **improved** (`p2` 0 → **369**) | `p1_boot` **232** vs 291; diverges at txn **#0** (oracle `W 060206`, ours `W 040F`). `p2_render` **369** vs 508, first difference at **#2**. |
| **S-NFC** | `st25dv_nfc_eeprom` + `st25dv_system_port` | **PARTIAL** | unchanged | NFC EEPROM (0x53) **11** vs 25, first **6** byte-identical, first difference at **#6** (oracle `W 200200`, ours `W 2002B8` — the written-back value is an arena address). System port (0x57) **12** vs 22, first **10** byte-identical, first difference at **#10** (oracle `W 0001`, ours `W 000101`). Both `p2_render` **0** (oracle 7 / 4). |
| **S-ADC** | `saadc` whole-run stream hash | **PARTIAL (prefix-exact)** | **improved** (17 → **71**) | first **5** register accesses byte-identical, first difference at **#5**: the oracle writes `CH[3].CONFIG` (0x548 ← 0x20000), ours goes straight to `CH[0].PSELP`. UART confirms `<err> adc_nrfx_saadc: Channel 3 not configured`. **71** vs 998. |
| **S-KEYS** | `gpiote0` whole-run stream hash; `gpiote1` count == 0 | **PASS** | unchanged | `gpiote0` **stream_sha256 identical** (25 == 25); `gpiote1` **0 == 0**. |
| **S-MIC** (negative) | `pdm0` == exactly 2 writes, no ENABLE/START | **PASS** | unchanged | `pdm0` **stream_sha256 identical**, 2 == 2. |
| **gyro** (negative) | `CTRL2_G` stays 0 / gyro never enabled | **PASS (weak)** | unchanged | `IMU_GYRO_ENABLED` = False in both. Caveat: `IMU_ACCEL_ENABLED` is now **True in both** (it was True in both before as well), so the negative still holds and is now slightly more discriminating. |
| **S-ESB** | ESB sync reaches 0x02, display-on 0x01, PTX > 0 | **FAIL (not reached)** | unchanged | `radio TransmittedFrames` **0** (oracle 0x230), `esbslave MasterFramesSeen` **0** (oracle 0x175), `vcentral Connected` **False** (oracle True), `ConnectIndsSent` 0 vs 1. `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01, `ESB_SYNC_ctx_105a` **0x01** vs 0x02 — now genuine readings from correct probe addresses. |
| **G-1** | `framebuffer.p2_render.sha256` | **FAIL** | unchanged | ours `0c5cc90b07…`, **0 lit px**; oracle `b26c73b37d…`, **1,098 lit px**. |
| **G-2** | `framebuffer.p1_boot.sha256` | **FAIL** | unchanged | ours `0c5cc90b07…`, **0 lit px**; oracle `1d617c65a6…`, **656 lit px**. |
| **G-3** | `spim_a` ordered byte stream per phase | **FAIL (truncation only)** | unchanged (34 txns) | `p1_boot` **34 vs 764**; **all 34 shared transactions byte-identical**; first difference at index **34**, where the oracle emits `{"op":"0x66","kind":"command","n_tx":1,"n_rx":1}` and we emit nothing. `p2_render` **0 vs 2,881**. |
| **G-4** | *(localiser only)* first differing row | **localised (unchanged)** | our framebuffer bytes are **bit-identical to iterations 16–19** (`0c5cc90b07…`) | first differing row **y = 267**, first differing pixel **x = 178** (oracle `ffffff`, ours `000000`) — top-left of the oracle's lit bbox (178,267)–(449,287). Not re-derived: the sha is bit-identical, so the result carries over. |
| **G-5** | panel init: `0x9F`→`0x4010`, three-band 153 600 B clear, five `0xC0` words, `0x46`/`0x31` pairs `0F 04` / `00 04` | **PASS** | unchanged | all four enumerated elements byte-exact, including the trailing `0xB9 FF` at index 33. |
| **G-6** | `spim_b` transaction count == 0 | **PASS** | unchanged | ours 0 == oracle 0, hash EQ, and we genuinely drive `spim_a`. |

Score: **5 PASS** (S-KEYS, S-MIC, gyro-negative, G-5, G-6), **5 PARTIAL**
(S-IMU, S-ALS, S-PMIC, S-NFC, S-ADC), **4 FAIL** (S-ESB, G-1, G-2, G-3) —
**identical to iterations 17–19 in every verdict cell.**  What iteration 20
bought is not a verdict but *depth*: three PARTIALs advanced materially, and the
two resets that had gated everything are both gone.

## 3. Transaction volumes

| device / phase | oracle | `g1-i17d` | iter 18 | iter 19 final | iter 19 reset-free-net | **iter 20** |
|---|---:|---:|---:|---:|---:|---:|
| LSM6DSO (0x6B) `p1_boot` | 1,089 | 983 | 983 | 983 | 1,027 | **1,027** |
| LSM6DSO (0x6B) `p2_render` | 1,200 | 0 | 0 | 0 | 456 | **700** |
| nPM1300 (0x6B) `p1_boot` | 291 | 199 | 199 | 199 | 232 | **232** |
| nPM1300 (0x6B) `p2_render` | 508 | 0 | 0 | 0 | 233 | **369** |
| OPT3001 (0x45) `p1_boot` | 33 | 14 | 14 | 14 | 14 | **14** |
| ST25DV system port (0x57) `p1_boot` | 22 | 12 | 12 | 12 | 12 | **12** |
| ST25DV NFC EEPROM (0x53) `p1_boot` | 25 | 11 | 11 | 11 | 11 | **11** |
| `saadc` accesses (whole run) | 998 | 17 | 17 | 17 | 53 | **71** |
| `gpiote0` accesses (whole run) | 25 | 25 | 25 | 25 | 25 | **25** (hash EQ) |
| `pdm0` accesses (whole run) | 2 | 2 | 2 | 2 | 2 | **2** (hash EQ) |
| `spim_a` `p1_boot` | 764 | 34 | 34 | 34 | 34 | **34** |
| `spim_a` `p2_render` | 2,881 | 0 | 0 | 0 | 0 | **0** |
| `spim_b` (both phases) | 0 | 0 | 0 | 0 | 0 | **0** (hash EQ) |
| framebuffer lit px `p1` / `p2` | 656 / 1,098 | 0 / 0 | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |

`spim_a` did not move by a single transaction, because everything past index 34
is gated on the BLE link.

## 4. What moved this iteration

### 4.1 The CPUNET t = 5.0942 s fault is fixed — and it was not a raw literal

A 60 ms CPUNET PC trace across the fault shows the core branching to **address
0x44** from inside `FUN_0102ff94` (`net_buf_unref`), after which the Zephyr
fault path prints `Reserved Exception` / `pc 0x00000000` — the symptom iteration
19 read as "PendSV restored PC = 0".  The shipped disassembly has three loads
(`pool->alloc`, `alloc->cb`, `cb->unref`); the reconstruction had two, so it
called `pool->alloc->max_alloc_size`, which for the HCI event pool is
`CONFIG_BT_BUF_EVT_RX_SIZE = 68 = 0x44`.  It also dropped the second argument
(`data`), which the shipped code keeps live in r1.  Both corrected;
`cfg_verify` PASS.  Full detail in `our_boot_bringup.md` §20.3.

### 4.2 Both cores are reset-free at the same time

| | iter 19 final | **iter 20** |
|---|---|---|
| app `ZEPHYR FATAL ERROR` @8.0 s | 0 | **0** |
| net `ZEPHYR FATAL ERROR` @8.0 s | 1 (t = 5.0942 s) | **0** |
| `SYSRESETREQ` in an 8 s run | 1 | **0** |
| app instructions @8.0 s | not reached | **17,753,624** |
| net instructions @8.0 s | not reached | **2,080,530** |
| `bt_enable()` completes the HCI handshake | no | **yes, t = 5.100 s** |
| `ancs_c_init()` returns 0 | not reached | **yes** |
| `bt_start()` reached | no | **yes** |

Two further fixes made that possible and are documented in
`our_boot_bringup.md`: the **shipped `_kernel` shadow** at 0x21004b28 closed
structurally across 75 TUs (§20.2 — provably correct, symptom-neutral, kept and
reported as such), and the **vendored ANCS client** (§20.5): the manifest had
adopted upstream `bt_ancs_register_attr` / `bt_ancs_register_app_attr` on a 1.0
instruction-*shape* match, but the shipped build uses `len ≤ 256` (not 32) and
`struct bt_ancs_client` offsets `0x868/0x870/0x874` (not `0x108/0x110/0x114`);
the recovered `ancs_service_ctx_clear` memsets 0xa2c bytes, corroborating the
larger struct.  Once `bt_enable` worked, that mismatch made `ancs_c_init` fail
and `ancs_main` reboot the SoC at t = 6.6 s.

### 4.3 Why the painting still does not happen

Unchanged and still operative: the oracle's own `spim_a.p1.trace` has **no SPI
activity between 0.121 s and 3.92 s**, and every transaction after index 33 is
downstream of the BLE link.  Our display driver reproduces the oracle
byte-for-byte for everything it is asked to do; it is simply never asked to
paint.  The gate is now precisely located: `bt_start()` reads
`device_info[0x1058]`, measures **0**, and returns without calling
`bt_le_adv_start` (`our_boot_bringup.md` §20.6).

## 5. First differences that are genuine recon defects

### S-IMU — LSM6DSO on `twim2` (`p1_boot` first divergence at transaction #3)

```
#0  oracle W 0x6B 0100   ours W 0x6B 0100     FUNC_CFG_ACCESS(0x01) <- 0x00
#1  oracle W 0x6B 0F     ours W 0x6B 0F       WHO_AM_I(0x0F) address
#2  oracle R 0x6B 6C     ours R 0x6B 6C       -> 0x6C, accepted
#3  oracle W 0x6B 18     ours W 0x6B 0180  <<< FIRST DIFFERENCE
```

Unchanged from iterations 14–20: the original does a read-modify-write of
**`CTRL9_XL` (0x18)** inside `lsm6dso_init_chip`, while ours writes
**`FUNC_CFG_ACCESS ← 0x80`** and reads `0x46` (`FSM_ENABLE_A`) in an
embedded-functions bank the original never enters.  **Classification: recon
defect.  Not fixed this iteration.**

`p2_render`, by contrast, is **byte-identical for all 700 transactions we
produce**; the only difference is that the oracle produces 1,200.  That is a
liveness gap, not a semantic one.

### S-PMIC — nPM1300 on `twim1` @0x6B (`p1_boot` first divergence at #0)

```
#0  oracle W 0x6B 060206   ours W 0x6B 040F   <<< FIRST DIFFERENCE
```

The original opens with a **bank-0x06 register-write burst** (GPIO / ship-mode);
ours opens with **bank-0x04 register reads**.  `p2_render` diverges at **#2**
(a repeat count: oracle `W 070401 ×2`, ours `×3`).  **Classification: recon
defect (init-sequence ordering).  Not fixed this iteration.**

### S-NFC — first-difference registers

```
st25dv_nfc_eeprom (0x53)
  #6   oracle W 0x53 200200   ours W 0x53 2002B8   <<< FIRST DIFFERENCE
st25dv_system_port (0x57)
  #10  oracle W 0x57 0001     ours W 0x57 000101   <<< FIRST DIFFERENCE
```

Both are read-modify-write sequences where the value written back differs; the
EEPROM payload is an **arena address** where the original writes 0x00, which is
itself diagnostic.  **Classification: recon defect.  Not fixed this iteration.**

### S-ADC — missing channel configuration

The oracle configures **`CH[3]`** (`0x548 ← 0x20000`) before touching `CH[0]`;
we skip it and the driver logs `adc_nrfx_saadc: Channel 3 not configured`.
**Classification: recon defect (missing channel configuration).  Not fixed this
iteration.**

## 6. Honest summary

* **The CPUNET t = 5.0942 s fault is fixed**, and iteration 19's hypothesis for
  it (the raw-literal ledger) was **wrong** — the cause was a missing
  dereference plus a dropped register argument in `net_buf_unref`.  That
  correction is recorded as such.
* **Both cores run 8.0 s reset-free simultaneously for the first time**, with
  zero `SYSRESETREQ`.
* **`bt_enable()` completes the full HCI handshake** over the reconstructed
  rpmsg transport, and the app core now reaches `bt_start()`.
* **BLE still does NOT advertise or connect.** `radio TransmittedFrames` = 0,
  `vcentral Connected` = False, `esbslave MasterFramesSeen` = 0.
* **No pixel was painted.** G-1/G-2 remain 0 lit px vs the oracle's 656 / 1,098;
  G-3 remains 34 of 764 with the whole 34-transaction prefix byte-identical and
  the first difference at index 34; G-5 and G-6 still **PASS**; the framebuffer
  sha is bit-identical to iterations 16–19, so G-4's localisation (row y = 267,
  pixel x = 178) carries over rather than being re-derived.
* **Score unchanged: 5 PASS / 5 PARTIAL / 4 FAIL**, but three PARTIALs advanced
  measurably (IMU `p2_render` 456 → **700** byte-identical transactions, PMIC
  233 → **369**, SAADC 53 → **71**).
* **Next**: `device_info[0x1058]` — the one byte between `bt_start()` and
  `bt_le_adv_start()` (`our_boot_bringup.md` §20.6).
