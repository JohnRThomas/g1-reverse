# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**Eighth measurement of `display_sensor_parity.md`'s criteria against our
rebuild** (iteration 21; previous measurements were iterations 14–20).

## READ THIS FIRST — iteration 21 is a partial capture and a reset REGRESSION

Iteration 21 closed the iteration-20 first divergence: `device_info[0x1058]` is
now **1** (was 0), the CPUNET's `0x0601` "ready" IPC message arrives, and
`bt_start()` runs past its state guard for the first time in this project
(`our_boot_bringup.md` §21.1–§21.4).  `bt_enable()` now completes at
**t = 1.397 s** instead of t = 5.100 s.

**But the app core no longer survives 8 s.**  Immediately past that guard,
`bt_start` formats the advertised device name through
`__sprintf_chk(dst, 0, 0x20, "%s_R_%02X%02X%02X", "Even G1", 0xff, 0xff, 0xff)`,
the recovered `_svfprintf_r` returns **131** for what should be a 16-character
result, the FORTIFY check fires and `k_oops()` resets the SoC at
**t = 1.4026 s** (`our_boot_bringup.md` §21.7).  Two of the three causes of that
were fixed this iteration (§21.5 the 2,128 absolute `rodata_*` pins, §21.6
`g_libc_heap_ctrl` = `_impure_ptr`); the third is named and NOT fixed.

Consequences for this file, stated plainly:

* **Every `p2_render` column below is from ITERATION 20 and is NOT re-measured.**
  The iteration-21 capture crashed **Renode itself** on entry to phase 2
  (`System.Threading.SemaphoreFullException` inside
  `Antmicro.Renode.UI.ConsoleIOSource`, see
  `/private/tmp/g1_ours_i21/run.out`) — an emulator-harness failure, not a
  firmware result — so `spim_a.p2.trace`, `twim1.p2.trace`, `twim2.p2.trace` and
  the `p2_render` framebuffer are **absent**.  Nothing is claimed for them.
* **The `p1_boot` half WAS captured and is reported below**, and it is a
  regression in *depth* for three sensors, because the app core reboots roughly
  every 1.4 s inside the 6 s phase-1 window.
* **No verdict cell changes.**  Score is still 5 PASS / 5 PARTIAL / 4 FAIL.

### Iteration 21 `p1_boot`, actually measured

| device | oracle | iter 20 | **iter 21** | note |
|---|---:|---:|---:|---|
| `spim_a` | 764 | 34 | **34** | the trace is **identical to iteration 20 modulo the `tick=` column** (verified with `sed 's/ tick=[0-9]*//' \| cmp`), so G-3's and G-5's iteration-20 findings carry over exactly |
| `spim_b` | 0 | 0 | **0** | byte-identical file (G-6 PASS) |
| LSM6DSO (twim2) | 1,089 | 1,027 | **551** | **regression** — the reboot loop truncates it |
| nPM1300 (twim1 0x6B) | 291 | 232 | **97** | **regression** |
| OPT3001 (twim1 0x45) | 33 | 14 | **14** | unchanged |
| ST25DV system port (0x57) | 22 | 12 | **6** | **regression** |
| ST25DV NFC EEPROM (0x53) | 25 | 11 | **0** | **regression** — never reached before the first reset |
| framebuffer `p1_boot` | 656 lit px | 0 lit px | **0 lit px** | `fb_p1_boot.ppm` is **byte-identical to iteration 20** (`cmp`), so G-2 and the G-4 localiser (first differing row y = 267, first differing pixel x = 178) carry over unchanged |
| `JBD_FRAMECOUNTER_P1` | 0x2A1 | 0x3 | **0x0** | |

**Not one pixel was painted, and that is stated plainly.**  `radio
TransmittedFrames` = 0 and `vcentral Connected` = False in the 8 s boot of the
iteration-21 pair, exactly as in iteration 20.

**The iteration-20 pair (`g1-i20a-app` + `g1-i20d-net`) therefore remains the
best-scoring build on this file's criteria**, and the tables in §2/§3 below are
its measurement, unchanged.  The iteration-21 pair
(`g1-i21b-app` + `g1-i21c-net`) is ahead on the *boot chain* and behind on the
*reset metric*; both are reported.

### Reproduce the iteration-21 `p1_boot` capture

```sh
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i21b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i21c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i21
```

Run it in the FOREGROUND: backgrounding it is what tripped Renode's console
IO source above.

---

## Everything below this line is the ITERATION 20 measurement, unchanged

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
