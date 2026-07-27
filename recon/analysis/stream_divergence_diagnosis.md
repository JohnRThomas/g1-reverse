# Peripheral-stream divergence diagnosis — P4 iteration 41 residue

**Status: DIAGNOSIS ONLY. No source file outside this document was modified.**
Written to the §5.4 standard of `recon/analysis/staged_refactor_r7_validation.md`:
every claim is cited to a shipped-image address + instruction, or to a command
run against an on-disk capture, and every fix is stated at the level of
"this function, this line, this call, these arguments".

Baseline artifacts used (all already on disk; **Renode was NOT run** — the
concurrent repair agent owns it):

| role | directory | seeded? | image |
|---|---|---|---|
| shipped, navigation | `/private/tmp/g1_ship_seed_q1`, `…_q2` | **yes**, `emulation SetSeed 305419896` | `app_update.bin` + `netcore_image.bin` |
| ours, navigation | `/private/tmp/g1_i41c_nav_s1`, `…_s2` | yes, same seed | `g1-i41c-app` + `g1-i30e-net` |
| ours, dashboard | `/private/tmp/g1_i41c_dash` | yes, same seed | `g1-i41c-app` + `g1-i30e-net` |
| shipped, dashboard | `/private/tmp/g1_oracle_dash`, `…_run2` | **NO** | shipped |

## 0. FIRST CORRECTION — the dashboard baseline is unseeded

`recon/emulator/reports/display_sensor_oracle_dashboard.json` and both shipped
dashboard capture directories (`/private/tmp/g1_oracle_dash{,_run2}`, 2026-07-26
12:30/12:42) predate iteration 41's seed fix. Verified:

```
$ for d in /private/tmp/g1_*; do [ -f "$d/capture.resc" ] && grep -q SetSeed "$d/capture.resc" && echo $d; done
/private/tmp/g1_i41b_dashseed   /private/tmp/g1_i41b_navseed_s1   /private/tmp/g1_i41b_navseed_s2
/private/tmp/g1_i41c_dash       /private/tmp/g1_i41c_nav_s1       /private/tmp/g1_i41c_nav_s2
```

i.e. **every seeded dashboard capture on disk is OURS; there is no seeded
shipped dashboard capture at all.** `g1_ship_seed_q1/q2` (navigation) are the
only seeded shipped runs. So every dashboard-stimulus number in §41.2/§41.12
item 2 compares a *seeded* ours against an *unseeded* shipped — one draw of a
random variable, which is exactly the condition §41.8 corrected for navigation.
**Anything below that is measured only on the dashboard stimulus is provisional
until a seeded shipped dashboard capture exists** (that capture is the single
cheapest missing measurement in this whole document; see §6).

## 1. Re-derived divergence table (commands, not quotes)

Streams below are hashed on the *content* columns only (`dir=…data=…`,
i.e. tick and seq stripped), per-device, never per merged bus.

```
===== NAVIGATION, both sides seeded 305419896
  twim1 p1 0x6B  ship=291  ours=291   EQ
  twim1 p1 0x45  ship=33   ours=33    EQ
  twim1 p1 0x53  ship=25   ours=25    EQ
  twim1 p1 0x57  ship=22   ours=22    EQ
  twim2 p1       ship=1089 ours=1089  EQ
  twim1 p2 0x6B  ship=508  ours=508   EQ
  twim1 p2 0x45  ship=80   ours=80    EQ
  twim1 p2 0x53  ship=7    ours=0     NE   <- ITEM 1
  twim1 p2 0x57  ship=4    ours=0     NE   <- ITEM 1
  twim2 p2       ship=1200 ours=1200  NE   <- ITEM 3
===== DASHBOARD, ours seeded / shipped UNSEEDED  (provisional, see §0)
  twim1 p1 (all four devices)          EQ
  twim2 p1       ship=1075 ours=1075  EQ
  twim1 p2 0x6B  ship=514  ours=513   NE   <- ITEM 2
  twim1 p2 0x45  ship=59   ours=59    EQ
  twim1 p2 0x53  ship=7    ours=0     NE   <- ITEM 1
  twim1 p2 0x57  ship=4    ours=0     NE   <- ITEM 1
  twim2 p2       ship=1206 ours=1206  NE   <- ITEM 3
```

**CORRECTION to §41.12 item 2 / §41.2.** The dashboard `twim1 p2_render`
"572 vs 584" is not a diffuse 12-transaction deficit. It decomposes exactly:

```
584 - 572 = 12 = 7 (ST25DV 0x53)  +  4 (ST25DV 0x57)  +  1 (nPM1300)
```

**11 of the 12 missing transactions ARE item 1.** Item 2 is a *single*
nPM1300 transaction. (Ours measures 572 = 513 + 59 + 0 + 0 here.)

Also note the navigation OPT3001 `p2_render` is 80 == 80 **EQ** against the
seeded shipped run — §41.11's table already said this, and the earlier
`78` reading in the *unseeded* `g1_ship_nav_s1` is seed jitter, not a gap.

---

# ITEM 4 — `saadc` whole-run stream sha. **ROOT CAUSE FOUND. Not a firmware defect.**

## 4.1 The measurement

Renode's `LogPeripheralAccess` lines carry the faulting **PC**, so the streams
can be diffed access-for-access. Host wall-clock prefix and PC stripped
(our link addresses necessarily differ):

```
$ grep 'saadc:' g1_ship_seed_q1/run.out | sed 's/^[0-9:.]* //; s/\[cpuapp: 0x[0-9A-F]*\] //' > sa_ship.txt
$ grep 'saadc:' g1_i41c_nav_s1/run.out  | sed 's/^[0-9:.]* //; s/\[cpuapp: 0x[0-9A-F]*\] //' > sa_ours.txt
$ wc -l ; diff | grep -c '^[<>]'
1000  1000        90   (= 45 changed lines)
$ diff sa_ship.txt sa_ours.txt | grep '^[<>]' | grep -v ResultPtr | wc -l
0
```

**Every one of the 45 differing accesses is `WriteUInt32 to 0x62C (ResultPtr)`,
and nothing else in the 1,000-access stream differs at all** — not one
`ChPselP`, `ChConfig`, `Resolution`, `Oversample`, `Enable`, `TasksStart`,
`TasksSample`, `EventsEnd` poll, `TasksStop` or ordering.

(1,000 `saadc:` log lines vs the oracle's 998 "accesses": exactly two of them
are `Logging is already enabled` banner lines, and
`grep -cE 'ReadUInt|WriteUInt'` gives **998** on both sides. The 45-conversion
count is unchanged.)

## 4.2 What `ResultPtr` is

All 45 writes come from **one** PC — shipped `0x0005F8C6`, ours `0x0005F4DE` —
inside `saadc_start_read` = `FUN_0005f760` @ `0x5f760`
(`recon/symbolized/app/saadc_start_read.c`), whose signature is
`(undefined4 param_1, int *param_2)`: `param_2` is the **caller-supplied result
buffer**, written straight into `SAADC.RESULT.PTR`.

The three distinct values, 15 uses each, in first-appearance order:

| | site A | site B | site C |
|---|---|---|---|
| shipped | `0x200275CE` | `0x200275A6` | `0x200275BE` |
| ours | `0x20028766` | `0x2002873E` | `0x20028786` |
| delta | **+0x1198** | **+0x1198** | +0x11C8 |

They are **stack addresses**, not statics:
* `nm -n g1-i41c-app/zephyr/zephyr.elf` has **no** symbol between
  `20027c08 A g_20026a68` and `20028808 A g_aging_mode_aux_thread_stack` —
  `0x2002873E/66/86` all fall inside that thread-stack block;
* `recon/symbols/g1_app_globals.ld` (3,337 pins) has **no** pinned global
  anywhere in `0x20026000..0x20029000` on the shipped side either;
* the values are 2-byte-aligned, not 4 — an `int16_t` local, which is exactly
  the SAADC one-shot result type;
* `saadc_start_read` is never reached by a direct `BL` anywhere in the image
  (whole-image raw Thumb `BL`/`B.W` scan for target `0x0005f760`: **zero**
  sites; the only reference is the function-pointer literal `0x0005f761` at
  VA `0x0008b590`, an nrfx driver vtable), so the pointer is always a live
  caller's frame.

## 4.3 Root cause

**`saadc/whole_run/stream_sha256` hashes three stack addresses.** Two of the
three are a *constant* `+0x1198` from the shipped ones — i.e. the same thread
stack, relocated as a whole — and the third is a further `+0x30`, i.e. one of
the three calling frames is 0x30 B deeper in our build than in the shipped one.
Neither is a semantic difference; the register programme is identical.

## 4.4 The fix

There is nothing to fix in the firmware. **Fix the gate, in
`recon/emulator/scripts/build_display_sensor_oracle.py`:** when building
`peripherals/saadc/whole_run/stream_sha256`, canonicalise the operand of
`WriteUInt32 to 0x62C (ResultPtr)` — replace the value with a small index
assigned in order of first appearance (`0`, `1`, `2`) before hashing, and
publish the raw pointer triple in a separate, non-gating field. Do the same
for any other register whose payload is a RAM address (none is present in this
capture). The pointer triple is still worth recording, because the `+0x30`
says one reconstructed caller's frame is 0x30 B larger than the original's.

**Confirming evidence:** with that canonicalisation the shipped and our
`saadc` streams are already **identical today** — the 45 `ResultPtr` lines are
the *complete* difference and the diff of everything else is empty (measured
above). No rebuild is needed to confirm; re-running the oracle builder over the
two existing `run.out` files is sufficient.

**Confidence: HIGH (measured, complete).** What I could not determine without a
capture: which three call sites supply the buffers (the call is indirect through
the vtable at `0x8b590`), hence which reconstructed function carries the extra
0x30 B of frame. A `sysbus.saadc` PC-on-caller probe would name it; it is
cosmetic.

---

# ITEM 3 — `twim2 p2_render` content. **ROOT CAUSE FOUND: a ~7 ms sampling-phase offset, 3 samples of 1,200.**

## 3.1 The divergence is three transactions, not a stream

Per-index diff of the `dir`+`data` columns (ticks ignored):

```
NAV  twim2 p1: ship=1089 ours=1089  differing indices: 0
NAV  twim2 p2: ship=1200 ours=1200  differing indices: 3     <- idx 217, 221, 225
DASH twim2 p1: ship=1075 ours=1075  differing indices: 0
DASH twim2 p2: ship=1206 ours=1206  differing indices: 1     <- idx 225
```

Every differing transaction is a **6-byte read of `OUTX_L_A` (0x28)** — the
accelerometer output — during the "don" gesture. All 1,197 (resp. 1,205) other
transactions, including every register address, every write payload and every
gyro read, are byte-identical, in order.

## 3.2 The three samples are the SAME waveform read 7 ms later

Navigation, indices 213–229 (`W 28` = set register, `R` = the 6 bytes back):

```
 idx  shipped                        ours                       ours-ship
 213  R 7F340000421C  10.293181 s    R 7F340000421C 10.299930 s   +6.749 ms
 217  R 30370000B117  10.373330 s    R DD3700008C16 10.380400 s   +7.070 ms  DIFF
 221  R E23900002013  10.453460 s    R 8E3A0000FB11 10.460511 s   +7.051 ms  DIFF
 225  R 933C00008E0E  10.533600 s    R 403D00006A0D 10.540650 s   +7.050 ms  DIFF
 229  R 453F0000FD09  10.613740 s    R 453F0000FD09 10.620790 s   +7.050 ms
```

Read as little-endian int16 X and Z, interleaving the two builds by timestamp:

```
X: 347F -> 3730(ship) -> 37DD(ours) -> 39E2(ship) -> 3A8E(ours) -> 3C93(ship) -> 3D40(ours) -> 3F45(both)
Z: 1C42 -> 17B1(ship) -> 168C(ours) -> 1320(ship) -> 11FB(ours) -> 0E8E(ship) -> 0D6A(ours) -> 09FD(both)
```

Both sequences are strictly monotone and **our values interleave exactly between
consecutive shipped values** — our poll lands 7 ms further along the identical
ramp. The polling period is 80.11 ms on both sides. Outside this ~0.3 s window
the modelled gesture is flat at the sample resolution, so a 7 ms offset changes
nothing, which is why only 3 of 1,200 differ.

## 3.3 Where the 7 ms comes from: our boot is ~6.4 ms slower, from the first transaction

```
first twim1 transaction   ship 49.94 ms   ours 53.39 ms   +3.45 ms
first twim2 transaction   ship 73.30 ms   ours 79.69 ms   +6.39 ms
first spim_a transaction  ship 101.70 ms  ours 108.07 ms  +6.37 ms
```

and the twim2 offset then holds essentially flat for the whole run
(`+6.39 ms` at index 0 of `p1`, `+6.65 ms` at the end of `p1`, `+6.81 →
+10.35 ms` across `p2`). Renode charges virtual time per instruction
(`PerformanceInMips=100`), so a reconstruction whose `.text` is not
byte-identical *must* reach the first I2C write at a different virtual time.
The residual drift (+6.8 → +10.3 ms over 14 s, ≈ 0.025 %) is the same effect
integrated over the run.

## 3.4 The fix

**There is no firmware defect here and no source change can close it** short of
byte-identical codegen for the whole boot path. The fix is to the gate, in
`recon/emulator/scripts/build_display_sensor_oracle.py`:

* keep `twim2/p1_boot/stream_sha256` as a hard gate (it is EQ on both stimuli);
* replace `twim2/p2_render/stream_sha256` with two gates:
  (a) the transaction *count* (already exact: 1,200 == 1,200 nav,
  1,206 == 1,206 dash), and
  (b) the stream sha computed **with the `0x28` read payloads replaced by their
  transaction index** — i.e. gate the register programme, not the modelled
  analogue value. Publish the raw `0x28` payload list separately, as an
  informational field, with the count of samples that differ from the oracle.

**Confirming evidence that the fix worked:** under (b) the navigation and
dashboard `twim2 p2_render` streams are **already EQ today** — the differing
set is exactly {217, 221, 225} and {225}, all `0x28` reads (measured above).

**Confidence: HIGH.** Caveat: the DASHBOARD side of this is measured against the
*unseeded* shipped capture (§0); the navigation side, which carries the same
conclusion with 3 of 1,200, is seed-matched on both sides and is the load-bearing
measurement.

---

# ITEM 2 — dashboard `twim1 p2_render` 584 vs 572, nPM1300 514 vs 513

## 2.1 The 12 decompose 11 + 1 (see §1). The "1" is the last transaction of the run.

`difflib.SequenceMatcher` over the nPM1300 (`dev=0x6B`) content columns,
`g1_oracle_dash` vs `g1_i41c_dash`:

```
ship 514  ours 513
delete ship[513:514]  ours[513:513]
   - 19.800194 s  W 070401        <- the ONLY difference, and it is the LAST
                                     nPM1300 transaction of the shipped run
```

**Every one of the other 513 nPM1300 transactions is identical and in order.**
The missing one is a member of a `W 070401` poll (bank 0x07 reg 0x04 ← 0x01)
that runs in bursts of six at 200 ms spacing; shipped emits 68 of them,
we emit 67.

## 2.2 It is a capture-window edge effect, and its onset is item 1

Aligning the 68 vs 67 `070401` timestamps index by index:

```
 idx  ship      ours      ours-ship
   0  6.0760    6.0774    +1.5 ms
  25  11.3264   11.3277   +1.3 ms
  26  11.7365   11.7289   -7.6 ms   <- sign flips here
  32  12.9397   12.9772   +37.5 ms
  38  14.1414   14.2298   +88.5 ms
  44  15.3430   15.4794   +136.4 ms
  50  16.5464   16.7277   +181.3 ms
  56  17.7981   18.0273   +229.2 ms
  62  18.9997   19.2770   +277.3 ms
  66  19.6002   19.8789   +278.7 ms
  67  19.8002      —               <- past our 20 s wall
```

Two facts:

1. **Up to index 25 the two runs agree to 1.5 ms.** The divergence starts at
   index 26, `t = 11.73 s` — and the shipped ST25DV render-phase burst is at
   **11.70606 … 11.71234 s**, i.e. immediately before it. Our run reaches that
   nPM1300 burst **7.6 ms early** — very close to the ~6.3 ms of I²C bus time
   the shipped spends on the 11 ST25DV transactions we never issue.
2. **From there the burst period differs**: shipped settles on
   1.2016–1.2034 s between burst starts, ours on 1.2483–1.2526 s — exactly
   one ~50 ms scheduling tick more per burst. Accumulated over 6 bursts that
   is the +277 ms at index 62, which pushes our 68th `W 070401` to
   20.079 s — outside the capture.

## 2.3 Root cause and fix

**Item 2 is not an independent defect. It is (a) downstream of item 1 and
(b) measured against an unseeded baseline (§0).** The nPM1300 register
programme is byte-identical for 513 of 514 transactions; nothing about the
PMIC driver is wrong. Both shipped dashboard runs give 514/68, so the shipped
side is at least stable, but neither of them was seeded, and our side was.

**The fix is: do not fix anything here yet.** In order:

1. Capture a **seeded** shipped dashboard run
   (`G1_ATT_WRITE="" G1_SEED=305419896 recon/emulator/scripts/capture_display_sensor_oracle.sh …`)
   and regenerate `display_sensor_oracle_dashboard.json` from it. Until that
   exists, no dashboard-stimulus count is admissible evidence about a code
   change — this is exactly the correction §41.8 made for navigation.
2. Land the item-1 fix and re-measure. The prediction is that restoring the
   render-phase ST25DV work restores the ≈6 ms of bus occupancy at t ≈ 11.71 s
   and with it the nPM1300 burst phase, taking 513 → 514 **as a collateral
   gain**, exactly as restoring the 15 Hz display workload in §41.5 took
   `twim1 p1_boot` OPT3001 35 → 33 and the whole per-device set to EQ.
3. Only if 513 ≠ 514 survives both of those is there a defect to hunt, and the
   place to look is the ~50 ms-per-cycle period difference of the nPM1300
   polling thread, not the transaction contents.

**Confirming evidence:** `twim1 p2_render` total 584 == 584 and nPM1300
514 == 514 on a *seeded* dashboard pair.

**Confidence: HIGH that the 12 decompose 11+1 and that the 1 is a window edge
effect; MEDIUM that item 1 causes it** (the coincidence of the sign flip with
the shipped ST25DV burst is strong but is one observation). What I could not
determine without a capture: whether the 1.2016 s → 1.2497 s burst-period
change is itself caused by the ST25DV work or is independent.

---

# ITEM 1 — the ST25DV render-phase traffic. **Localised to ONE call site and TWO proven reconstruction defects on its only reachability path.**

## 1.1 What the missing traffic actually is

Shipped navigation, seeded, `twim1.p2.trace` seq 258–268 (t = 11.70606 …
11.71234 s) — this is the *whole* of the missing render-phase work:

```
0x57 W 0014 / R 7F00        0x53 W 0000 / R E1404001      <- read CC file
0x57 W 0016 / R 03          0x53 W 0004 / R 031C9106      <- read the NDEF TLV
                            0x53 W 0004031C               <- write T=0x03 L=0x1C
                            0x53 W 0006 91 06 06 "WLCCAP" 20 01 09 1E 03 0A
                                        51 07 03 "WLCSTAI" 05 64 01
                            0x53 W 0022FE                 <- terminator
```

It is **one call to `st25dv_build_and_write_ndef_records` = `FUN_000250f8`**
(4 + 7 transactions), byte-identical to the second of the two calls the shipped
firmware already makes during boot (`p1` seq 297–310, t = 4.21346 … 4.21972 s),
which our build reproduces exactly.

## 1.2 There are exactly two call sites in the whole image, and the missing one is `case 3`

Raw whole-image Thumb `BL`/`B.W` scan of `app_update.bin` (every halfword
boundary, not just catalogued extents) for target `0x000250f8`:

```
bl site 0000fd74 -> 000250f8      box_placement_animation_step, case 3
bl site 0000fe4c -> 000250f8      box_placement_animation_step, case 12
(no other site, and no function-pointer literal 0x000250f9 anywhere)
```

`box_placement_animation_step` = `FUN_0000fcf0` @ `0xfcf0`, 356 B, `tbb` at
`0xfd08` over states 1..14; its only caller is `handle_box_placement_event`
`0x255d8`.

**The render write is the `case 3` site, not `case 12`** — proven from the
payload, not assumed. `wlccap_record_next_fragment` (`FUN_00024a40`) builds the
6-byte WLCCAP payload from `record[0x10..0x19]`, which
`event_record_init` (`0x25090`) copies verbatim from `primary_spec` =
`{0x20, s[7], s[8], s[9], s[0xa], s[0x10], s[0xb], s[0xd], s[0xe], s[0xf]}`:

| wire byte | fragment case | expression | observed | ⇒ |
|---|---|---|---|---|
| 0 = `0x20` | 0 | `rec[0x10]` | `0x20` | — |
| 1 = `0x01` | 1 | `(rec[0x14]&1) \| (rec[0x11]<<6) \| …` = `(s[0xa]&1) \| (s[7]<<6) \| …` | `0x01` | **`s[7] == 0`** |
| 2 = `0x09` | 2 | `(rec[0x16]&0x1f) \| (rec[0x15]<<5)` = `(s[0xb]&0x1f) \| (s[0x10]<<5)` | `0x09` | **`s[0xb] == 9`** |
| 3,4,5 | 3,4,5 | `s[0xd], s[0xe], s[0xf]` | `1E 03 0A` | — |

`case 12` (`0xfe3a`) executes `strb r3,[r4,#7]` with `r3 = 2` and
`strb r3,[r4,#0xb]` with `r3 = 0x13` **before** its `bl 0x250f8`, so a case-12
write would put `0x81` and `0x13` on the wire. Neither value appears anywhere
in either capture. **⇒ both shipped writes are `case 3` writes.**

The same decoding pins the rest of the state at the render write:
`s[0xb] = s[0xc] = 9` (the write assigns `s[0xb] = s[0xc]` at `0xfd68`
*before* the call, and byte 2 still reads 9), and the WLCSTAI payload
`05 64 01` decodes through `wlcstai_record_next_fragment` as
bitmap `0x05` → `s[0x13]` = **battery 100** and `s[0x15]` = 1. So at the render
write `|s[0x13] − *g_2000f6e4|` cannot be > 20 unless `*g_2000f6e4` is still 0 —
which is exactly what happens when the *first* write was taken through the
`*g_20003023 != 0` / `s[0xb] != s[0xc]` early-out at `0xfd4e`/`0xfd54`, both of
which jump to `0xfd68` and **skip** the `strh r3,[r0]` at `0xfd66`.

So the shipped behaviour is: two `case 3` writes, the second one reached only
because the state machine **returns to `case 3` a second time** while
`*g_2000f6e4` is still 0. Our build makes the first write and never comes back.

## 1.3 The state machine, and the one number that controls how long it stays in state 10

`box_placement_animation_step`'s `tbb` table at `0xfd0c` is
`07 10 17 45 59 59 59 0f 59 73 86 97 0f 41`, i.e.

```
state  1 -> 0xfd1a   2 -> 0xfd2c   3 -> 0xfd3a   4 -> 0xfd96
       5,6,7,9 -> 0xfdbe          8,13 -> 0xfd2a (return)
      10 -> 0xfdf2  11 -> 0xfe18  12 -> 0xfe3a  14 -> 0xfd8e
```

The steady-state cycle is `3 → 4 → 9 → 10 → 11 → 3`. `case 3` sets
`*g_20007a04 = 150.0f`; `case 4` waits it out; **`case 9` recomputes it**:

```
0000fdc2  ldrb  r0, [r4, #0xb]      ; s[0xb]
0000fdc4  adds  r0, #3
0000fdc6  bl    #0xd824             ; __floatsidf(int)  -> double in r0:r1
0000fdca  vldr  d0, [pc, #0x9c]     ; @0xfe68 = 2.0                    <-- BASE
0000fdce  vmov  d1, r0, r1          ; exponent = (double)(s[0xb]+3)
0000fdd2  bl    #0x75acc            ; pow(d0, d1)       -> d0
0000fdd6  ldr   r3, [pc, #0xac]     ; @0xfe84 = 0x40490000  (hi of 50.0)
0000fdd8  vmov  r0, r1, d0
0000fddc  movs  r2, #0              ; (lo of 50.0)
0000fdde  bl    #0xd588             ; __aeabi_dsub(pow, 50.0) -> r0:r1
0000fde2  bl    #0xdee8             ; __truncdfsf2(r0:r1) -> float bits in r0
0000fde8  str   r0, [r3]            ; *g_20007a04 = (float)(2^(s[0xb]+3) − 50)
```

With `s[0xb] = 9` (set by `init_config_fields_default9` @`0x7c3c2`, which
writes `s[0xb] = s[0xc] = 9`, and re-confirmed by the wire byte above) the
shipped deadline is **2^12 − 50 = 4046 ms**. `case 10` (`0xfdf2`) then holds
the machine in **state 10 for ~4 s at a time**, and state 10 is the *only*
state in which `transport_state_update` will touch the box record:

```
transport_state_update = FUN_0002538c   (UNCATALOGUED — classified.json jumps
0x25364(+36 ⇒ ends 0x25388) straight to 0x2542c; process_box_event reaches it by
`b.w #0x2538c` at 0x2551e)

  phase 2:  if (now − *g_20007a00 >= 3001) {
                if (state[5] == 10) { if (!state[0]) state[12] = 6; state[1] = 1; }
                state[3] = 1; *g_20007a00 = now; }
  phase 4:  if (state[5] == 10) { if (!state[0]) state[12] = 6; state[1] = 1; }
            if (!state[2]) state[2] = 1; *g_20007a00 = now;
```

`state[1]` is what makes `case 10 → 11`, and `case 11` then routes to
`case 2` (`k_sleep(1639 ms)`) → `case 3`. **`*g_20007a04` therefore decides
whether the box state machine ever gets nudged out of its no-write cycle.**

## 1.4 DEFECT A — `case 9`'s deadline is computed through FIVE ABI/constant errors

`recon/symbolized/app/box_placement_animation_step.c` (the tree the build
compiles, per `recon/generated/app_retained_sources.cmake:508`) declares

```c
extern uint32_t get_elapsed_ms_since_mark(void), __floatsidf(uint32_t);
extern double   pow(uint32_t, uint32_t), __truncdfsf2(void);
extern void     dcmp_negate_rhs(double, double);
...
case 5: case 6: case 7: case 9:
  if (!s[7]) {
      uint32_t x = __floatsidf((uint8_t)(s[0xb] + 3));
      double   y = pow(0, x);
      dcmp_negate_rhs(y, 3.140625);
      *deadline = (float)__truncdfsf2();
  }
```

and GCC emits, in `/private/tmp/g1-i41c-app/zephyr/zephyr.elf` at `0xd454`:

```
    d458:  ldrb  r0, [r4, #11]
    d45a:  adds  r0, #3
    d45c:  uxtb  r0, r0                 ; (1) EXTRA truncation
    d45e:  bl    c5fc <__aeabi_i2d>     ;     correct call…
    d462:  mov   r1, r0                 ; (2) keeps only the LOW word of the double
    d464:  mov   r0, r5                 ; (3) r5 = s[7] = 0  as pow's "base"
    d466:  bl    d5c0 <pow>             ;     but our pow reads d0/d1 (hard-float)
    d46a:  vldr  d1, [pc, #148]         ; (4) 0x4009200000000000 = 3.140625
    d46e:  bl    78776 <dcmp_negate_rhs>;     but that helper reads r0..r3
    d472:  bl    cc94 <__aeabi_d2f>     ; (5) __truncdfsf2 called with NO argument
    d476:  vmov  r0, r1, d0
    d47a:  bl    cc94 <__aeabi_d2f>     ;     …and again, for the (float) cast
    d480:  str   r0, [r3]               ;     *deadline = garbage
```

Each is verified against the callee's own prologue in our own image:

| callee | our address | reads | our call passes |
|---|---|---|---|
| `pow` | `0xd5c0` | `vstr d0,[sp]`, `vmov.f32 s18,s2` → **d0, d1** | `r0`, `r1` |
| `__truncdfsf2`/`__aeabi_d2f` | `0xcc94` | `mov.w r2, r1, lsl #1` → **r0:r1** | nothing |
| `dcmp_negate_rhs` (`__aeabi_dsub`) | `0x78776` | `eor r3,r3,#0x80000000; b __aeabi_dadd` → **r0..r3** | `d0`, `d1` |

and against the shipped constants: **base `2.0`** (`@0xfe68`, read back as
`0000000000000040` → 2.0) not `0`, and **subtrahend `50.0`**
(`0x4049000000000000`) not `3.140625` (`0x4009200000000000`).

**Consequence.** `*g_20007a04` — the sole control on how long the machine sits
in state 10, i.e. the sole window in which `transport_state_update` can set
`state[1]`/`state[12]` — is a deterministic garbage bit pattern instead of
4046 ms. That is exactly the shape of a defect that removes a whole phase of
work rather than one transaction, and it sits on the *only* reachability path
to the missing call.

### The fix (§5.4 level)

In `recon/symbolized/app/box_placement_animation_step.c` — and the four
parallel copies `recon/app/src/FUN_0000fcf0.c`,
`recon/verified/src/FUN_0000fcf0.c`, `recon/named/box_placement_animation_step.c`,
`recon/readable_sources/app/g1/box_placement_animation_step.c` — replace the
declarations and the `case 5/6/7/9` body with the project's already-proven
raw-bits convention (the one landed in `battery_model_state_update.c` in §39.6
and in `fuel_gauge_update.c` in §41.10):

```c
union g1_d { double d; uint64_t u; };
union g1_f { float  f; uint32_t u; };

extern uint64_t __floatsidf(int);                        /* soft: r0 -> r0:r1 */
extern double   pow(double, double);                     /* hard: d0,d1 -> d0 */
extern uint64_t dcmp_negate_rhs(uint64_t, uint64_t);     /* soft: r0:r1, r2:r3 */
extern uint32_t __truncdfsf2(uint64_t);                  /* soft: r0:r1 -> r0  */
...
case 5: case 6: case 7: case 9:
    if (!s[7]) {
        union g1_d n, p, r; union g1_f out;
        n.u = __floatsidf((int)s[0xb] + 3);       /* NO (uint8_t) cast     */
        p.d = pow(2.0, n.d);                      /* base 2.0, not 0       */
        r.u = dcmp_negate_rhs(p.u, 0x4049000000000000ULL);  /* − 50.0      */
        out.u = __truncdfsf2(r.u);
        *deadline = out.f;
    }
    set_time_mark(); next = 10; break;
```

Expected codegen after the fix: `ldrb/adds/bl __floatsidf/vldr d0,=2.0/
vmov d1,r0,r1/bl pow/vmov r0,r1,d0/movs r2,#0/ldr r3,=0x40490000/bl dcmp_negate_rhs/
bl __truncdfsf2/str` — the shipped sequence instruction for instruction.

## 1.5 DEFECT B — `transport_state_update` drops the timestamp refresh on one arm

Shipped `FUN_0002538c`, `phase == 1` arm:

```
000253b0  ldr   r2, [r5, #8]        ; context[8] = NFC-field ADC × 10
000253b2  cmp.w r2, #0x1f4          ; 500
000253b6  ldr   r2, [pc, #0x6c]     ; = 0x20018c65
000253b8  bhs   #0x253c2
000253ba  ldrb  r1, [r2] ; cbnz r1, #0x253c0 ; strb r3, [r2]   ; *active = 1
000253c0  pop
000253c2  strb  r1, [r2]            ; *active = 0
                                    ;   ** FALLS THROUGH **
000253c4  bl    #0x7c398 ; ldr r3,=0x20007a00 ; str r0,[r3]    ; *timestamp = now
```

Ours (`/private/tmp/g1-i41c-app/zephyr/zephyr.elf` `0x22b6c`):

```
   22b90:  bcc.n  22b96
   22b92:  strb   r1, [r2, #0]      ; *active = 0
   22b94:  pop    {r3, r4, r5, pc}  ; <-- RETURNS; no *timestamp update
```

i.e. `recon/symbolized/app/transport_state_update.c`'s

```c
if (*(uint32_t *)(context + 8) >= 500U) {
    *active = 0U;
} else if (*active == 0U) { *active = 1U; }
```

is missing the shipped fall-through. **Fix:** add `*timestamp =
thunk_FUN_00074f68();` on that arm only (the `else if` arm must still return
without it, matching `0x253c0`). One line, five parallel trees
(`recon/{symbolized/app,named,readable_sources/app/g1}/transport_state_update.c`,
`recon/{app,verified}/src/FUN_0002538c.c`).

Effect: `*g_20007a00` is the base of the 3001 ms `phase == 2` timer that (with
`state[5] == 10`) sets `state[1]`/`state[12]`. Leaving it stale mistimes that
timer against the state-10 window. Note this also affects the *shipped-correct*
behaviour only when the box is present and the battery is ≤ 99, so it is
secondary to DEFECT A but is on the same path and is unambiguously a defect.

## 1.6 What I ruled out

* **Not a missing callee.** Every `BL` inside the true extents of
  `handle_box_placement_event` (0x25528, 200 B), `box_placement_animation_step`
  (0xfcf0, 356 B), `process_box_event` (0x254d8, 226 B) and
  `transport_state_update` (0x2538c, 152 B) was decoded and matched against the
  reconstructions' callee lists: **no G-3-style zero-call callee.**
* **Not a missing switch arm.** The 14-entry `tbb` at `0xfd0c` was decoded and
  every target is present in our `switch` (states 8 and 13 → `0xfd2a` = the
  bare `pop`, i.e. our `default:`).
* **Not the battery gate closing at boot.** The WLCSTAI payload byte
  `0x64` = 100 in *our own* boot record proves `get_device_info()[0xfc0] == 100`
  at t = 4.2 s in our build, so `0x1d < battery` was true and
  `box_placement_animation_step` was reached. (It does **not** prove the
  percentage stays 100 for the rest of the run — see §1.7.)
* **Not the `rodata_50100` store.** `handle_box_placement_event` `0x25596`
  stores the *immediate* `0x00050100` into `b[0x10..0x13]`; our source writes
  `(unsigned long)&rodata_50100`, and `rodata_50100` is PROVIDEd at `0x00050100`
  — the emitted literal at `0x22df0` is `00 01 05 00`, i.e. **the same value**.
  Cosmetically misleading, not a defect.
* **Not `*g_20003023` being written elsewhere.** A whole-image scan of literal
  pools for every word in `[0x20002fe0, 0x20003024]` finds `0x20003023` at
  exactly one site, `0xfe74`, the literal pool of `box_placement_animation_step`.
* **Not an ST25DV driver problem.** Every ST25DV transaction our build does
  emit — 25 on `0x53` and 22 on `0x57` in `p1_boot`, both stimuli — is
  byte-identical to the shipped stream (sha `f678f6c33af5…` / `b137b7464187…`
  on both sides).

## 1.7 Confidence, and what needs a capture

**Confidence that the missing traffic is exactly one `case 3`
`st25dv_build_and_write_ndef_records` call: VERY HIGH** (call-site scan +
payload decode, both from the shipped bytes).
**Confidence that DEFECT A and DEFECT B are real: CERTAIN** (both read off the
two disassemblies side by side).
**Confidence that fixing DEFECT A alone restores the traffic: MEDIUM.** I can
prove `*g_20007a04` is garbage; I cannot evaluate the garbage statically, so I
cannot prove the machine is stuck in state 10 rather than racing through it.

**The one capture that settles it** (for whoever owns Renode): on the *fixed*
and on the *current* build, hook our `0xd480` (`str r0,[r3]` in
`box_placement_animation_step` case 9) and print `r0` — the deadline float
bits — plus a watch on the box state buffer `0x20003520` bytes `[1]`, `[5]`,
`[0xb]`, `[0xc]` and on `g_20003023` = `0x200041c3`. The shipped counterpart is
`0xfde8` with the buffer at `0x20002380` and the flag at `0x20003023`. Two
15-second runs, one probe file each. Predicted shipped value at `0xfde8`:
`0x457CE000` (= 4046.0f). If ours already reads `0x457CE000` after the fix and
the write still does not appear, the remaining suspect is the third variable I
could not pin statically: `state[0]` (`b[0]`), which
`handle_box_placement_event` sets to 1 at `0x25580` and which gates
`state[12] = 6`.

---

# ITEM 5 — the `-ffp-contract` question. **SETTLED, and the premise is inverted.**

## 5.1 There is no disagreement between AGENTS.md §1b and §40.13 item 7

Whole-image scan of `app_update.bin`: every catalogued function disassembled
over its declared extent, counting fused (`VFMA/VFMS/VFNMA/VFNMS`) vs unfused
(`VMLA/VMLS/VNMLA/VNMLS`) multiply-accumulates.

```
19 functions FUSED-only,  5 functions UNFUSED-only,  0 functions MIXED
```

The five unfused bodies are **exactly** AGENTS.md §1b's list:

| function | entry | unfused ops |
|---|---|---|
| `fuel_gauge_update` | `0x00010b18` | `VNMLS` ×1 |
| `fast_inverse_sqrt` | `0x000265e8` | `VMLS` ×2 |
| `imu_mahony_ahrs_update` | `0x00026624` | `VMLA` ×16, `VNMLS` ×6, `VNMLA` ×1, `VMLS` ×3 |
| `orientation_get_heading_deg` | `0x00026828` | `VMLA` ×1 |
| `quaternion_to_euler` | `0x0007cab4` | `VMLS` ×2, `VMLA` ×2, `VNMLS` ×1 |

and `battery_soc_curve_model_init` = `FUN_0000e53c` @ `0xe53c` carries
**`VFMA` ×10, zero unfused** — so §40.13 item 7 is right too. The two
statements are about different functions and **both are correct**; §41.12
item 4's "standing disagreement" is a misreading. Recorded so it stops
recurring.

(Sanity check on extents: re-scanning every function from its entry to the
*next* function's entry — i.e. ignoring the declared size, so Ghidra
under-reporting cannot hide a hit — produces exactly one extra hit,
`vmla.i32 q0, q5, d4[0]` at `0x50fe4`, which uses NEON `q`/`d` registers that
do not exist on a Cortex-M33/FPv5-SP-D16 and lies in `FUN_00050e64`'s trailing
rodata. It is a false decode in data, not code.)

## 5.2 The flag is NOT needed: the build is already at `-ffp-contract=off`

`§41.12 item 4` states those TUs "compile at GCC's default
`-ffp-contract=fast` and emit `VFMA` where the shipped image has `VMLA`".
**That is false for this build.** From
`/private/tmp/g1-i41c-app/compile_commands.json`, the flags for
`recon/symbolized/app/*.c` are

```
-Os -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard … -std=c99
```

and `-std=c99` (strict ISO, not `gnu99`) makes GCC 12 default to
`-ffp-contract=off`. Measured on the actual toolchain, not quoted:

```
$ cat fmatest.c ;# float f(float a,float b,float c){return a*b+c;}
-std=c99                     ->  vmla.f32  s2, s0, s1
-std=gnu99                   ->  vfma.f32  s2, s0, s1
-std=c99  -ffp-contract=fast ->  vfma.f32  s2, s0, s1
-std=gnu99 -ffp-contract=off ->  vmla.f32  s2, s0, s1
(arm-zephyr-eabi-gcc (Zephyr SDK 0.16.5-1) 12.2.0)
```

And the linked image agrees. Op histograms in
`/private/tmp/g1-i41c-app/zephyr/zephyr.elf` vs the shipped image:

| body | shipped | ours | verdict |
|---|---|---|---|
| `imu_mahony_ahrs_update` | vmla 16, vnmls 6, vnmla 1, vmls 3 | **vmla 16, vnmls 6, vnmla 1, vmls 3** | **identical histogram** |
| `orientation_get_heading_deg` | vmla 1 | vmla 1 | identical |
| `quaternion_to_euler` | vmls 2, vmla 2, vnmls 1 | vmls 2, vmla 2, vnmls 1 | identical |
| `fuel_gauge_update` | vnmls 1 | vnmls 1 | identical |
| `fast_inverse_sqrt` | vmls 2 | (none) | unfused, but different codegen |

**Nothing needs pinning for those five, and nothing about the IMU fusion
arithmetic that drives the dashboard would change.** §41.12 item 4's stated
cost — "it would change the arithmetic of `imu_mahony_ahrs_update` and
`imu_fusion_thread` … so landing it needs its own build + full four-framebuffer
gate" — does not apply, because the flag is not needed at all.

## 5.3 The real, opposite gap: six bodies the shipped image FUSES and we do not

Because the whole tree is at contract=off, the fusion in the shipped image has
to be written explicitly. Ten reconstructions already do this and match:

```
curve_table_interp_201pt  9 fma ==  9      __ieee754_asinf   26 == 26
lc3_energy_compute        1 ==  1          __ieee754_logf    13 == 13
lc3_ltpf_analyse         44 == 44          __ieee754_log10f   2 ==  2
lc3_mdct_forward         14 == 14          lc3_spec_analyze   1 ==  1
lc3_tns_analyze          82 == 82
```

`grep -c '__builtin_fma' recon/symbolized/app/curve_table_interp_201pt.c` → 9,
`__ieee754_logf.c` → 14, `lc3_sns_analyze.c` → 9. **The mechanism already in
use is `__builtin_fmaf()` at the site, not a build flag.**

Six bodies still spell `a*b+c` and therefore emit `VMLA` where the shipped
image has `VFMA`:

| body | entry | shipped fused | ours |
|---|---|---|---|
| `battery_model_state_update` | `0x0000c358` | vfma 13, vfnms 1 | vmla 29, vmls 3 |
| `battery_soc_curve_model_init` | `0x0000e53c` | vfma 10 | vmla 8 |
| `spline_interp_pair_2out` | `0x0000ea70` | vfms 2, vfma 4 | vmls 2, vmla 4 |
| `spline_interp_3pt` | `0x0000eb7c` | vfms 1, vfma 2 | vmls 1, vmla 2 |
| `__ieee754_expf` | `0x00076290` | vfma 5, vfms 2 | vmla 3, vmls 2, vnmls 2 |
| `atanf` | `0x000768e0` | vfma 12 | vmla 7, vnmls 4 |

(Three more shipped-fused bodies — `lc3_mdct_fft` `0x6b3c8`,
`lc3_sns_unquantize` `0x6bd74`, `lc3_sns_spectral_shaping` `0x6bfc8` — have no
symbol of that name in our ELF at all and are a separate question, not an
`fp-contract` one. `lc3_sns_analyze` has 169 fused ops in ours vs 37 counted in
the shipped `FUN_0006c778`, but that function is the flagship Ghidra
data-inflation case — 10,232 declared vs ~1,002 B of true code — so the
shipped 37 is not a like-for-like count and this row must be re-derived over
the true extent before anyone reads anything into it.)

## 5.4 The fix, and its cost

**Do not add `-ffp-contract` anywhere.** Neither globally (it would break the
five already-correct unfused bodies) nor per-file (`-ffp-contract=fast` on a
whole TU would fuse *every* mul-add in it, including any that the shipped image
leaves unfused — none of the six is mixed today, but that is a property to
preserve deliberately, not by accident).

**Instead, convert the specific expressions in the six files above to
`__builtin_fmaf(a, b, c)` / `-__builtin_fmaf(a, b, -c)`, one site at a time,
matching the shipped instruction at each address** — exactly the pattern
already proven in `curve_table_interp_201pt.c`, `__ieee754_logf.c` and
`lc3_sns_analyze.c`. Cost: zero build-flag surface, zero effect on any other
TU, and the diff is auditable per instruction.

**Gating.** Four of the six are inert for the current oracles
(`spline_interp_pair_2out`, `spline_interp_3pt`, `__ieee754_expf`, `atanf` —
though `atanf`/`expf` are reachable from the fusion path, so gate anyway).
**Two are not:** `battery_model_state_update` (`0xc358` — still an open defect
per AGENTS.md §1b) and `battery_soc_curve_model_init` (`0xe53c`) are the
battery EKF, and fused vs unfused rounds differently, so their state-of-charge
output can move by an ulp. Because the ST25DV/NDEF work of ITEM 1 is gated on
`device_info[0xfc0] > 0x1d` **and** the WLC record carries the percentage byte
verbatim, those two must be landed on their own build and gated on:
the four framebuffers, `twim1 p1_boot` ST25DV `0x53`/`0x57`
(25 / 22, sha `f678f6c33af5…` / `b137b7464187…`), and the WLCSTAI payload byte
staying `0x64`.

**Confirming evidence for the whole item:** re-running the §5.1 scan over the
rebuilt ELF should give, for all 24 bodies, an op histogram identical to the
shipped one — 19 fused-only and 5 unfused-only, same counts, no mixed.

**Confidence: HIGH.** Everything here is static and reproducible; the only
soft spot is the `lc3_*` rows, flagged above.

---

# 6. Summary and the one measurement that is missing

| item | verdict | root cause | fix location |
|---|---|---|---|
| 1 ST25DV render phase absent | **localised, 2 proven defects, causality MEDIUM** | `box_placement_animation_step` case 9 computes `*g_20007a04` through 5 float-ABI/constant errors; `transport_state_update` drops a timestamp refresh | `recon/symbolized/app/box_placement_animation_step.c` case `5/6/7/9`; `…/transport_state_update.c` phase-1 arm (+4 parallel trees each) |
| 2 dashboard `twim1 p2` 584 vs 572 | **11 of 12 ARE item 1; the 1 is a capture-window edge effect** | nPM1300 burst phase diverges from t = 11.73 s, immediately after the shipped ST25DV burst | nothing yet — re-measure after item 1, on a *seeded* shipped dashboard capture |
| 3 `twim2 p2` content | **not a firmware defect** | 3 of 1,200 (nav) / 1 of 1,206 (dash) `0x28` reads land 7 ms later on the same gesture ramp; our boot is 6.4 ms slower from the first I²C write | gate change in `build_display_sensor_oracle.py` |
| 4 `saadc` stream sha | **not a firmware defect** | the only differing accesses are 45 `RESULT.PTR` writes carrying a *stack address* | gate change in `build_display_sensor_oracle.py` |
| 5 `-ffp-contract` | **settled; premise inverted** | build is already at contract=off via `-std=c99`; the real gap is 6 bodies needing `__builtin_fmaf` | 6 named `.c` files, per-site |

**The single most valuable missing capture** is a **seeded shipped dashboard
run**:

```sh
G1_ATT_WRITE="" G1_SEED=305419896 \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ship_seed_dash
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ship_seed_dash /private/tmp/g1_ship_seed_dash_rep
```

Until it exists, `display_sensor_oracle_dashboard.json` is one draw of a random
variable and no dashboard count is admissible evidence about a code change —
the same correction §41.8 already made for navigation, not yet made for the
dashboard.

**Second most valuable:** the deadline/state probe described in §1.7, which is
what converts item 1 from "two proven defects on the only path" into "root
cause proven".
