# Where the "~2.9 µs per byte" comes from — a measurement pass

**Question (`our_boot_bringup.md` §48.13 item 1):** the phase criterion gates
refactor stages on a boot-path offset that moves monotonically with `zephyr.bin`
size at ~2.9 µs/byte, *for bytes no instruction reads or executes*.  If that
slope is a Renode artefact, the criterion measures the emulator, not the
firmware.

**ANSWER: it is neither a Renode artefact nor firmware-real.  It is FOUR
raw absolute string addresses left in our own reconstruction.**  They are passed
to `log_message()` as format pointers.  In the shipped image those addresses
hold real format strings; in our relinked image they hold unrelated `.rodata`,
so `printf` walks memory to the next NUL byte.  Move the image and the walk
gets longer.  Four such sites → **4.00 printed characters per byte of image
shift**, ~93 executed instructions per character → **~4.0 µs per byte**.

Suppressing exactly those four calls in the emulator, with the image byte
**untouched**, collapses the whole 420-byte / 1.140 ms boot-offset spread of
§48.11's family — base, `s04`, `T14` and every pad — to **0.000 ms and an
identical instruction count**.

Every number below is from a command run in this pass.  This pass changed no
firmware source, no gate parameter, no transformer and no emulator model.

---

## 1. Re-derivation of the slope — §48's headline number is wrong

`bash /private/tmp/g1-i49/boot2.sh` reproduces §48.11's table exactly from the
captures still on disk; those captures are not stale.  But the slope §48 quotes
is computed across the in-tree base, which §48.11 itself flags as off the line.

Within the semantics-free pad family (`T14` + inert `.text` pad, one source):

`(79.440 − 78.610) ms / (956,284 − 956,076) B` = **3.99 µs per byte**, not 2.7
and not 2.9.

Second, independent family (`NONE` symbol set + pad), same slope:
`(80.180 − 79.440) / (956,484 − 956,292)` = **3.85 µs/B**;
`nonepad136 → nonepad200` = `0.250 / 64` = **3.91 µs/B**.

**Correcting §48.6.1 and §48.11: the semantics-free slope is ~3.9–4.0 µs/byte.**

## 2. Renode's virtual time is instruction count / 100 MIPS

Probe `/private/tmp/g1-i50/mark.sh`: boot symbols hooked at addresses re-read
from each ELF, printing `machine.ElapsedVirtualTime` and
`cpuapp.ExecutedInstructions`.

```
MARK z_arm_prep_c  vt=3.47 µs      i=347
MARK z_data_copy   vt=7573.09 µs   i=757309
MARK main          vt=53870.45 µs  i=5386980
```

`vt(µs) = insns / 100` **exactly** at every marker where the core never idles.
So a per-byte *time* cost must be a per-byte *executed-instruction* cost.  There
is no flash model, no image-load charge and no per-page cost that could invent
virtual time: **the "Renode's own execution model" candidate is ruled out by
construction.**  (There is also **no MCUboot in this emulation** — `g1-ours.resc`
`LoadELF`s the two images directly and sets the reset vectors, so the
"bootloader hashes the image" candidate is ruled out too.)

## 3. The cost is NOT in the boot path.  `z_bss_zero` / `z_data_copy` are clean.

`T14` (956,076 B) vs `T14pad200` (956,284 B), `G1_SEED=305419896`, `RunFor 0.2`:

| marker | `T14` insns | `T14pad200` insns | Δ |
|---|---:|---:|---:|
| `__start` | 0 | 0 | 0 |
| `z_arm_prep_c` | 347 | 347 | **0** |
| `z_bss_zero` | 367 | 367 | **0** |
| `z_data_copy` | 757,309 | 757,309 | **0** |
| `z_cstart` | 780,122 | 780,122 | **0** |
| `bg_thread_main` | 1,327,653 | 1,327,653 | **0** |
| `main` | 5,386,980 | 5,386,980 | **0** |
| `runtime_info_sync` (1st) | 5,873,840 | 5,894,337 | **+20,497** |
| twim1 first tick | 53.390 ms | 53.390 ms | **0** |
| twim2 first tick | 78.610 ms | 79.440 ms | **+0.830 ms** |
| spim_a first tick | 107.010 ms | 107.830 ms | +0.820 ms |

Measured, not assumed: **`z_bss_zero` and `z_data_copy` execute the identical
instruction count** — the pad is in `.text`, neither `.bss` nor `.data` changes
size, and iteration 43's `+3.45 ms` mechanism is not this one.  Idle time is
identical too (1,394.27 µs in both at the first `runtime_info_sync`), so the
delta is 100 % *executed* work.

## 4. The work is console printing — and the extra characters are garbage

Renode guest profiler (`EnableProfilerCollapsedStack`), leaf instruction counts
over a 0.1 s run, `T14` → `T14pad200`:

```
uarte_nrfx_poll_out    +37,493   calls 12,251 -> 16,415
z_cbvprintf_impl       +11,746   calls  2,288 ->  3,121
is_tx_ready.isra.0     +11,665
pm_device_state_get     +8,329
g1_vprintf_char_out     +7,492
k_is_in_isr             +4,154
                       -------
                       ~80,879 of the +77,466 total leaf delta
```
*(`qspi_workaround_apply −59,064` / `nrf_qspi_pins_set +59,064`, identical call
counts, are a nearest-symbol attribution artefact of the profiler across the
moved code and cancel exactly.)*

`sysbus.uart0 CreateFileBackend`, same runs:

```
T14        uart0 = 2,450 bytes
T14pad200  uart0 = 3,283 bytes      +833
```

The extra 833 bytes are **binary `.rodata` printed as text**.  First divergence
is immediately after `set testmode is 0`, where the **shipped** firmware prints
`role_init(): Master!------`.

## 5. The four defective call sites, named

Hooking `log_message` and dumping `r0` (the format pointer) on both images:
**every call site's `r0` moves by exactly +208** — the `.rodata` shift — **except
four, whose `r0` is a fixed constant**:

| `r0` (does not relocate) | LR | function | what lives at that address **in the shipped image** |
|---|---|---|---|
| `0x00099919` | `0x00017cb1` | `main` | `"%s(): Master!------\n"` |
| `0x000993c9` | `0x00013c23` | `power_for_panel` | `"%s(): set buck2 to 1.2v\n"` |
| `0x0009943c` | `0x00013bbd` | `power_for_panel` | `"%s(): turn on -2v for panel.\n"` |
| `0x00099476` | `0x000164bf` | `power_for_imu_and_mic` | `"%s(): enable ldsw2 for imu and mic\n"` |

(shipped strings read with `tools/extract.py`; all four appear correctly in a
shipped-image UART capture — `role_init(): Master!------`,
`power_for_panel(): set buck2 to 1.2v`, `power_for_panel(): turn on -2v for
panel.`, `power_for_imu_and_mic(): enable ldsw2 for imu and mic`.)

The sources:

```
recon/app/src/main.c:240             log_message(0x00099919, 0x00099b4c);
recon/app/src/main.c:241             debug_print(0x00099919, 0x00099b4c);
recon/app/src/FUN_00015df4.c:52      puVar3 = (unsigned char*)0x000993c9;
recon/app/src/FUN_00015df4.c:77      puVar3 = (unsigned char*)0x0009943c;
recon/app/src/power_for_imu_and_mic.c:17  DEBUG_PRINT(... : 0x00099476, 0x00099c28);
```
and, in the tree the ladder actually builds,
`recon/refactor/stage_07_internal_linkage/tree/recon/symbolized/app/display/g1_display_01.c:224,248`
plus the corresponding `main.c` / `power_for_imu_and_mic.c`.
`recon/symbolized/app/main.c:308` shows the shape precisely — the *second*
argument was symbolized (`((unsigned long)"role_init") /*=0x99b4c*/`) and the
**format pointer was left as the raw address `0x00099919`**.

In our link, `0x00099919` lands inside a float table.  `printf` prints from
there to the next NUL.  `T14` finds one 19 bytes later; `T14pad200`, whose
`.rodata` sits 208 bytes higher under that same fixed address, finds one 228
bytes later.

## 6. The arithmetic closes exactly

Pad sweep, one 0.1 s seeded run per point (`/private/tmp/g1-i50/sweep.sh`):

| pad | `zephyr.bin` | uart0 bytes | twim2 t0 | cpuapp insns |
|---:|---:|---:|---:|---:|
| 0 | 956,076 | 2,450 | 78.610 ms | 6,103,190 |
| 16 | 956,092 | 2,515 | 78.700 | 6,109,464 |
| 48 | 956,124 | 2,643 | 78.820 | 6,121,891 |
| 64 | 956,140 | 2,707 | 78.860 | 6,128,079 |
| 80 | 956,156 | 2,771 | 78.950 | 6,134,532 |
| 96 | 956,172 | 2,835 | 78.980 | 6,140,749 |
| 104 | 956,188 | 2,899 | 79.040 | 6,146,948 |
| 120 | 956,204 | 2,963 | 79.100 | 6,153,176 |
| 152 | 956,236 | 3,091 | 79.220 | 6,162,040 |
| 184 | 956,268 | 3,219 | 79.350 | 6,174,458 |
| 200 | 956,284 | 3,283 | 79.440 | 6,180,656 |

**Exactly 64 extra printed characters per 16 bytes of pad = 4.0000 chars per
byte** — one per bogus site, dead linear over the whole sweep.
`833 chars / 208 B = 4.0048`; `77,466 insns / 833 chars = 93.0 insns/char`;
`0.830 ms / 833 chars = 996 ns/char`; `→ 3.99 µs per image byte`.
The 0.1 s probe reproduces §48's full-capture `twim2` t0 **to the tick** on all
eleven points, so it is a faithful, cheap proxy.

## 7. THE CONTROL — suppress the four calls, keep the image byte-identical

A Renode hook at `log_message` returns immediately (`cpu.PC = cpu.LR`) **iff**
`r0` is one of the four addresses.  No image, no source, no linker script and no
emulator model is modified; only those four diagnostics are removed.

| image | `zephyr.bin` | uart0 | twim2 t0 | cpuapp insns |
|---|---:|---:|---:|---:|
| `T14` | 956,076 | **1,492** | **77.650 ms** | 6,017,499 |
| `T14pad48` | 956,124 | **1,492** | **77.650** | 6,017,499 |
| `T14pad96` | 956,172 | **1,492** | **77.650** | 6,017,499 |
| `T14pad200` | 956,284 | **1,492** | **77.650** | 6,017,499 |
| `s04` (= `a105`) | 956,292 | **1,492** | **77.650** | 6,017,513 |
| **in-tree base** | **956,496** | **1,492** | **77.650** | 6,017,513 |

All six `uart0.txt` are **`cmp`-identical**.  §48.11's spread — 78.610 … 79.750,
**1.140 ms over 420 bytes** — becomes **0.000 ms**, and the residual
instruction-count difference between the base and `T14` is **14 instructions
(0.14 µs)**, which is the real semantic difference the 14 static-ifications make.

> **The per-byte boot cost is exactly zero once four bogus `printf` format
> pointers are removed.  There is no cost per byte of image.  There is a cost
> per character of garbage, and the garbage length is a function of link layout.**

---

## 8. Answers to the three questions the brief asked

### 8.1 Where does the time go
Into `z_cbvprintf_impl` → `g1_vprintf_char_out` → `uarte_nrfx_poll_out`, at
~93 executed instructions per character, printing 361–1,514 bytes of `.rodata`
that four `log_message()` calls mistake for format strings.  Ruled out **by
measurement**, not assumption: `z_bss_zero` (Δ0 insns), `z_data_copy` (Δ0),
everything before `main` (Δ0), MCUboot (absent from the emulation), Renode's
time accounting (virtual time = insns/100 MIPS, exactly), linker alignment
(the whole effect vanishes under the control while the image is unchanged).

### 8.2 Firmware-real or emulator-only
**Neither, and this is a third category the brief did not anticipate: a
reconstruction defect.**

* It is **not a Renode artefact.** Renode is faithfully charging time for
  instructions the firmware really executes. Real silicon would pay *more*: a
  115200-baud console spends ~87 µs per character against Renode's ~1 µs, so
  the emulator **understates** this by roughly two orders of magnitude.
* It is **not firmware-real** in the sense that matters. The **shipped**
  firmware does not do it: the shipped image prints the four intended strings
  and its console output has no layout-dependent length. The size sensitivity
  exists only in our rebuild.
* So the criterion is measuring **our firmware** — correctly — but what it is
  measuring at the margin is a **bug in the reconstruction that is unrelated to
  any refactor stage**.

### 8.3 Consequence for the criterion — stated honestly

The criterion's **mechanism is sound**: it compares peripheral-transaction
timing, virtual time is a faithful function of executed instructions, and the
BLE-slot quantisation `criterion_bound_redesign.md` derives is real.  It is not
measuring the emulator.

But its **current sensitivity is dominated by a defect**.  Any refactor that
moves `.rodata` by N bytes shifts the boot path by ~4N µs *for reasons that have
nothing to do with the refactor*, and §48 showed 16 bytes is enough to cross a
BLE connection-event boundary and flip the verdict.

Concretely:

* **§48.8's sentence "this emulator's boot path costs ~2.7 µs per byte" is
  wrong and I am contradicting it plainly.** The boot path costs nothing per
  byte. §48's *conclusion* — that stage 07's gate failure is caused by image
  size and not by internal linkage, and is reproduced by inert padding —
  **survives intact and is now explained**: §48.13 item 1 is closed.
* **The stage 07 FAIL is an artefact of the four literals, not of stage 07.**
  So is P4 iter-46's "a 204-byte inert pad flips the gate" for stage 04. Any
  verdict on a stage declared `size-changing` whose failure is a *timing*
  displacement — README rows 01, 04/04-B, 07 (and 05/06/08 inheriting) — is
  contaminated in proportion to how far that stage moved `.rodata`. Verdicts
  resting on `cmp`-identical captures, on counts, on framebuffers, or on the
  `byte-identical` stages (02, 03) are unaffected.
* **A sound criterion needs the defect removed, not the bound widened.** Fixing
  the four literals (they are ordinary symbolization misses; the correct string
  is known for each) removes ~4 µs/byte of layout noise from every future gate
  run and would let stage 07's 14 symbols be judged on their semantics. That is
  the single highest-value repair available to the phase criterion — **and this
  pass deliberately did not perform it.**
* **The gate that should have caught this does not exist.**
  `check_ram_pin_collisions.py` scores linker-script pins in the **RAM** window;
  `check_net_raw_literals.py` scores source literals `0x21xxxxxx` in **net-core
  RAM**. Neither can see an app-core **flash** `.rodata` address written into a
  C body. The stage-07 tree that the ladder builds contains **117 distinct
  raw `0x0009xxxx`–`0x000exxxx` literals in 284 occurrences across 107 files**
  (C comments and string bodies excluded); four are demonstrably live on the
  boot path. That count is an upper bound on the class, not a defect count —
  many are legitimate references to blob/table extents — but nothing measures
  which.

---

## 9. What I did NOT determine

1. **Which of the other 113 raw flash literals are live and wrong.** Only the
   four that fire in the first 100 ms of a seeded boot were identified, by
   hooking `log_message`. A `debug_print`-routed variant (`g_log_use_alt_sink`
   ≠ 0) was never exercised — the flag is 0 in every run here.
2. **Whether removing the four literals actually makes stage 07 PASS.** The
   control proves the *boot offset* collapses; it does not prove the
   slot-quantised gate returns 0 failures, because I ran no full 20 s
   two-stimulus capture under the control. That needs a build, and building is
   a repair.
3. **The −37.3 ms / −29.0 ms structural offsets vs shipped** (§48.13 item 10).
   Our base prints 3,603 console bytes against the shipped image's 2,089; the
   1,514-byte excess is worth ~1.4 ms, i.e. ~5 % of the dashboard offset. The
   rest is unexplained and untouched.
4. **Only one seed** (`305419896`), as in §47/§48. The control's result is a
   `cmp` on six images at that seed, not a distribution.
5. **The 956,180-byte "defect island"** is still corroborated, not proved
   (§48.13 item 2) — unchanged by this pass, though it is now expected: the
   verdict is a modular function of a smoothly-moving offset.
6. **`SweepDwell 4 → 8`** (§44.5) — still not run, eighth pass running.
7. **`cfg_verify` was not run** and is cited nowhere, per the standing rule.
8. **The net core was not built and not touched.**

## 10. Acceptance bar, re-measured in this pass

| gate | required | measured | |
|---|---|---|---|
| framebuffers, 4 classes | byte-identical | `nav p1_boot` 3/3, `nav p2_render` 3/3, `dash p1_boot` 4/4, `dash p2_render` 4/4 — `cmp` exit 0 against the shipped oracle, on the §48 captures still on disk | ✔ |
| `nm -u` app | 0 | **0** on base, `T14`, `a105` | ✔ |
| `nm -u` net | 0 | **0** | ✔ |
| duplicate globals | 0 | **0** on all three app images | ✔ |
| pin gates | 0 / 0 | `raw_literal_pins_inside_a_live_object` **0**, `bound_pins_escaping_their_owner` **0** (`bound_pins_ok` 627, `abs_symbols_not_in_linker_scripts` 3) | ✔ |
| `check_thread_create_stack_args --trials 120` | 10/10 | **10 / 10**, exit 0 | ✔ |
| `tools/verify_data.py` | 995/995 | **995 / 995 files, 56,279 / 56,279 B, 100.00 %** | ✔ |
| refactor test suite | 215/215 | **215 / 215 OK** | ✔ |
| net `zephyr.bin` FROZEN | 225,581 B | **225,581 B**, sha256 `e09b9481a3154e16…`, not rebuilt | ✔ |
| app flash | re-measure | **956,496 B / 982,528 B = 97.35 %** (in-tree base; FLASH region `0x000efe00`) | measured |

`~/Projects/armemul` **not modified**: `models/BLE_VirtualCentral.cs` sha256
`1f10e117632a1bb3…`, `NRF5340_SPIM.cs` 3 `TraceFile` occurrences,
`NRF5340_TWIM.cs` 2 — both hooks intact, `git status` unchanged from the
pre-pass state.

## 11. Footprint

Repository: **this file only** (`recon/analysis/boot_cost_per_byte.md`, new).
No firmware source, no stage tree, no transformer, no gate parameter, no
emulator model, no oracle JSON, no golden framebuffer, nothing committed.
`W = 100.513 ms` and `R = 1.160 ms` are untouched.

Outside the repository (all new, all under `/private/tmp/g1-i50/`):
`mark.sh` (boot-marker probe), `prof.sh` (guest profiler), `uart.sh`,
`sweep.sh`, `fmt.sh` (format-pointer dump), `skip.sh` (**the control**),
`agg.py`, `agg2.py`, and their per-image output directories and `.resc` files.
`/private/tmp/g1-i49/**` and `/private/tmp/g1-i49-*` (§48's builds and captures)
were **read only**.

## 12. Reproducing

```sh
cd /Users/freedomcoder/Projects/G1disasm2

# the slope, from section 48's own captures
bash /private/tmp/g1-i49/boot2.sh

# where the instructions go
bash /private/tmp/g1-i50/mark.sh T14        0.2
bash /private/tmp/g1-i50/mark.sh T14pad200  0.2

# the four fixed format pointers  (look for dr0 == 0)
bash /private/tmp/g1-i50/fmt.sh T14
bash /private/tmp/g1-i50/fmt.sh T14pad200

# 4.00 characters per byte
for t in T14 T14pad16 T14pad48 T14pad64 T14pad80 T14pad96 \
         T14pad104 T14pad120 T14pad152 T14pad184 T14pad200; do
    bash /private/tmp/g1-i50/sweep.sh $t; done

# THE CONTROL -- image untouched, four calls skipped, slope becomes zero
for t in T14 T14pad48 T14pad96 T14pad200; do bash /private/tmp/g1-i50/skip.sh $t; done
bash /private/tmp/g1-i50/skip.sh base /private/tmp/g1-i48-base
bash /private/tmp/g1-i50/skip.sh s04  /private/tmp/g1-i49-a105
```
