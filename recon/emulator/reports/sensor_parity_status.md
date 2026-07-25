# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**Third measurement of `display_sensor_parity.md`'s criteria against our
rebuild** (iteration 16; previous measurements were iterations 14 and 15).
Iteration 16 fixed the SPIM `p_reg` defect, so **our firmware drives the real
JBD panel for the first time and G-5 now passes**. It also introduced a
relocation-aware `.data` pointer restore. Both changes moved the boot *further*
and into a *new* fault, so the sensor volumes below are **lower** than
iteration 15's — that regression is real and is reported as such in §4.

* Oracle (diff target): `recon/emulator/reports/display_sensor_oracle.json`
  (shipped `app_update.bin` / `netcore_image.bin`), criteria in
  `recon/emulator/reports/display_sensor_parity.md` §5.
* Our build: **`/private/tmp/g1-i16b-app/zephyr/zephyr.elf`** (iteration 16
  final, app) + `/private/tmp/g1-i9c-net/zephyr/zephyr.elf` (net, unchanged
  since iteration 9).
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
G1_APP_ELF=/private/tmp/g1-i16b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i9c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_ours_i16b2

# (b) build the same JSON from our capture, into a SCRATCH report dir
PYTHONSAFEPATH=1 .venv/bin/python \
  recon/emulator/scripts/build_display_sensor_oracle.py \
  /tmp/g1_ours_i16b2 <SCRATCH>/i16/rep_i16b

# (c) diff -- PER DEVICE, never the merged twim1 bus hash
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i14/diff_parity.py \
  <SCRATCH>/i16/rep_i16b/display_sensor_oracle.json
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i16/firstdiff.py

# (d) G-3 / G-5: ordered spim_a transaction diff vs the oracle trace
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/i16/g5diff.py \
  <SCRATCH>/g1_oracle/spim_a.p1.trace /tmp/g1_ours_i16b2/spim_a.p1.trace
```

`G1_HOOKS=0` is required because the four `sysbus.cpuapp AddHook` PCs in the
oracle capture are **ORIGINAL-image** addresses; our build relocates them.
`G1_CTX_FE8` / `G1_CTX_105A` are the arena-relative equivalents of the
original's `device_ctx+0xfe8` / `+0x105a` (`g1_ram_arena` = `0x200030a0` in this
build, arena origin `0x20002000` — unchanged since iteration 14).

> **Read the `spim_a` trace file, not the JBD counters.** Our build takes a
> `SYSRESETREQ` at t ≈ 0.104 s, which resets the peripheral models, so the
> end-of-run `spim_a.jbd FrameCounter` / `JournalCount` readouts come back
> **0** even though the panel really was driven. The ordered transaction log
> `spim_a.p1.trace` (33 transactions, including three pixel windows) is the
> authority and is what §2's G-3/G-5 rows are measured from.

## 2. Per-criterion table (iteration 16 final, `g1-i16b-app`)

| id | criterion | verdict | vs iter 15 | evidence |
|---|---|---|---|---|
| **S-IMU** | `twim2` LSM6DSO stream hash per phase | **PARTIAL** | **969 → 25 txns** (regression, §4) | `p1_boot` 25 txns vs oracle 1 089; first **3** transactions byte-identical, first difference still at txn **#3**. `p2_render` **0** (oracle 1 200). |
| **S-ALS** | `opt3001_ambient_light` stream hash | **PARTIAL (prefix-exact)** | unchanged | `p1_boot` 7 txns vs 33; **all 7 byte-identical to the oracle's first 7**, then ours stops. `p2_render` 0 vs 80. |
| **S-PMIC** | `npm1300_charger_fuelgauge` stream hash | **PARTIAL** | unchanged (85 txns) | `p1_boot` 85 txns vs oracle 291 (270 after the RLE collapse); still diverges at txn **#0**. `p2_render` 0 vs 508. |
| **S-NFC** | `st25dv_nfc_eeprom` + `st25dv_system_port` | **PARTIAL / NOT-EXERCISED** | unchanged | system port `p1_boot` 6 txns vs 22, **all 6 byte-identical**, then stops. NFC EEPROM (`0x53`) **0** vs 25 — and iteration 16 **root-caused why**: see §3. |
| **S-ADC** | `saadc` whole-run stream hash | **PARTIAL (prefix-exact)** | **gain error GONE** | 5 register accesses vs 998; all 5 byte-identical to the oracle's first 5, then the conversion cycle never runs. The `<err> adc_nrfx_saadc: Selected ADC gain is not valid` message **no longer appears**: it is logged at t=0.0898 s by `g1-i16-app` and is absent from `g1-i16b-app`, which reaches a strictly *later* point (fault at 0.104 s) — so it is genuinely fixed, not merely unreached. The stage-a3 `.data` restore is the only change between the two builds; **which** restored word supplies the gain is not yet pinned down. |
| **S-KEYS** | `gpiote0` whole-run stream hash; `gpiote1` count == 0 | **PASS** | unchanged | `gpiote0` **stream_sha256 identical** (`2f47878f…`), 25 accesses = 25. `gpiote1` **0 == 0**. |
| **S-MIC** (negative) | `pdm0` == exactly 2 writes, no ENABLE/START | **PASS** | unchanged | `pdm0` **stream_sha256 identical** (`255852a6…`). |
| **gyro** (negative) | `CTRL2_G` stays 0 / gyro never enabled | **PASS (weak)** | unchanged | `GyroscopeEnabled` = **False**, matching the oracle. **Caveat unchanged:** `AccelerometerEnabled` is also **False** (oracle **True**), so the negative criterion holds for the wrong reason. |
| **S-ESB** | ESB sync reaches 0x02, display-on 0x01, PTX > 0 | **FAIL (not reached)** | unchanged | `radio TransmittedFrames` = 0 (oracle 0x230), `esbslave MasterFramesSeen` = 0 (oracle 0x175), both context bytes `0x00` (oracle `0x01` / `0x02`). |
| **G-1** | `framebuffer.p2_render.sha256` | **FAIL** | still failing, now for a *narrower* reason | ours `0c5cc90b…`, **0 lit px**; oracle `b26c73b3…`, **1 098 lit px**. The panel is correctly *cleared*; the dashboard is never painted because the SoC resets first. |
| **G-2** | `framebuffer.p1_boot.sha256` | **FAIL** | as above | ours `0c5cc90b…`, 0 lit px; oracle `1d617c65…`, 656 lit px. |
| **G-3** | `spim_a` ordered byte stream per phase | **FAIL (truncation only)** | **0 → 33 txns; prefix now exact** | `p1_boot` ours sha `8df70cec…` vs oracle `b64599b1…`, **33 vs 764** transactions. **All 33 shared transactions are byte-identical**; the divergence is pure truncation at index 33 (`0xB9 tx=B9FF`). `p2_render` 0 vs 2 881. |
| **G-4** | *(localiser only)* first differing row | **localised** | newly usable | **first differing row y = 267, first differing pixel x = 178** (oracle `ffffff`, ours `000000`) — precisely the top-left corner of the oracle's lit bbox (178,267)–(449,287). |
| **G-5** | panel init: `0x9F`→`0x4010`, three-band 153 600 B clear, five `0xC0` words, `0x46`/`0x31` pairs `0F 04` / `00 04` | **PASS** | **UNTESTED → PASS** | All four enumerated elements reproduced **byte-exactly** — see §3. |
| **G-6** | `spim_b` transaction count == 0 | **PASS** | **vacuous → genuine** | ours 0 == oracle 0, and our build now really does drive `spim_a` (33 txns) and not `spim_b`, so this no longer passes for the wrong reason. |

Score: **5 PASS** (S-KEYS, S-MIC, gyro-negative, **G-5**, G-6), **5 PARTIAL**
(S-IMU, S-ALS, S-PMIC, S-NFC, S-ADC), **4 FAIL** (S-ESB, G-1, G-2, G-3).
Compared with iteration 15 (3 PASS + 1 vacuous, 5 PARTIAL, 1 FAIL, 3 NOT
REACHED, 1 UNTESTED), the graphics half of the gate moved from *unmeasurable*
to *measured*, and **G-5 is the first display criterion this project has ever
passed**.

## 3. G-5 — the panel-init sequence, transaction by transaction

Our first 33 `spim_a` transactions are **byte-identical** to the shipped
firmware's, covering the whole §3.1 init block:

| idx | oracle | ours |
|---|---|---|
| 0–3 | `0x66` / `0x99` / `0x06` / `0x01 tx=0110` | identical |
| 4–6 | `0x02` len **61446** / **61446** / **30726** (= 153 600 pixel bytes, three 192/192/96-row bands) | identical |
| 7–16 | five `0xC0` words `0000`, `0014`, `1800`, `1814`, `0C0A`, each followed by `0x97` | identical |
| 17–20 | `0x71` / `0x97` / `0x73` / `0x97` | identical |
| 21–24 | `0x46 tx=460F`, `0x31 tx=3104` (**brightness pair `0F 04`**), `0xA3`, `0x97` | identical |
| 25–27 | `0x06` / `0xA9` / `0x36 tx=360612` | identical |
| 28–31 | `0x46 tx=4600`, `0x31 tx=3104` (**brightness pair `00 04`**), `0xA3`, `0x97` | identical |
| **32** | **`0x9F tx=9F000000 rx=00004010`** — the panel ID probe, answered `0x4010` and accepted | **identical** |
| 33 | `0xB9 tx=B9FF` | **absent** — the SoC resets here |

All four elements the G-5 criterion enumerates are therefore reproduced
exactly. The single §3.1 item we do not emit is the trailing `0xB9 FF`, and it
is missing because of the §4 fault, not because of a wrong byte.

## 4. First differences and the current blocker

### The new blocker: a NULL `.data` function pointer (NFC EEPROM ops table)

Our build now takes a **USAGE FAULT / "Illegal use of the EPSR"** (INVSTATE) at
t ≈ 0.104 s and resets:

```
0x0002c6fe:  4798  blx r3      ; in attr_store_get, r3 = *(*(&g_pt_nfc_link_cfg)) = 0
>>> ZEPHYR FATAL ERROR 35 ; fatal_error: Resetting system
```

`pt_nfc_eeprom_link_start` passes `&g_pt_nfc_link_cfg_static` (arena **+0x408**)
to `pt_nfc_eeprom_link_init`, which returns −1 unless the first four words are
all non-zero. The shipped `.data` there is the ops table
`{ 0x00030c25, 0x00030c61, 0x0007d0c1, 0x0007d0c3, 0x00087c50, 0x6b }`; our
build zeroes it, so the guard fails (measured: 1 entry / **8 instructions**),
`g_pt_nfc_link_cfg` stays NULL, and `attr_store_get` dereferences it. **This is
also exactly why S-NFC's `st25dv_nfc_eeprom` (0x53) has 0 transactions** — the
NFC user-memory path is gated on this table.

Iteration 16's stage-a3 restore cannot fix it yet because none of the five
pointers resolves: `0x30c24` (`misc_dev_api_transfer_op12`) was
**garbage-collected** (the zeroed table was its only referrer), `0x30c60`,
`0x7d0c0` and `0x7d0c2` are **interior** to catalogued functions (the recurring
Ghidra fold), and `0x87c50` is a `struct device` named **`"i2c@b000"`** (i2c2)
needing `DEVICE_DT_GET`. Full detail in `our_boot_bringup.md` §16.5.

### Why the sensor volumes went DOWN this iteration

Iteration 15's final build spun forever in `nrfx_spim_xfer` but **stayed
alive**, so the periodic sensor threads kept running for the full 6 s of
`p1_boot`. Iteration 16 fixed that spin, ran further, and then **died at
0.104 s**. Renode's nRF5340 platform has no reset macro, so both cores halt
there and nothing runs afterwards.

| device | oracle `p1_boot` | `g1-i15e-app` | **`g1-i16b-app`** |
|---|---:|---:|---:|
| `twim2` LSM6DSO | 1 089 | 969 | **25** |
| `twim1` nPM1300 | 291 | 85 | **85** |
| `twim1` OPT3001 | 33 | 7 | **7** |
| `spim_a` | 764 | **0** | **33** |

This is an honest regression on sensor volume and a large advance on display
parity. Both are reported; neither fix is reverted, because each is proven
against the shipped disassembly (§3 and `our_boot_bringup.md` §16.1–16.2).

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

Unchanged from iterations 14 and 15: after the WHO_AM_I handshake the original
does a read-modify-write of **`CTRL9_XL` (0x18)** inside `lsm6dso_init_chip`,
while ours writes **`FUNC_CFG_ACCESS ← 0x80`** and reads `0x46`
(`FSM_ENABLE_A`) in an embedded-functions bank the original never enters, via
`mem_bank_set` / `fsm_enable_get` / `attr_set`.
**Classification: recon defect.** **Not fixed this iteration** — the SPIM
root-cause, the relocation-aware `.data` work and the G-5 measurement consumed
the budget. Next step unchanged: re-derive `lsm6dso_init_chip` and the
`dev_api_call_slot0` dispatch against the shipped disassembly.

### S-PMIC — nPM1300 on `twim1` @0x6B (first divergence still at transaction #0)

```
#0  oracle W 0x6B 060206   ours W 0x6B 040F   <<< FIRST DIFFERENCE
#1  oracle W 0x6B 061600   ours R 0x6B 00
#2  oracle W 0x6B 060C00   ours W 0x6B 0410
#3  oracle W 0x6B 061100   ours R 0x6B 17
```

The original opens with a **bank-0x06 register-write burst** (the GPIO /
ship-mode block); ours opens with **bank-0x04 register reads**. Same device,
same addressing, different init-routine ordering.
**Classification: recon defect (init-sequence ordering). Not fixed this
iteration.**

### S-ALS, S-NFC (system port), S-ADC — prefix-exact, then stop

Byte-identical for every transaction our build makes, then they stop while the
oracle continues (OPT3001 through `CONFIG ← CE10`; ST25DV system port through
`W 0017` / `R 24`; SAADC through `INTENSET ← 0x12`).
**Classification: not-yet-reached**, now because of the §4 reset.

## 5. Honest summary

* **5 criteria pass outright**: S-KEYS, S-MIC (negative), gyro (negative),
  **G-5**, and G-6 — all by exact stream-hash / byte-sequence equality, not by
  inspection.
* **G-5 is the headline**: the panel-init block is byte-identical to the
  shipped firmware for all 33 transactions we emit, including the
  `0x9F`→`0x4010` ID probe and the full 153 600 B three-band clear. G-3 fails
  **only by truncation** — every shared transaction matches.
* **G-1/G-2 fail** with 0 lit pixels: our panel is correctly cleared but never
  painted, because the SoC resets at 0.104 s. G-4 localises the first
  difference to row 267, pixel 178.
* **5 are partial.** Three (S-ALS, S-NFC system port, S-ADC) are **byte-exact
  for every transaction we emit**. Two (S-IMU, S-PMIC) are genuine recon
  defects with named first-differing registers, unchanged this iteration.
* **Sensor volumes regressed** (S-IMU 969 → 25) because the boot now dies
  earlier. Reported, not hidden; see §4.
* **S-ESB fails**: `radio TransmittedFrames` = 0.
* The single highest-value next fix is the §4 NFC ops table: it is the current
  first divergence, it directly explains S-NFC, and clearing it should restore
  the sensor volumes *and* let the dashboard paint.
