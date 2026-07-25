# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**Sixth measurement of `display_sensor_parity.md`'s criteria against our
rebuild** (iteration 19; previous measurements were iterations 14–18).

Iteration 19 found that the iteration-18 blocker was a *symptom*: the buffer
handed to `bt_rpmsg_send` was **NULL** because `ancs_main` was calling
**`bt_send(NULL)` where the shipped firmware calls `bt_enable(NULL)`** — a stale
callee name that happened to resolve to a real Zephyr symbol, so the link bound
it silently and `.text.bt_enable` was garbage-collected.  Fixing that, plus a
`g1_ram_arena` that had been sized to a pin's *base* rather than its *extent*,
makes **the app core run 8.0 s with zero fatal errors — the first reset-free app
boot in this project.**  On the net core five further defects were fixed and the
Bluetooth host now comes up (`<inf> bt_hci_raw: Bluetooth enabled in RAW mode`).

**Every graphics and sensor number below is nevertheless UNCHANGED from
iteration 18, and that is reported plainly rather than dressed up.**  BLE still
does not advertise (`radio TransmittedFrames` = 0, `vcentral Connected` =
False), and the capture is still truncated inside `p1_boot` — now by the **net**
core, which takes a fatal at t = 5.0942 s immediately after `hci_driver_send()`
(`our_boot_bringup.md` §19.8) and, through Renode's nRF5340 reset path, halts
the app core with it.  No pixel was painted.

* Oracle (diff target): `recon/emulator/reports/display_sensor_oracle.json`
  (shipped `app_update.bin` / `netcore_image.bin`), criteria in
  `recon/emulator/reports/display_sensor_parity.md` §5.
* Our build: **`/private/tmp/g1-i19b-app/zephyr/zephyr.elf`** +
  **`/private/tmp/g1-i19e-net/zephyr/zephyr.elf`** (both rebuilt this
  iteration — see `our_boot_bringup.md` §19).
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
G1_APP_ELF=/private/tmp/g1-i19b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i19e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i19e

# (b) build the same JSON from our capture, into a SCRATCH report dir
PYTHONSAFEPATH=1 .venv/bin/python \
  recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i19e <SCRATCH>/g1-i19/rep_i19e

# (c) diff -- PER DEVICE, never the merged twim1 bus hash, plus the ordered
#     per-device RLE first-difference index
PYTHONSAFEPATH=1 .venv/bin/python <SCRATCH>/g1-i19/diff_parity.py \
  <SCRATCH>/g1-i19/rep_i19e/display_sensor_oracle.json
```

`G1_HOOKS=0` is required because the four `sysbus.cpuapp AddHook` PCs in the
oracle capture are **ORIGINAL-image** addresses; our build relocates them.
`G1_CTX_FE8` / `G1_CTX_105A` are the arena-relative equivalents of the
original's `device_ctx+0xfe8` / `+0x105a`.  **NOTE for the next iteration:**
`g1_ram_arena` moved this iteration (base 0x200030a0 → **0x20003100**, size
0x27000 → **0x28400**), so those two literals are now stale by +0x60; they are
observation-only counters (`DISPLAY_ON_ctx_fe8` / `ESB_SYNC_ctx_105a` read
`0x7C` instead of `0x00`) and affect no criterion, but the +0x60 shift makes the
correct values for this build **`G1_CTX_FE8=0x20055238`** and
**`G1_CTX_105A=0x200552aa`**; the capture above was run with the old ones and
those two counters must therefore be disregarded for iteration 19.

> **Our capture still dies inside `p1_boot`, at t = 5.0942 s.**  In iterations
> 16–18 that was the **app** core; it now survives (0 `ZEPHYR FATAL ERROR` in an
> 8 s app UART).  It is now the **net** core (§4.2), and Renode's nRF5340
> platform resets the SoC from it, which halts the app core too.  **That is why
> every `p2_render` column below is still zero.**

## 2. Per-criterion table (iteration 19, `g1-i19b-app` + `g1-i19e-net`)

| id | criterion | verdict | vs iter 18 | evidence |
|---|---|---|---|---|
| **S-IMU** | `twim2` LSM6DSO stream hash per phase | **PARTIAL** | unchanged (983 txns) | `p1_boot` 983 vs oracle 1,089; first **3** transactions byte-identical, first difference at txn **#3** (oracle `W 18`, ours `W 0180`). `p2_render` 0 (oracle 1,200). |
| **S-ALS** | `opt3001_ambient_light` stream hash | **PARTIAL (prefix-exact)** | unchanged (14 txns) | `p1_boot` 14 vs 33; **all 14 byte-identical**, then ours stops (oracle's #14 is `W 7E`). `p2_render` 0 vs 80. |
| **S-PMIC** | `npm1300_charger_fuelgauge` stream hash | **PARTIAL** | unchanged (199 txns) | `p1_boot` 199 vs 291; diverges at txn **#0** (oracle `W 060206`, ours `W 040F`). `p2_render` 0 vs 508. |
| **S-NFC** | `st25dv_nfc_eeprom` + `st25dv_system_port` | **PARTIAL** | counts unchanged; one payload byte moved | NFC EEPROM (0x53) **11** vs 25, first **6** byte-identical, first difference at **#6**: oracle `W 200200`, ours **`W 2002B8`** (was `W 200258` in iteration 18 — the written-back value is an arena-relative address and the arena moved; the *index* is unchanged). System port (0x57) **12** vs 22, first **10** byte-identical, first difference at **#10** (oracle `W 0001`, ours `W 000101`). |
| **S-ADC** | `saadc` whole-run stream hash | **PARTIAL (prefix-exact)** | unchanged (17 accesses) | first **5** register accesses byte-identical, first difference at **#5**: the oracle writes `CH[3].CONFIG` (0x548 ← 0x20000), ours goes straight to `CH[0].PSELP`.  UART confirms: `<err> adc_nrfx_saadc: Channel 3 not configured`.  17 vs 998. |
| **S-KEYS** | `gpiote0` whole-run stream hash; `gpiote1` count == 0 | **PASS** | unchanged | `gpiote0` **stream_sha256 identical**, 25 == 25.  `gpiote1` **0 == 0**. |
| **S-MIC** (negative) | `pdm0` == exactly 2 writes, no ENABLE/START | **PASS** | unchanged | `pdm0` **stream_sha256 identical**, 2 == 2. |
| **gyro** (negative) | `CTRL2_G` stays 0 / gyro never enabled | **PASS (weak)** | unchanged | `GyroscopeEnabled` = False, matching the oracle.  Caveat unchanged: `AccelerometerEnabled` is also False in both, so the criterion holds but is not discriminating. |
| **S-ESB** | ESB sync reaches 0x02, display-on 0x01, PTX > 0 | **FAIL (not reached)** | unchanged | `radio TransmittedFrames` = 0 (oracle 0x230), `esbslave MasterFramesSeen` = 0 (oracle 0x175), `vcentral Connected` = **False** (oracle True), `ConnectIndsSent` 0 vs 1.  Both context bytes read `0x7C` — a stale probe address, see §1. |
| **G-1** | `framebuffer.p2_render.sha256` | **FAIL** | unchanged | ours `0c5cc90b…`, **0 lit px**; oracle `b26c73b3…`, **1,098 lit px**. |
| **G-2** | `framebuffer.p1_boot.sha256` | **FAIL** | unchanged | ours `0c5cc90b…`, **0 lit px**; oracle `1d617c65…`, **656 lit px**. |
| **G-3** | `spim_a` ordered byte stream per phase | **FAIL (truncation only)** | unchanged (34 txns) | `p1_boot` **34 vs 764** transactions; **all 34 shared transactions byte-identical**; first difference at index **34**, where the oracle emits `{"op":"0x66","kind":"command","n_tx":1,"n_rx":1}` and we emit nothing.  `p2_render` 0 vs 2,881. |
| **G-4** | *(localiser only)* first differing row | **localised (unchanged)** | our framebuffer bytes are **bit-identical to iterations 16–18** (`0c5cc90b…`) | first differing row **y = 267**, first differing pixel **x = 178** (oracle `ffffff`, ours `000000`) — the top-left of the oracle's lit bbox (178,267)–(449,287).  Not re-derived: the sha is bit-identical, so the result carries over. |
| **G-5** | panel init: `0x9F`→`0x4010`, three-band 153 600 B clear, five `0xC0` words, `0x46`/`0x31` pairs `0F 04` / `00 04` | **PASS** | unchanged | all four enumerated elements byte-exact, including the trailing `0xB9 FF` at index 33. |
| **G-6** | `spim_b` transaction count == 0 | **PASS** | unchanged | ours 0 == oracle 0, hash EQ, and we genuinely drive `spim_a`. |

Score: **5 PASS** (S-KEYS, S-MIC, gyro-negative, G-5, G-6), **5 PARTIAL**
(S-IMU, S-ALS, S-PMIC, S-NFC, S-ADC), **4 FAIL** (S-ESB, G-1, G-2, G-3) —
**identical to iterations 17 and 18 in every cell.**  Iteration 19's work bought
no parity cell; it bought the app core's reset (which had gated every one of
them) being eliminated outright, and moved the remaining blocker onto the net
core one call past `hci_driver_send()`.

## 3. `p1_boot` transaction volumes

| device | oracle | `g1-i15e` | `g1-i16b` | `g1-i17d` | `iter 18` | **iter 19** |
|---|---:|---:|---:|---:|---:|---:|
| `twim2` LSM6DSO (0x6B) | 1,089 | 969 | 25 | 983 | 983 | **983** |
| `twim1` nPM1300 (0x6B) | 291 | 85 | 85 | 199 | 199 | **199** |
| `twim1` OPT3001 (0x45) | 33 | 7 | 7 | 14 | 14 | **14** |
| `twim1` ST25DV system port (0x57) | 22 | 6 | 6 | 12 | 12 | **12** |
| `twim1` ST25DV NFC EEPROM (0x53) | 25 | 0 | 0 | 11 | 11 | **11** |
| `saadc` register accesses (whole run) | 998 | — | 5 | 17 | 17 | **17** |
| `gpiote0` register accesses (whole run) | 25 | — | 25 | 25 | 25 | **25** (hash EQ) |
| `pdm0` register accesses (whole run) | 2 | — | 2 | 2 | 2 | **2** (hash EQ) |
| `spim_a` | 764 | 0 | 33 | 34 | 34 | **34** |
| `spim_b` | 0 | 0 | 0 | 0 | 0 | **0** (hash EQ) |

Every `p2_render` column is **0** in all of our builds, because the capture is
still truncated inside `p1_boot`.

## 3b. BOTH BUILDS: the reset-free-net variant reaches `p2_render`

The net fixes of `our_boot_bringup.md` §19.5–19.7 are provably correct but move
the boot *further into a new stall*, so the capture was **also** run with
`g1-i19b-net`, the last net build in which **neither core resets**.  Same
script, same determinism knobs, same stimulus (this run used the corrected
context-probe addresses `G1_CTX_FE8=0x20055238` / `G1_CTX_105A=0x200552aa`).

| device / phase | final tree (`i19e-net`) | **reset-free net (`i19b-net`)** | oracle | first difference |
|---|---:|---:|---:|---:|
| LSM6DSO `p1_boot` | 983 | **1,027** | 1,089 | #3 |
| LSM6DSO `p2_render` | 0 | **456** | 1,200 | **#456 — the entire 456-transaction prefix is byte-identical** |
| nPM1300 `p1_boot` | 199 | **232** | 291 | #0 |
| nPM1300 `p2_render` | 0 | **233** | 508 | #0 |
| `saadc` (whole run) | 17 | **53** | 998 | #5 |
| OPT3001 `p1_boot` | 14 | 14 | 33 | #14 (prefix-exact) |
| ST25DV sysport / EEPROM `p1_boot` | 12 / 11 | 12 / 11 | 22 / 25 | #10 / #6 |
| `spim_a` `p1_boot` / `p2_render` | 34 / 0 | **34 / 0** | 764 / 2,881 | #34 |
| `gpiote0` / `pdm0` / `spim_b` | 25 / 2 / 0 hash EQ | 25 / 2 / 0 **hash EQ** | 25 / 2 / 0 | — |
| framebuffer `p1_boot` / `p2_render` | `0c5cc90b…` 0 lit px | `0c5cc90b…` **0 lit px** | 656 / 1,098 lit px | — |

The extra live run time buys **real sensor traffic no previous iteration
reached** — the IMU's whole `p2_render` prefix is byte-identical to the
oracle's — but **not one lit pixel and not one extra `spim_a` transaction**,
because everything past `spim_a` index 34 is gated on the BLE link.  **No
criterion in §2 changes verdict**, so the table above is reported as additional
evidence, not as a score change.

Caveat, recorded plainly: Renode's stdout for that longer run is truncated after
`ORACLE_PHASE_BEGIN p2_render`, so its end-of-run **counter echoes** were not
captured; the transaction traces and both framebuffer dumps are complete and are
what the table is computed from.  `RADIO_TX` = 0 / `VC_CONNECTED` = False for
the same pair come from the separate 8.0 s boot run.

## 4. What moved this iteration

### 4.1 The app core no longer resets

| | iter 18 (`g1-i17d-app`) | **iter 19 (`g1-i19b-app`)** |
|---|---|---|
| `ZEPHYR FATAL ERROR` in the app boot UART | **1** (t = 5.093 s) | **0** (measured over 8.0 s) |
| `bt_enable` present in the ELF | **no** (`.text.bt_enable` GC'd, map address 0) | **yes, 0x55154** |
| `bt_enable(NULL)` actually executed | no | **yes, t ≈ 5.13 s** |
| HCI Reset (0x0c03) reaching `bt_rpmsg_send` | no | **yes, buf 0x2003f774, type 0** |
| app instructions @8.0 s | — | **16,942,935** |

Two defects, both measured, both in `our_boot_bringup.md` §19.1–19.2:

1. **`ancs_main` called `bt_send(NULL)` instead of `bt_enable(NULL)`.**  The
   shipped `ancs_main` executes `movs r0,#0 / bl 0x54a44` at 0x199a0, and the
   name catalogue already recorded 0x00054a44 as `bt_enable` ("the former
   bt_send label was an identity mismatch") — but the correction was never
   propagated into `ancs_main`'s callee `extern`, and `bt_send` is a real Zephyr
   symbol, so the cohesive link bound the wrong function with zero diagnostics.
   A Renode hook proved it: `RPMSG_SEND buf=0x0 type=0 lr=0x187f7`, i.e. the
   iteration-18 headroom assertion was simply `net_buf_simple_push` on a **NULL**
   buffer.  Fixed together with a dropped third argument to `bt_foreach_bond`.
2. **`g1_ram_arena` was sized to the highest pin's base, not its extent.**  The
   display thread's stack is `arena + 0x26e68` and 0x1400 bytes long, so its top
   0x1268 bytes lay outside the arena, on top of `backend_data_0`,
   `logging_thread`, `tx_thread_data` and `bt_workq` — and `bt_enable`
   initialises the last two, which is why this only detonated once `bt_enable`
   started working.  `G1_RAM_ARENA_LIMIT` raised 0x20029000 → 0x2002a400.

### 4.2 The CPUNET Bluetooth host comes up — and is the new first divergence

For the first time the CPUNET UART prints

```
[00:00:00.342,376] <inf> bt_sdc_hci_driver: SoftDevice Controller build revision: …
[00:00:00.342,529] <inf> bt_hci_raw: Bluetooth enabled in RAW mode
```

after five fixes (`our_boot_bringup.md` §19.3–19.7): `bt_enable_raw` and
`bt_buf_get_tx` and `z_isr_install` displaced onto their stock singleton owners,
the controller→host `k_fifo` and the HCI `struct ipc_ept` relocated off raw
addresses that aliased `hci_cmd_pool`/`sdc_mempool`, `CONFIG_MAIN_STACK_SIZE`
raised 512 → 1024 (measured: `z_arm_fault` psp 0x40 below `z_main_stack`), and
every recovered thread stack grown by the shipped 0x40 `K_KERNEL_STACK_RESERVED`.

The remaining divergence is:

```
<err> os: ***** Reserved Exception ( … ) *****     (CPUNET, t = 5.0942 s)
<err> os: Faulting instruction address (r15/pc): 0x00000000
<err> os: Fault during interrupt handling
```

A CPUNET PC trace across it ends `… FUN_0102acf4 → net_buf_get →
z_impl_k_queue_get → z_pend_curr → arch_swap → z_arm_pendsv → 0x0`, i.e. PendSV
restored **PC = 0** and `_kernel.cpus[0].current` is garbage.  It is reached only
through `hci_driver_send()`.  **Not yet root-caused**, and no guess is recorded
here as if it were.  The most likely home is the ledger in
`our_boot_bringup.md` §19.9: **93 raw `0x21xxxxxx` literals in the CPUNET
sources still land inside a live linked object**, 61 of them inside
`sdc_mempool` and 6 inside `_sw_isr_table`.

### 4.3 Why that still stops the painting

Unchanged and still the operative fact: the oracle's own `spim_a.p1.trace` has
**no SPI activity between 0.121 s and 3.92 s**, and every transaction after
index 33 is downstream of the BLE link — transactions 34–65 are a second full
panel init and 66+ are the 219-byte `0x02` pixel windows.  Our display driver
reproduces the oracle byte-for-byte for everything it is asked to do; it is
simply never asked to paint.

## 5. First differences that are genuine recon defects

### S-IMU — LSM6DSO on `twim2` (first divergence at transaction #3)

```
#0  oracle W 0x6B 0100   ours W 0x6B 0100     FUNC_CFG_ACCESS(0x01) <- 0x00
#1  oracle W 0x6B 0F     ours W 0x6B 0F       WHO_AM_I(0x0F) address
#2  oracle R 0x6B 6C     ours R 0x6B 6C       -> 0x6C, accepted
#3  oracle W 0x6B 18     ours W 0x6B 0180  <<< FIRST DIFFERENCE
```

Unchanged from iterations 14–19: the original does a read-modify-write of
**`CTRL9_XL` (0x18)** inside `lsm6dso_init_chip`, while ours writes
**`FUNC_CFG_ACCESS ← 0x80`** and reads `0x46` (`FSM_ENABLE_A`) in an
embedded-functions bank the original never enters.  **Classification: recon
defect.  Not fixed this iteration.**

### S-PMIC — nPM1300 on `twim1` @0x6B (first divergence at transaction #0)

```
#0  oracle W 0x6B 060206   ours W 0x6B 040F   <<< FIRST DIFFERENCE
```

The original opens with a **bank-0x06 register-write burst** (GPIO / ship-mode);
ours opens with **bank-0x04 register reads**.  **Classification: recon defect
(init-sequence ordering).  Not fixed this iteration.**

### S-NFC — first-difference registers

```
st25dv_nfc_eeprom (0x53)
  #6   oracle W 0x53 200200   ours W 0x53 2002B8   <<< FIRST DIFFERENCE
st25dv_system_port (0x57)
  #10  oracle W 0x57 0001     ours W 0x57 000101   <<< FIRST DIFFERENCE
```

Both are read-modify-write sequences where the value we write back differs.  The
EEPROM payload changed from `200258` to `2002B8` purely because `g1_ram_arena`
moved by +0x60 — i.e. the byte we write back is an **arena address**, which is
itself diagnostic: the original writes 0x00 there.  **Classification: recon
defect.  Not fixed this iteration.**

### S-ADC — missing channel configuration

The oracle configures **`CH[3]`** (`0x548 ← 0x20000`) before touching `CH[0]`;
we skip it and the driver logs `adc_nrfx_saadc: Channel 3 not configured`.
**Classification: recon defect (missing channel configuration).  Not fixed this
iteration.**

## 6. Honest summary

* **The app core is reset-free for the first time.** 0 `ZEPHYR FATAL ERROR` in
  an 8.0 s UART capture, against 1 (t = 5.093 s) in every iteration since 16.
* **`bt_enable` had never been called.** Its body was garbage-collected out of
  every previous build because `ancs_main` named the callee `bt_send`, and
  `bt_send` is a real symbol.  The iteration-18 "no headroom" assertion was
  `net_buf_simple_push` on a **NULL** buffer, not a pool defect — the
  iteration-18 hypothesis is corrected here.
* **The CPUNET Bluetooth host now comes up** (`Bluetooth enabled in RAW mode`,
  SoftDevice Controller build revision printed) after five further fixes.
* **BLE still does NOT advertise or connect.** `radio TransmittedFrames` = 0,
  `vcentral Connected` = False, `esbslave MasterFramesSeen` = 0.
* **No pixel was painted, and no graphics or sensor number changed.** G-1/G-2
  remain 0 lit px vs the oracle's 656 / 1,098; G-3 remains 34 of 764
  transactions with the whole 34-transaction prefix byte-identical and the first
  difference at index 34; G-5 and G-6 still **PASS**; the framebuffer sha is
  bit-identical to iterations 16–18, so G-4's localisation (row y = 267,
  pixel x = 178) carries over unchanged rather than being re-derived.
* **Score unchanged: 5 PASS / 5 PARTIAL / 4 FAIL.**
* **Next**: the CPUNET t = 5.0942 s fault (§4.2), then the 93-entry raw-literal
  ledger (`our_boot_bringup.md` §19.9) that is its most likely cause, then the
  named per-sensor defects above.
