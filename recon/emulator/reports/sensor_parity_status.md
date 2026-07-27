# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**Twenty-second measurement** (iteration 35; previous measurements were
iterations 14–34).  From iteration 34 there are **two** oracles and **two**
criteria sets, both in force:

| oracle | screen | stimulus | criteria |
|---|---|---|---|
| `display_sensor_oracle.json` | `E_ID_SCREEN_NAVIGATION` (id 10) | phone connects **and writes GATT `0a0600000000`**, then `don` gesture | G-1…G-6, S-* |
| **`display_sensor_oracle_dashboard.json`** *(new)* | **`E_ID_SCREEN_DASHBOARD` (id 6)** | phone connects, **NO GATT command**, then `don` gesture | **D-1…D-7, S-D-*** |

> ## ⇩ CURRENT STATE: **P4 iteration 41** (detail in `our_boot_bringup.md` §41) ⇩
> **Iteration 41 (`g1-i41b-app`, net unchanged `g1-i30e-net`) is the live
> measurement.  ALL FOUR framebuffers are still BYTE-IDENTICAL to the shipped
> firmware (`cmp` vs the golden `.raw` files, 153,600 B each, exit 0; dashboard
> `p1_boot` all-zero) — re-verified at HEAD `5337623a`, which the latent-defect
> harvest had left ungated.**
>
> * **`G-3` CLOSED as a defect.**  `ui_navigation_task`'s missing `event == 0`
>   arm is restored from the shipped Thumb: navigation `spim_a` `p1_boot`
>   **126 -> 808** and `p2_render` **109 -> 2,859** (shipped 764 / 2,881;
>   whole run **3,667 vs 3,645**).  The restored animation is the shipped one
>   *cell for cell*: `x=32`, 9 pixel bytes, rows 265…285, 21 blits per refresh,
>   at **66.62 ms = 15.0105 Hz**, identical to the shipped cadence to the
>   nanosecond.  The whole residue is **one extra frame** because our
>   `NAVIGATION_ACTIVE` transition is 110 ms early (3.981 s vs 4.091 s).
> * **Collateral: the whole navigation `twim1 p1_boot` per-device set now
>   matches** — 371 == 371, OPT3001 **33 == 33 sha EQ** (was 35), nPM1300
>   291 == 291 sha EQ, both ST25DV ports sha EQ, `ESB_MASTER_FRAMES`/`ESB_ACKS`
>   0x175 == 0x175.  The `33 <-> 35` puzzle of §40.13 item 5 and R7 §4.5 was
>   the MISSING DISPLAY WORKLOAD, not jitter and not the NDEF change.
> * **The capture's non-determinism is a HARNESS defect, now root-caused.**
>   `platforms/nrf5340.repl:459` gives the net core a stock
>   `Miscellaneous.NRF52840_RNG`, which draws from Renode's emulation-wide
>   `RandomGenerator` — **re-seeded randomly at every Renode start**
>   (measured: 2124439726, then 720424243).  The **shipped** images are
>   therefore bistable too: two shipped runs gave `spim_a` 786/2,859 and
>   764/2,881.  Whole-run totals are invariant; only the `RunFor "6"` split
>   moves.  Fix: `emulation SetSeed <n>` before the platform is created.
>   **Until a capture states its seed, gate on WHOLE-RUN totals and PER-DEVICE
>   streams, never on a per-phase count or the merged `twim1` bus sha.**
>
> Still open: the `saadc` stream sha (count exact at 998), dashboard
> `twim1 p2_render` 572 vs 584 with nPM1300 513 vs 514 and the ST25DV render
> traffic absent, `twim2 p2_render` content, the `-ffp-contract=off` pin and the
> `__extendsfdf2` log-gated ABI defect.
> Everything between here and that section is kept for provenance and is
> superseded.

## Iteration 35 record (kept) — **THE DASHBOARD IS PAINTED**

Build **`g1-i35b-app`**, net **unchanged** `g1-i30e-net`; captures
`/private/tmp/g1_ours_dash_i35b` and `/private/tmp/g1_ours_nav_i35b`.
Full detail and every measurement in `our_boot_bringup.md` §35.

Iteration 34's `* buffer overflow detected *` reboot is **eliminated**.  It was
not "the three font families are unrecovered" but three separate, provable
holes, only one of which rodata batch 4 filled:

* the glyph **counts** `rodata_8ac2c/_8ac30/_8ac34` were absolute pins into the
  original image — they are elements [3]/[4]/[5] of the already byte-verified
  `recon/data/rodata_0x8ac20.c` (0x60, 0x0b, 0x0b) and are now bound onto it;
* the glyph **directories** `rodata_98e3c/_98fbc/_98fe8` were **2-byte string
  stubs** — the identical mis-classification iteration 33 fixed for the default
  font; all three are now byte-exact in `g1_app_font_rodata.c` (96 + 11 + 11
  entries, extents proven by closure on their neighbours in both directions);
* the glyph **bitmaps** live inside `rodata_d753a`, the byte-verified 59,944 B
  blob of rodata batch 4, now wired with its four interior pins.

**MEASURED, dashboard stimulus:** no fault anywhere in 20 s
(`fortify_chk_fail` 0, `z_arm_fatal_error` 0, was 1 each), every glyph memcpy
inside its 676-byte buffer, `spim_a` `p2_render` **0 → 2,665** transactions,
`JBD FrameCounter` p2 `0x3` → **`0x0A1D`**, and the panel receives
**1,499 lit pixels at peak, bbox (78,213)–(564,330)** against the oracle's
2,923 in (78,211)–(564,338) — **1,346 of them exactly the right grey value and
ZERO wrong pixels**.  This is the first dashboard render in the project.

**D-1 is still FAIL** and the reason is now a different, named defect: the
firmware **enters the dashboard, paints it in 190 ms, then returns to IDLE**
(`ui_DashBoard_task` ×3, `DashBoard_Reflash` ×5 vs the oracle's 136), so the
end-of-phase framebuffer — what D-1 grades — is blank again.
**Dashboard score: 5 PASS / 2 PARTIAL / 4 FAIL** (was 4/2/4).
D-2, **D-3** (`spim_a` `p1_boot` 34 == 34, `stream_sha256` identical), D-7,
S-D-MIC and S-D-KEYS all PASS.

**Navigation regression gate: HELD.**  `p1_boot` is **bit-identical** to the
oracle in both i35a and i35b — `1d617c65a688f10e`, 656 lit px, **0 differing
rows**; `spim_a` 126 / 109 transactions and `JBD` 0x40 / 0xAA / 0xEB all
identical to iterations 33 and 34.  G-1's `p2_render` moved 544 → 351 (i35a)
→ **116** lit px: reported as a change because it was measured, but scored
pixel-by-pixel it is an **improvement** — i35b's 116 pixels are **all 116
correct with zero wrong pixels**, where i35a drew 351 of which 249 were pixels
the shipped firmware never lights.  G-1 remains FAIL (982 missing).

Flash **737,504 → 921,576 B (93.80 % of 982,528)**; RAM unchanged 253,765 B;
`nm -u` 0; 0 duplicate globals; all pin/thread/net gates unchanged.
`g1_app_rodata_00.c` is withheld on a measured flash argument (it would reach
990,265 B, over the partition).

## Iteration 34: the dashboard is reached by REAL STIMULUS

`E_ID_SCREEN_DASHBOARD` is **not phone-commandable** — a whole-image `BL` scan
of the shipped app finds no `update_persist_task_status(_, 6, _)` call site at
all.  The firmware selects it *itself*, from `process_for_new_task` case 0
(`IDLE`) at `0x0002e1a2`
(`movs r2,#2 / movs r1,#6 / bl update_temp_task_status`), with its own reason
string **`"IMU:wakeup:dashboard"`**, when the `don` head-up gesture sets
`device_ctx[0xee4] = 2`.  The existing oracle never sees it because the
`0a0600000000` GATT write installs persist task 10 (navigation) first and wins
the race.  **So the dashboard stimulus is the navigation stimulus MINUS the GATT
write** — nothing added, nothing poked.

* **SHIPPED**: `SCREEN_ID_ctx_d5 = 0x06`, `DashBoard_Reflash` ×136,
  `p2_render` **2,923 lit px**, bbox (78,211)–(564,338),
  sha `19b1f24a09f97a8d…` — the real head-up dashboard: `Mon, Jan 1`, a large
  `00:00` clock, a Bluetooth glyph, a divider and the
  `Hold Right TouchBar / to Add QuickNote` hint.
* **OURS (`g1-i33c-app`)**: `SCREEN_ID_ctx_d5 = 0x00` — never leaves IDLE.
  **D-1 FAIL** (0 lit px; first differing row y = 211, first differing pixel
  x = 244).  **D-2 PASS**, **D-3 PASS** (`spim_a` `p1_boot` 34 == 34
  transactions, `stream_sha256` `f91505ab8dc0dd27…` **identical**), D-7 PASS.
  Root cause measured to one instruction: `lsm6dso_init_chip` reads the chip id
  back from the **parameter register** instead of the spilled stack slot the
  callee wrote, so it sees `0x3` where the I2C bus really returned `0x6C`, the
  IMU never initialises and the `don` gesture does nothing.
* **OURS (`g1-i34a-app`, that one fix)**: `SCREEN_ID_ctx_d5 = **0x06**`,
  `DISPLAY_ON = 0x01`, and `ui_DashBoard_task` / `DashBoard_Reflash` run **for
  the first time in this project** — **D-5 and D-6 PASS**.  It then hits
  `* buffer overflow detected *` in `gui_utf_draw` because
  `resource_manger_get(font=3, ch=',')` dispatches to the **still-unrecovered**
  `get_font_style3_glyph_offset`, which returns a 3,354-byte glyph for a
  676-byte buffer → `K_ERR_KERNEL_OOPS` → reset.  **D-1 still FAIL.**
  **Recovering the three remaining font families is now the single blocker.**

Full detail and every measurement in `our_boot_bringup.md` §34.

## Iteration 33: **THE RECONSTRUCTED FIRMWARE PAINTS PIXELS.**
## `p1_boot`'s 640×480 4 bpp framebuffer is **BYTE-IDENTICAL to the oracle's**
## (`sha256 1d617c65a688f10e…`, **656 == 656 lit pixels**, bbox x 178–449 /
## y 267–287, **zero differing rows**) — our rebuild renders the shipped
## firmware's own boot screen, *"Your route is being generated…"*, pixel for
## pixel.  **G-2 PASSES.**  `p2_render` paints too (**544** lit px) but draws a
## shorter string than the oracle's 1,098-px one, so **G-1 still FAILS**.

Build **`g1-i33c-app`**, net **unchanged** `g1-i30e-net`; capture
`/private/tmp/g1_ours_i33c`, report `/private/tmp/g1-i33/rep-c`.
Full detail and every measurement in `our_boot_bringup.md` §33.

Three defects, each measured before and after, took the raster from
"never runs" to "byte-exact":

1. **`g_display_msgq` was never initialised.**  All six shipped
   `K_MSGQ_DEFINE` objects came up with `msg_size = 0`, `max_msgs = 0`,
   `buffer_start = NULL`: `gen_app_data_image.py` restored only their two
   self-referential dlist heads, because the ring-buffer pointers name SRAM
   *outside* the recovered arena.  Measured consequence: `display_reflash` ran
   **226** times and `submit_display_reflash_work` **0** times — every
   `k_msgq_put` returned `-ENOMSG`, so the display thread never received a
   single message and `ui_refalsh_warp` never ran.  Fixed by restoring the
   shipped static initialiser with a dedicated ring buffer of the exact shipped
   size (`--static-msgq display`).
2. **`send_response_data_to_ble` had a 16-byte frame where the shipped
   function has 32** — instance **18** of the undersized-stack-frame class the
   parity harness is structurally blind to (`cfg_verify` PASSes before and
   after).  Its 24-byte message overran the frame and destroyed the saved LR;
   once the raster actually reached it, the epilogue popped `PC = 0` →
   `K_ERR_ARM_USAGE_ILLEGAL_EPSR` → SoC reset at t ≈ 5.9 s.
3. **The default-font resources were never recovered.**  The glyph directory
   (`rodata_9890c`), its length (`g_default_font_glyph_table_count`) and the
   packed glyph bitmaps (`rodata_e5f62`) were all raw **absolute flash pins to
   the ORIGINAL image**, so our link read its own image at those VAs.  The
   length came back as **0x2000b448 = 536,918,600**, so the directory scan for
   `'Y'` ground through half a billion iterations and the cooperative display
   thread never returned — measured as phase 2 issuing **zero** SPI and zero
   I2C transactions while burning 5 minutes of host time.  Both blobs are now
   emitted byte-exact (1,328 B + 37,050 B, extents proven two independent ways
   that agree to the byte), and the length is bound to the byte-verified
   `rodata_0x8ac20 + 8`.

| counter | oracle | iter 31 | iter 32 (`i32b`) | **iter 33 (`i33c`)** |
|---|---:|---:|---:|---:|
| machine reset / CPU halt | none | halt @ 6 s | none | **none over 20 s** |
| **`DISPLAY_ON_ctx_fe8`** | **0x01** | 0x01 | 0x01 | **0x01 — MATCHES** |
| **`ESB_SYNC_ctx_105a`** | **0x02** | 0x02 | 0x02 | **0x02 — MATCHES** |
| `esbslave MasterFramesSeen` / `AcksInjected` | 0x175 / 0x175 | 0 / 0 | 0x176 / 0x176 | **0x176 / 0x176** |
| `esbslave AnnounceResponses` | 0x15B | 0 | 0x91 | **0x167 — best ever** |
| `radio TransmittedFrames` | 0x230 | 0x4A | 0x232 | **0x231** |
| `vcentral DataEvents` | 0x215 | — | 0x212 | **0x215 — MATCHES exactly** |
| **`spim_a` `p1_boot` / `p2_render`** | **764 / 2,881** | 66 / 0 | 66 / 0 | **126 / 109** |
| `spim_a` pixel windows `p1` / `p2` | 673 / 2,752 | 6 / 0 | 6 / 0 | **64 / 106** |
| `JBD FrameCounter` `p1` / `p2` | 0x2A1 / 0xD61 | — | 0x6 / 0x6 | **0x40 / 0xAA** |
| `JBD JournalCount` | 0x400 | — | 0x42 | **0xEB** |
| `twim1` `p1` / `p2` | 371 / 599 | 240 / 0 | 346 / 628 | **346 / 587** |
| `twim2` (LSM6DSO) `p1` / `p2` | 1,089 / 1,200 | 925 / 0 | 1,041 / 700 | **1,041 / 700** |
| `saadc` whole run | 998 | 17 | 101 | **95** |
| `pdm0` / `gpiote0` / `gpiote1` | 2 / 25 / 0 | 2 / 25 / 0 | 2 / 25 / 0 | **2 / 25 / 0, hash-EQ** |
| **framebuffer lit px `p1` / `p2`** | **656 / 1,098** | 0 / 0 | 0 / 0 | **656 / 544** |
| **framebuffer sha256 `p1`** | `1d617c65…` | `0c5cc90b…` | `0c5cc90b…` | **`1d617c65…` IDENTICAL** |
| framebuffer sha256 `p2` | `b26c73b3…` | `0c5cc90b…` | `0c5cc90b…` | `b855eac0…` |

`twim1` per device (`p1_boot` / `p2_render`), ours vs oracle: nPM1300
**286 / 507** vs 291 / 508; OPT3001 **35 / 80** vs 33 / 80 — and the OPT3001
`p2_render` per-device stream **hash-matches the oracle exactly**, the first
sensor byte-stream in this project to do so; ST25DV EEPROM 11 / 0 vs 25 / 7;
ST25DV system port 14 / 0 vs 22 / 4.

| id | iter 32 | **iter 33** | first difference / detail |
|---|---|---|---|
| **G-1** | FAIL | **FAIL** | `p2_render` ours `b855eac0…`, **544 lit px**, bbox x 120–353 / y 267–287; oracle `b26c73b3…`, **1,098 lit px**, bbox x 34–497 / y 266–287.  Same band, same baseline, **shorter string**.  First differing row **y = 266**, first differing pixel **x = 37**. |
| **G-2** | FAIL | **PASS** | `p1_boot` **`1d617c65a688f10e…` == oracle**, **656 == 656 lit px**, bbox x 178–449 / y 267–287 identical, **zero differing rows**.  Byte-for-byte the golden framebuffer. |
| **G-3** | FAIL, first diff idx 66 | **FAIL, first diff idx 126** | `p1_boot` **126 vs 764**, all 126 identical entry-for-entry; oracle's idx 126 is `{"op":"0x02","x":32,"y":265,"n_pixel_bytes":9}`.  `p2_render` 109 vs 2,881, idx 0.  Ours reaches the same `p1` image in **64** windows where the oracle uses 673. |
| **G-4** | localiser | localiser | `p1_boot`: **no differing row**.  `p2_render`: first differing row **266**, first differing pixel **x = 37**. |
| **G-5** | PASS | **PASS** | panel init byte-exact over the whole 126-transaction `p1` prefix. |
| **G-6** | PASS | **PASS** | `spim_b` 0 == 0, hashes EQ, both phases. |
| **S-MIC** | PASS | **PASS** | `pdm0` whole-run hash EQ, 2 accesses. |
| **S-KEYS** | PASS | **PASS** | `gpiote0` hash EQ, 25 accesses; `gpiote1` 0 == 0. |
| **S-ALS** | PARTIAL | **PARTIAL — best ever** | OPT3001 35 / 33 and **80 / 80 with the stream hash EQUAL**. |
| **S-PMIC** | PARTIAL | **PARTIAL — best ever** | nPM1300 286 / 291 and **507 / 508**. |
| **S-IMU** | PARTIAL | **PARTIAL** | `twim2` 1,041 / 1,089 and 700 / 1,200; `IMU_ACCEL_ENABLED` True, `IMU_GYRO_ENABLED` False. |
| **S-NFC** | PARTIAL | **PARTIAL** | ST25DV EEPROM 11 / 25 and 0 / 7; system port 14 / 22 and 0 / 4. |
| **S-ADC** | FAIL | **FAIL** | `saadc` 95 / 998, hash NE. |
| **S-ESB** | PARTIAL (all 3) | **PARTIAL — all THREE criteria met** | `ctx[0x105a] == 2` ✓, `ctx[0xfe8] == 1` ✓, master PTX 0x176 all ACKed ✓; `AnnounceResponses` 0x167 vs 0x15B. |

**Criteria score: 5 PASS / 5 PARTIAL / 4 FAIL** (iteration 32: 4 / 5 / 5).
The new PASS is **G-2**, the acceptance-bar one.

**Named next blocker:** `p2_render` selects a **different, shorter navigation
string** than the oracle's *"Navigate stopped due to app disconnection."*  The
raster, the font, the canvas geometry and the baseline are all proven correct
by G-2, so this is a state/content question inside `ui_navigation_task`, not a
display one.

**Also open:** five of the six static `K_MSGQ_DEFINE` queues are still dead
(the generator supports `--static-msgq all`); 356 absolute `A` symbols remain in
the app link's FLASH range; and the clock-digit and style-3 font families are
still unrecovered raw pins.

---

## Iteration 31 record (kept) — the app's GATT service was MISSING; the display
## gate opened but the build panicked at t ≈ 6 s

## READ THIS FIRST — iteration 31: **`DISPLAY_ON_ctx_fe8` reaches 0x01 and an
## `action = 1` display START arrives, both for the first time in this
## project** — the app's own GATT service was simply MISSING from the link.
## Still 0 lit pixels, and the build now panics at t ≈ 6 s one step further on.

**NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the
oracle's **656** (`p1_boot`) / **1,098** (`p2_render`).

What changed (full detail and every measurement in `our_boot_bringup.md` §31;
capture `/private/tmp/g1_ours_i31c`, app **`g1-i31c-app`**, net **unchanged**
`g1-i30e-net`):

1. **Root cause of the display gate: the shipped `bt_gatt_service_static`
   section holds THREE services — Zephyr's GATT (8 attrs), Zephyr's GAP (7) and
   the application's own NUS-shaped transport service (`{0x0008ad18, 6}`) — and
   OUR link had only the first two.**  The 128-bit NUS UUID body occurs 5 times
   in `app_update.bin` and **0 times** in our `zephyr.bin`, so the virtual
   phone's ATT write had nothing to land on: `ble_process_req_dispatch` was hit
   **0 times** in a 20 s capture, `now_has_persist_task` returned 0 all **398**
   times, and `trigger_screen_state_change` was only ever called with
   `action = 0`.
2. **Fixed** by emitting the service in a new wiring TU
   (`recon/application/app/src/g1_bt_nus_service.c`) rather than by
   `CONFIG_BT_NUS=y`, because stock `nus.c` would bring a SECOND `nus_cb`
   singleton while the recovered one at `0x2000a2b8` is already written by the
   retained `FUN_0004f500`.  Two dangling pins (`rodata_8ad40` = `&attrs[2]`,
   `rodata_4f4f1` = `on_sent`) were rebound onto it.
3. **That unmasked a stack-frame defect in `spec_ble_command_hook`**: Ghidra
   had named two 256-byte buffers as ten scalars, so our frame was 212 bytes
   against the shipped `subw sp,sp,#1500`, and the body's own
   `memset(…, 0, 0xfc)` calls overwrote the return address (INVSTATE,
   `K_ERR_ARM_USAGE_ILLEGAL_EPSR`).  Fixed with a struct at the shipped offsets.
4. **Then the chain completes**: `ble_dispatch op=0x0a` → **`display_START
   action = 1`** → `device_info[0xfe8] = 1`.  `spim_a` `p1_boot` goes 34 → **66
   transactions, all 66 byte-identical to the oracle's**, including three
   `op 0x02` full-screen clears whose `pixel_sha256` match the oracle exactly.
5. **The next divergence is a kernel panic**, `K_ERR_KERNEL_PANIC` from
   `__ASSERT(!_THREAD_SUSPENDED)` (sched.c:1458) inside the recovered
   `z_tick_sleep`: `display_dispatch_thread` returns from `arch_swap()` still
   suspended after its post-blit 35 ms sleep.  Both cores halt at t ≈ 6 s, so
   every ESB / phase-2 / sensor volume in this build collapses to near zero.
   **Reported, not hidden**: iteration 30's app remains the build with the
   healthy 20 s run, and both are tabulated below.

| counter | oracle | iter 30 (`g1-i23a-app`) | **iter 31 (`g1-i31c-app`)** |
|---|---:|---:|---:|
| **`DISPLAY_ON_ctx_fe8`** | **0x01** | 0x00 | **0x01 — MATCHES** |
| **`ESB_SYNC_ctx_105a`** | **0x02** | 0x02 | **0x02 — MATCHES** |
| display START `action = 1` | yes | **no** | **YES** |
| machine reset / CPU halt | none | none | **halt @ t ≈ 6 s** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | **66 / 0** |
| `spim_a` `p1_boot` pixel windows | many | 3 | **6** |
| framebuffer lit px `p1` / `p2` | 656 / 1,098 | 0 / 0 | **0 / 0** |
| `twim2` (LSM6DSO) `p1` / `p2` | 1,089 / 1,200 | 1,027 / 700 | 925 / 0 |
| `twim1` `p1` / `p2` | 371 / 599 | — / 370 | 240 / 0 |
| `saadc` whole run | 998 | 95 | 17 |
| `pdm0` / `gpiote0` whole run | 2 / 25 | 2 / 25 | **2 / 25, hash-EQ** |
| `radio TransmittedFrames` | 0x230 | 0x234 | 0x4A |
| `esbslave MasterFramesSeen` | 0x175 | 0x175 | 0 |

| id | iter 30 | **iter 31** | first difference / detail |
|---|---|---|---|
| **G-1** | FAIL | **FAIL** | `p2_render` 0 lit px, 0 windows (core halted before phase 2); oracle 1,098 px, bbox x 34–497 / y 266–287. |
| **G-2** | FAIL | **FAIL** | `p1_boot` 0 lit px, **6** windows (was 3); oracle 656 px, bbox x 178–449 / y 267–287. |
| **G-3** | FAIL (trunc.) | **FAIL (trunc.) — IMPROVED** | first difference index **66** (was 34); the 66 shared `spim_a` transactions are identical entry-for-entry. |
| **G-4** | localiser | localiser | our framebuffer still `0c5cc90b07…`; oracle's first differing row **y = 267**, pixel **x = 178**. |
| **G-5** | PASS | **PASS — extended** | panel init byte-exact over the whole 66-transaction prefix. |
| **G-6** | PASS | **PASS** | `spim_b` 0 == 0, hashes EQ, both phases. |
| **S-MIC** | PASS | **PASS** | `pdm0` whole-run hash EQ, 2 accesses. |
| **S-KEYS** | PASS | **PASS** | `gpiote0` whole-run hash EQ, 25 accesses. |
| **S-IMU** | PARTIAL | **PARTIAL** (halt-truncated) | 925 / 1,089 and 0 / 1,200. |
| **S-ALS** | PARTIAL | **PARTIAL** (halt-truncated) | on `twim1`, 240 / 371 and 0 / 599. |
| **S-PMIC** | PARTIAL | **PARTIAL** (halt-truncated) | same bus. |
| **S-NFC** | PARTIAL | **PARTIAL** (halt-truncated) | same bus. |
| **S-ADC** | FAIL | **FAIL** | 17 / 998. |
| **S-ESB** | PARTIAL (2 of 3) | **PARTIAL (2 of 3, different two)** | `ctx[0x105a] == 2` ✓, **`ctx[0xfe8] == 1` ✓ (first time)**, master PTX > 0 ✗ (halt). |

**Criteria score: 4 PASS / 5 PARTIAL / 5 FAIL** (headline unchanged; G-5's
proven prefix nearly doubled and the display-on criterion is met for the first
time).

**Named next blocker:** the `sched.c:1458` `_THREAD_SUSPENDED` panic
(`our_boot_bringup.md` §31.7).  Two scheduler families — recovered
`unready_thread`/`sched_update_cache`/`z_tick_sleep` and stock sched.c's own
statics — coexist over one shared `_kernel`; audit that first.

---

## Iteration 29 record (kept) — still 0 lit pixels, but **master ESB PTX
## frames reach the virtual right lens for the FIRST time in this project**
## (`MasterFramesSeen` 0 → **0x26C**, all ACKed, first frame **byte-identical**
## to the oracle's), because `esb.c` turned out to be **stock NCS 2.5.1** —
## iteration 28's "Even modified it" verdict is WITHDRAWN with byte evidence

**NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the
oracle's **656** (`p1_boot`) / **1,098** (`p2_render`); `spim_a` is **34 / 764**
and **0 / 2,881**; **no `0x02` pixel window is emitted in `p2_render`**, so **no
display START with `action = 1` arrived** (our `firmware_events` is `{}` against
the oracle's `{"spi_read_id":1,"display_START":2,"BLIT":15}`).  The three `0x02`
transactions in `p1_boot` are the panel-init window writes the oracle also makes
there and they paint nothing.

Measured this iteration (`our_boot_bringup.md` §29; capture
`/private/tmp/g1_ours_i29a`, net `g1-i29a-net` — byte-identical to the final
`g1-i29d-net`, so the capture IS the final tree's — app **unchanged**
`g1-i23a-app`):

1. **`esb.c` is STOCK.**  Iteration 28 located only 32 of its 53 sections and
   concluded Even had vendored the FIFO/payload cluster.  Rebuilt with
   **`CONFIG_ESB_MAX_PAYLOAD_LENGTH=251`** and **`ESB_EVT_IRQ = SWI3_IRQn`**,
   **all 40 sections present in the shipped image are relocation-masked
   byte-identical** and the 39 in the main run TILE `0x01032764..0x01033b18`
   with **no gap and no overlap**.
2. **The 251 is confirmed three ways**: iteration 24's decode of the shipped
   `esb_config` (`payload_length = 0xfb`); the shipped `.bss` tiling
   (`rx_payload.0` `0x21005256` +0x800, `tx_payload.1` `0x21005a56` +0x800,
   `pids` `0x21006256`, `rx/tx_payload_buffer` 253 B each, `esb_state`
   `0x21006458`) — zero slack only at 251; and `FUN_0102b49c` staging exactly
   `packet[0] = 0xfb`.
3. **SWI3 is a real, necessary Even change**: the SDK hardcodes SWI0, but MPSL
   already owns SWI0 on CPUNET (`mpsl_init.c:38`).  The only unmasked
   difference before the change was `f04f 5300` vs `f04f 6380` — the
   `NVIC->ISPR[0]` bit for IRQ 29 vs IRQ 26 — at three sites.
4. **The whole ESB core is displaced** (37 reconstructions), with no external
   referrer of a file-local section and **no retained source touching any of
   the 28 `esb.c`-owned shipped RAM addresses**.
5. **The shipped `CONFIG_HEAP_MEM_POOL_SIZE` is 2560, not 8192** — read out of
   the shipped `.data` `_system_heap` initialiser at `0x210008b4`.  That
   measured correction freed the 4.6 KiB the correct payload length needs.
6. **A/B, reported not hidden:** giving `g_esb_rx_payload` its true 256-byte
   size (it stands on a 24-byte relocation block, and every received frame
   overruns it) is provably correct **and halts both cores** 0.29 s after the
   first ESB ACK, because it unmasks the never-before-executed
   announce-response path.  Kept in the tree, gated OFF.

| counter | oracle | iter 27 | iter 28 | **iter 29** |
|---|---:|---:|---:|---:|
| machine reset | none | **≈5.8 s** | none | **none over 20 s** |
| `radio TransmittedFrames` | 0x230 | 0x0 | 0xCF | **0x339** |
| `vcentral Connected` | True | False | True | **True** |
| `vcentral ConnectInds` / `DataEvents` | 1 / 0x215 | 0 / 0 | 1 / 0x26B | **1 / 0x26B** |
| **`esbslave MasterFramesSeen`** | 0x175 | 0 | 0 | **0x26C** |
| **`esbslave AcksInjected`** | 0x175 | 0 | 0 | **0x26C** |
| `esbslave AnnounceResponses` | 0x15B | 0 | 0 | **0x26C** |
| `ESB_SYNC_ctx_105a` | 0x02 | 0x01 | 0x01 | **0x01** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x00 | 0x00 | **0x00** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | 0 / 0 | **0 / 0** |

First master PTX frame, ours vs the oracle — **identical**:

```
ours   tx#1 len=41 8282828282200311000000000000000000000000000000000000000000000000000000000000004BFD
oracle tx#1 len=41 8282828282200311000000000000000000000000000000000000000000000000000000000000004BFD
```

`tx#3` differs: the oracle sends a sync/data frame, we repeat the `0x11`
announce — which is exactly why `ESB_SYNC_ctx_105a` never reaches `0x02`.

| device / phase | oracle | iter 27 | iter 28 | **iter 29** |
|---|---:|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 551 / 0 | 1,027 / 700 | **1,027 / 700** |
| nPM1300 `p1_boot` / `p2_render` | 291 / 508 | 97 / 0 | 232 / 370 | **232 / 370** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | 14 / 0 | **14 / 0** |
| ST25DV EEPROM / system port `p1` | 25 / 22 | 0 / 6 | 11 / 12 | **11 / 12** |
| `saadc` (whole run) | 998 | 5 | 71 | **71** |
| `gpiote0` / `gpiote1` / `pdm0` | 25 / 0 / 2 | 25 / 0 / 2 | 25 / 0 / 2 | **25 / 0 / 2, hash-EQ** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | 34 / 0 | **34 / 0** |
| `spim_b` | 0 | 0 | 0 | **0, hash-EQ** |

**Per-criterion verdicts (iteration 29):** G-5 **PASS** (34-transaction non-blit
prefix byte-exact, `0x9F` ID probe answering `0x4010`, `0x46`/`0x31` brightness
pair), G-6 **PASS**, S-MIC **PASS** (`255852a6c9…` EQ), S-KEYS **PASS**
(`2f47878f41…` EQ); S-IMU / S-ALS / S-PMIC / S-NFC **PARTIAL** (volumes above,
state flags all True); **S-ESB moves FAIL → PARTIAL** — its criterion is the
boolean triple (`ESB_SYNC_ctx_105a == 0x02`, `DISPLAY_ON_ctx_fe8 == 0x01`,
**master PTX frames > 0**) and the third is satisfied for the first time.
G-1, G-2, G-3, S-ADC **FAIL**.  G-3's first difference is at index **34** in
`p1_boot` (truncation only; oracle continues with
`{"op":"0x66","kind":"command"}`) and index **0** in `p2_render` (oracle
`{"op":"0x02","kind":"pixel_window","x":32,"y":265}`).  G-4 localiser: our
framebuffer is still bit-identical to iterations 16–28 (`0c5cc90b07…`), so the
first differing row is **y = 267** and the first differing pixel **x = 178**
(oracle `ffffff`, ours `000000`).
**Score: 4 PASS / 5 PARTIAL / 5 FAIL** (iteration 28: 4 / 4 / 6).

**Next divergence:** the announce-response path.  Our master repeats the `0x11`
announce frame forever; the oracle interleaves 26 sync/data frames.  Enabling
the proven `g_esb_rx_payload` sizing makes the firmware take that branch — and
halt — so `FUN_0102b49c` / `esb_write_payload` / `esb_start_tx` and the ESB
event IRQ stack are the named next target (`our_boot_bringup.md` §29.6).

## Everything below this line is the ITERATION 28 measurement, kept for provenance

> **CORRECTION (iteration 29).**  Item 5 below — "`esb.c` is KEPT … Even
> genuinely diverged there" — is **WRONG and is withdrawn**.  The 21
> non-matching sections were a Kconfig value (`CONFIG_ESB_MAX_PAYLOAD_LENGTH`
> 251, not 32) plus a one-line header difference (`ESB_EVT_IRQ = SWI3_IRQn`).
> With both applied, every `esb.c` section in the shipped image is
> byte-identical and the unit is displaced.  See the iteration-29 block above.

**Fifteenth measurement of `display_sensor_parity.md`'s criteria against our
rebuild** (iteration 28; previous measurements were iterations 14–27).

## READ THIS FIRST — iteration 28: still 0 lit pixels, but the ≈5.8 s reset is
## GONE, iteration 26's every sensor volume is recovered exactly, and for the
## FIRST time in this project `radio TransmittedFrames` is non-zero (**0xCF**)
## with `vcentral Connected` **True**

**NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the
oracle's **656** (`p1_boot`) / **1,098** (`p2_render`); `spim_a` is **34 / 764**
and **0 / 2,881**; **no `0x02` pixel window is emitted in `p2_render`**, so **no
display START with `action = 1` arrived** (our `firmware_events` is `{}` against
the oracle's `{"spi_read_id":1,"display_START":2,"BLIT":15}`).  The three `0x02`
transactions in `p1_boot` are the panel-init window writes the oracle also makes
there and they paint nothing.

Measured this iteration (`our_boot_bringup.md` §28; capture
`/private/tmp/g1_ours_i28b`, net `g1-i28c-net` — byte-identical to `g1-i28b-net`
so the capture IS the final tree's — app **unchanged** `g1-i23a-app`):

1. **Iteration 27's blocker was mis-identified and is now fixed.**  The assert
   string at `0x0103e73b` is `".../nrfx/drivers/src/nrfx_timer.c"`, not
   `nrfx_ipc.c` (that string ends at `0x0103e73a`), and line 202 is
   `nrfx_timer_disable`'s `NRFX_ASSERT(m_cb.state != UNINITIALIZED)`.
2. **Root cause, MEASURED with a Renode watchpoint:** `nrfx_timer_init` DID
   succeed and wrote `state = 1`; a `memcpy` from `FUN_0102b3f0 + 0x66` into
   `g_net_ctrl_status_byte` then zeroed it, because iteration 26's *compressed*
   relocation blocks put the two objects `0xb1` bytes apart where the shipped
   layout keeps them far apart.
3. **A defect the parity harness structurally cannot see:** the recovered
   `timer_configure` carried base frequency `0x000f4240` (1 MHz) where the
   shipped bytes carry `0x00f42400` (16 MHz) — **the ESB timer was clocked
   sixteen times too fast**.  Only a byte comparison against the SDK finds it.
4. **A mechanical sweep replaced crash-by-crash discovery.**  2,506 stock
   `.text` sections indexed; **153 of the 980 retained recovered net functions
   are relocation-masked byte-identical to a stock section**, 70 of them in
   units that own mutable state; **46 shipped RAM addresses attributed to
   stock-owned `.bss`/`.data` objects**.  Record:
   `recon/ownership/net_duplicate_singleton_sweep.json`.
5. **Three complete units displaced** — `nrfx_timer.c` (6 fns, 472
   distinguishing bytes), `esb_dppi.c` (12 fns, 996), `nrfx_ipc.c` (5 sections
   tiling 408 B exactly, 148).  **`esb.c` is KEPT**: only 32 of its 53 sections
   are in the shipped image and eight retained reconstructions inside its own VA
   run match none of them, so Even genuinely diverged there.
6. **`esb_init` SUCCEEDS for the first time** (probe: `FUN_010333b4 + 0x22a`,
   the `*initialized = 1` tail) and the stock `esb_ppi_init` runs.
   `esbslave MasterFramesSeen` is nonetheless still **0**.

| counter | oracle | iter 26 | iter 27 | **iter 28** |
|---|---:|---:|---:|---:|
| machine reset | none | none | **≈5.8 s** | **none over 20 s** |
| `radio TransmittedFrames` | 0x230 | 0x0 | 0x0 | **0xCF** |
| `vcentral Connected` | True | False | False | **True** |
| `vcentral ConnectInds` / `DataEvents` | 1 / 0x215 | 0 / 0 | 0 / 0 | **1 / 0x26B** |
| `esbslave MasterFramesSeen` | 0x175 | 0 | 0 | **0** |
| `ESB_SYNC_ctx_105a` | 0x02 | 0x01 | 0x01 | **0x01** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x00 | 0x00 | **0x00** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | 0 / 0 | **0 / 0** |

| device / phase | oracle | iter 26 | iter 27 | **iter 28** |
|---|---:|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 1,027 / 700 | 551 / 0 | **1,027 / 700** |
| nPM1300 `p1_boot` / `p2_render` | 291 / 508 | 232 / 370 | 97 / 0 | **232 / 370** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | 14 / 0 | **14 / 0** |
| ST25DV EEPROM / system port `p1` | 25 / 22 | 11 / 12 | 0 / 6 | **11 / 12** |
| `saadc` (whole run) | 998 | 71 | 5 | **71** |
| `gpiote0` / `gpiote1` / `pdm0` | 25 / 0 / 2 | 25 / 0 / 2 | 25 / 0 / 2 | **25 / 0 / 2, hash-EQ** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | 34 / 0 | **34 / 0** |
| `spim_b` | 0 | 0 | 0 | **0, hash-EQ** |

**Per-criterion verdicts (iteration 28):** G-5 **PASS** (34-transaction non-blit
prefix byte-exact, `0x9F` ID probe answering `0x4010`, `0x46`/`0x31` brightness
pair), G-6 **PASS**, S-MIC **PASS** (`255852a6c9…` EQ), S-KEYS **PASS**
(`2f47878f41…` EQ); S-IMU / S-ALS / S-PMIC / S-NFC **PARTIAL** (volumes above,
state flags all True); G-1, G-2, G-3, S-ADC, S-ESB **FAIL**.  G-3's first
difference is at index **34** in `p1_boot` (truncation only) and index **0** in
`p2_render`.  G-4 localiser: our framebuffer is still bit-identical to
iterations 16–27 (`0c5cc90b07…`), so the first differing row is **y = 267** and
the first differing pixel **x = 178** (oracle `ffffff`, ours `000000`).
**Score: 4 PASS / 4 PARTIAL / 6 FAIL** — iteration 26's score restored from
iteration 27's 4 / 1 / 9, with the radio and BLE-link counters ahead of both.

**Next divergence:** downstream of a working ESB bring-up — whether
`esb_write_payload` / `start_tx_transaction` (both among the eight `esb.c`
functions Even modified) key a PTX frame the provisioned slave recognises.

## Everything below this line is the ITERATION 27 measurement, kept for provenance

## READ THIS FIRST — iteration 27: still 0 lit pixels, and this iteration is a
## **REGRESSION on every counter** against iteration 26.  What it buys is
## structural: the radio-arbitration ops table is restored and complete, and the
## next blocker is named to a file and line.

**NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the
oracle's **656** (`p1_boot`) / **1,098** (`p2_render`); `spim_a` is **34 / 764**
and **0 / 2,881**; **no `0x02` pixel window is emitted in `p2_render`**, so **no
display START with `action = 1` arrived** (our `firmware_events` is `{}` against
the oracle's `{"spi_read_id":1,"display_START":2,"BLIT":15}`).  The three `0x02`
transactions in `p1_boot` are the panel-init window writes the oracle also makes
there and they paint nothing.

Measured this iteration (`our_boot_bringup.md` §27; capture
`/private/tmp/g1_ours_i27b`, net `g1-i27b-net`, app **unchanged**
`g1-i23a-app`):

1. **Iteration 26's premise is refuted by byte evidence.**  The 14 "unresolved
   Ghidra-gap functions" behind `g_net_radio_ops_table_ptr` are **stock NCS
   2.5.1 library code this link already contains**: `0x21000530` is the MPSL
   front-end-module `p_api` pointer word and `0x21000534..0x21000574` is the FEM
   API vtable, both owned by `libmpsl_fem_common.a`; the nine-entry table at
   `0x210004e0` is a SoftDevice Controller `.data` object.  All 16 vtable
   targets are **byte-identical** to the shipped code at a constant −0x34, and
   the 9 SDC-table targets match **opcode-for-opcode over all 62 instructions**.
   Reconstructing them would have duplicated singletons.
2. **The whole low `.data` window is proven stock.**  Over
   `0x21000000..0x21000574`, 256 of 349 words are byte-identical to the shipped
   `.data` and all 93 differing words are flash code pointers whose differences
   collapse to **exactly two constants, one per archive** (`0xa0` ×68, `0x34`
   ×25); the map shows 1,396 B covered by stock archive `.data` and **0**
   non-stock input sections.  New gate:
   `recon/application/verify_net_stock_data_window.py` → **PROVEN**.
3. **The ops table is RESTORED and COMPLETE — there is no atomic EXCLUDE.**
   The 52 addresses in that window are reclassified out of iteration 26's
   fabricated blocks and bound to `__data_start + <shipped .data offset>`
   (`STOCK_DATA_WINDOWS` in `recon/application/gen_net_ram_relocs.py`).  Seven
   blocks disappear, `g_net_radio_ops_table_ptr` is `0x21000530` and the word
   there reads `0x21000534` — the live 16-entry vtable.  Net RAM **−504 B**
   (63,508 B, 96.91 %) and FLASH **−144 B** (225,073 B, 97.26 %).
4. **One reconstruction corrected with byte evidence:** `FUN_01021920` saved r4
   and tail-called through ip precisely because **r3 is a live fourth
   argument**; the old `void(void)` body clobbered it.  The corrected body
   compiles to the shipped thunk **byte-for-byte**.  Stated honestly: the old,
   wrong body also passes `cfg_verify` (`PASS, 40 trials, 0 cover cases`), so
   parity is not the evidence — the bytes are.
5. **MEASURED REGRESSION, reported plainly.**  With the arbitration path live
   the CPUNET reaches a *newly executable* nrfx assert and resets the SoC at
   **≈5.8 s**: `assert_post_action("…/nrfx/drivers/src/nrfx_ipc.c", 202)` from
   our `FUN_01035028`, i.e. nrfx-IPC's
   `NRFX_ASSERT(m_cb.state != UNINITIALIZED)`.  It is the **same class** as
   item 3 — the stock `nrfx_ipc.c` initialises its own `m_cb` at `0x21009178`
   while our four recovered copies read a private zeroed block at the relocated
   `0x21004af8`.  `sdc_assertion_handler` and MPSL's `m_assert_handler` are
   **never entered**.

| device / phase | oracle | iter 24 | iter 25 | iter 26 | **iter 27** |
|---|---:|---:|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 1,027 / 268 | 551 / 0 | 1,027 / 700 | **551 / 0** |
| nPM1300 `p1_boot` / `p2_render` | 291 / 508 | 232 / 140 | 97 / 0 | 232 / 370 | **97 / 0** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | 14 / 0 | 14 / 0 | **14 / 0** |
| ST25DV NFC EEPROM / system port `p1` | 25 / 22 | 11 / 12 | 0 / 6 | 11 / 12 | **0 / 6** |
| `saadc` (whole run) | 998 | 41 | 5 | 71 | **5** |
| `gpiote0` / `gpiote1` / `pdm0` | 25 / 0 / 2 | 25 / 0 / 2 | 25 / 0 / 2 | 25 / 0 / 2 | **25 / 0 / 2 (all hash-EQ)** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | 34 / 0 | 34 / 0 | **34 / 0** |
| `spim_b` | 0 | 0 | 0 | 0 | **0 (hash-EQ)** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x0 | 0x0 / 0x0 | 0x3 / 0x3 | **0x0 / 0x0** |
| `JBD JournalCount` | 0x400 | 0x0 | 0x0 | 0x22 | **0x0** |
| `radio TransmittedFrames` | 0x230 | 0x1 | 0x2 | 0x0 | **0x0** |
| `vcentral Connected` | True | False | False | False | **False** |
| `esbslave MasterFramesSeen` | 0x175 | 0 | 0 | 0 | **0** |
| `ESB_SYNC_ctx_105a` / `DISPLAY_ON_ctx_fe8` | 0x02 / 0x01 | 0x01 / 0x00 | 0x01 / 0x00 | 0x01 / 0x00 | **0x01 / 0x00** |
| machine reset / CPU halt | none | ≈15 s | ≈1.3 s | **none (20 s)** | **≈5.8 s** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |

The phase-2 columns are 0 because both cores stop at ≈5.8 s, inside phase 1's
6 s window.  Iteration 26's numbers are the ones to beat and they are recorded
here unchanged; iteration 26's image is rebuildable from commit `806dba5c`.

## Verdicts (iteration 27)

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…` / **0 lit px** / 0 pixel windows; oracle `b26c73b37d…` / **1,098** / 2,881 transactions, bbox x 34–497, y 266–287. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…` / **0 lit px** / 3 pixel windows; oracle `1d617c65a6…` / **656** / 764 transactions, bbox x 178–449, y 267–287. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764**, the 34 shared transactions identical entry-for-entry, first difference index **34** (oracle `{"op":"0x66","kind":"command"}`, ours `<end>`).  `p2_render` **0 vs 2,881**, first difference index **0** (oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265}`). |
| **G-4** | *localiser* | our framebuffer bytes are bit-identical to iterations 16–26, so first differing row **y = 267**, first differing pixel **x = 178** (oracle `ffffff`, ours `000000`). |
| **G-5** | **PASS** | panel-init sequence byte-exact over the whole 34-transaction prefix, including the `0x9F` ID probe answering `0x4010` and the `0x46`/`0x31` brightness pair. |
| **G-6** | **PASS** | `spim_b` 0 == 0, hash-EQ, both phases. |
| **S-IMU** | **PARTIAL** | LSM6DSO 551 / 0 vs 1,089 / 1,200; `IMU_ACCEL_ENABLED` **False** vs True (was True in iteration 26), gyro False == False. |
| **S-ALS** | **FAIL** | OPT3001 14 / 0 vs 33 / 80; `ConversionReady` **False** vs True (was True in iteration 26). |
| **S-PMIC** | **FAIL** | nPM1300 97 / 0 vs 291 / 508; `ChargingEnabled` **False** vs True (was True in iteration 26). |
| **S-NFC** | **FAIL** | ST25DV EEPROM **0** vs 25, system port 6 vs 22 in `p1_boot`; 0 in `p2_render`. |
| **S-ADC** | **FAIL** | `saadc` 5 vs 998. |
| **S-MIC** | **PASS** | `pdm0` 2 == 2, hash-EQ. |
| **S-KEYS** | **PASS** | `gpiote0` 25 == 25, hash-EQ; `gpiote1` 0 == 0. |
| **S-ESB** | **FAIL** | `ESB_SYNC_ctx_105a` **0x01** vs 0x02, `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01, master PTX frames **0** vs 0x175, `radio TransmittedFrames` **0** vs 0x230. |

Score: **4 PASS / 1 PARTIAL / 9 FAIL** (G-5, G-6, S-MIC, S-KEYS pass), down from
iteration 26's 4 / 4 / 6.  Every lost cell is a consequence of the ≈5.8 s reset,
not of a different behaviour before it.

## The first divergence for iteration 28

**`nrfx_ipc.c:202`.**  The CPUNET resets at ≈5.8 s through
`assert_post_action(file="…/nrfx/drivers/src/nrfx_ipc.c", line=202)` called from
`FUN_01035028 + 0x20`, then `z_arm_svc → _oops → z_do_kernel_oops →
z_arm_fatal_error → panic`; both cores then report `PC does not lay in memory`
because the reset vector table at address 0 is empty in this machine.  The
asserted object is nrfx-IPC's control block `{handler, p_context, state}`: our
four recovered copies (`FUN_01034fa8`, `FUN_01035028`, `FUN_01035068`,
`FUN_010350a4`) read the relocated pin `g_net_gpiote_evt_handler_table`
(`0x21004af8`) while the **stock** `nrfx_ipc.c` — also linked, `nrfx_ipc_init`
at `0x01035e5c` — initialises **its own** `m_cb` at `0x21009178`.  Because
`0x21004af8` is `.bss` in the shipped image and the archive symbol is local, a
linker `PROVIDE` cannot name it: the remedy is **displacement** to the stock
singleton, the iteration-26 §26.4 pattern, with an ownership record.

## Everything below this line is the ITERATION 26 measurement, kept for provenance

## READ THIS FIRST — iteration 26: still 0 lit pixels; the machine now survives
## the **whole 20 s** for the first time since iteration 23, but
## `radio TransmittedFrames` fell to **0**

**NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the
oracle's **656** (`p1_boot`) / **1,098** (`p2_render`); `spim_a` is **34 / 764**
and **0 / 2,881**; **no `0x02` pixel window is emitted in `p2_render`**, so **no
display START with `action = 1` arrived**.  The three `0x02` transactions in
`p1_boot` are the panel-init window writes the oracle also makes there and they
paint nothing.

Measured this iteration (`our_boot_bringup.md` §26; capture
`/private/tmp/g1_ours_i26f`, net `g1-i26a-net`, app **unchanged**
`g1-i23a-app`):

1. **The CPUNET absolute-RAM-address collision class is closed structurally.**
   All **300** recovered addresses (196 linker pins + 125 raw source literals)
   are classified and bound to real storage — 70 `used, retain` blocks,
   3,416 B, one per cluster so every original relative distance stays exact.
   Both gates go to **0**: `check_net_raw_literals.py` **69 colliding / 125
   distinct → 0 / 0**, and `check_ram_pin_collisions.py --core net` (the
   `--core` option is new and additive; the app default is unchanged)
   **66 colliding + 130 free → 0 / 0, EXIT 0**.
2. **The ESB session word at `0x2100065c` is restored** to its shipped `1`
   (it read `0x0000FFFF` inside `sdc_mempool`), together with 30 further
   recovered addresses whose shipped `.data` initialiser is non-zero.  28 more
   stay zero under the atomic pointer-exclusion policy and are each named in
   the generated source.
3. **`PROVIDE(rodata_1032e41 = 0x01032e41)` — the third `rodata_`-named code
   pointer — is resolved and removed.**  It is `ecdh_thread`: the two Ghidra
   gaps iteration 25 named (`0x01032640`, `0x01032530`) are NCS `hci_ecdh.c`,
   whose stock unit is already linked, so the recovered duplicate is
   **displaced** rather than reconstructed (reconstructing it would have
   started a second ECDH thread on a second `k_poll_signal`).
4. **MEASURED: the ≈1.3 s reset is gone.**  Iteration 25's capture contains
   `PC does not lay in memory` twice at ≈1.3 s; iteration 26's 20 s capture
   contains it **zero** times and reaches the full `00:00:20.000000000`.  A
   directed 6 s probe hooked at our build's own `sdc_assertion_handler`
   (`0x01034150`) shows it is **never entered**.
5. **MEASURED REGRESSION, reported plainly: `radio TransmittedFrames` 1–2 → 0.**
   The app still calls `bt_le_adv_start` (hooked, reached once) and the CPUNET
   never keys a frame.  Root cause below.

| device / phase | oracle | iter 24 | i25b | iter 25 | **iter 26** |
|---|---:|---:|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 1,027 / 268 | 1,027 / 268 | 551 / 0 | **1,027 / 700** |
| nPM1300 `p1_boot` / `p2_render` | 291 / 508 | 232 / 140 | 232 / 140 | 97 / 0 | **232 / 370** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | 14 / 0 | 14 / 0 | **14 / 0** |
| ST25DV NFC EEPROM / system port `p1` | 25 / 22 | 11 / 12 | 11 / 12 | 0 / 6 | **11 / 12** |
| `saadc` (whole run) | 998 | 41 | 41 | 5 | **71** |
| `gpiote0` / `gpiote1` / `pdm0` | 25 / 0 / 2 | 25 / 0 / 2 | 25 / 0 / 2 | 25 / 0 / 2 | **25 / 0 / 2 (all hash-EQ)** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | 34 / 0 | 34 / 0 | **34 / 0** |
| `spim_b` | 0 | 0 | 0 | 0 | **0 (hash-EQ)** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x0 | 0x3 / 0x0 | 0x0 / 0x0 | **0x3 / 0x3** |
| `JBD JournalCount` | 0x400 | 0x0 | 0x0 | 0x0 | **0x22** |
| `radio TransmittedFrames` | 0x230 | 0x1 | 0x1 | 0x2 | **0x0** |
| `vcentral Connected` | True | False | False | False | **False** |
| `esbslave MasterFramesSeen` | 0x175 | 0 | 0 | 0 | **0** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |

`p2_render` LSM6DSO 268 → **700** and nPM1300 140 → **370** are the direct
consequence of not resetting: the phase-2 threads keep polling for the whole
14 s instead of dying part-way.  They are the highest sensor volumes this
project has measured.

## Verdicts

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…` / **0 lit px** / 0 pixel windows; oracle `b26c73b37d…` / **1,098** / 2,752 windows, bbox x 34–497, y 266–287. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…` / **0 lit px** / 3 pixel windows; oracle `1d617c65a6…` / **656** / 673 windows, bbox x 178–449, y 267–287. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764**, the 34 shared transactions byte-identical, first difference index **34** (oracle `{"op":"0x66","kind":"command"}`, ours `<end>`).  `p2_render` **0 vs 2,881**, first difference index **0** (oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265}`). |
| **G-4** | *localiser* | our framebuffer bytes are bit-identical to iterations 16–25, so first differing row **y = 267**, first differing pixel **x = 178** (oracle `ffffff`, ours `000000`). |
| **G-5** | **PASS** | panel-init sequence byte-exact over the whole 34-transaction prefix, including the `0x9F` ID probe answering `0x4010` and the `0x46`/`0x31` brightness pair. |
| **G-6** | **PASS** | `spim_b` 0 == 0, hash-EQ, both phases. |
| **S-IMU** | **PARTIAL** | LSM6DSO 1,027 / 700 vs 1,089 / 1,200; accel enabled True, gyro False — both match the oracle. |
| **S-ALS** | **PARTIAL** | OPT3001 14 / 0 vs 33 / 80; `ConversionReady` True, matches. |
| **S-PMIC** | **PARTIAL** | nPM1300 232 / 370 vs 291 / 508; `ChargingEnabled` True, matches. |
| **S-NFC** | **PARTIAL** | ST25DV EEPROM 11 vs 25, system port 12 vs 22 in `p1_boot`; 0 in `p2_render`. |
| **S-ADC** | **FAIL** | `saadc` 71 vs 998. |
| **S-MIC** | **PASS** | `pdm0` 2 == 2, hash-EQ. |
| **S-KEYS** | **PASS** | `gpiote0` 25 == 25, hash-EQ; `gpiote1` 0 == 0. |
| **S-ESB** | **FAIL** | `ESB_SYNC_ctx_105a` **0x01** vs 0x02, `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01, master PTX frames **0** vs 0x175, `radio TransmittedFrames` **0** vs 0x230. |

Score: **4 PASS / 4 PARTIAL / 6 FAIL** (G-5, G-6, S-MIC, S-KEYS pass).

## The first divergence for iteration 27

`g_net_radio_ops_table_ptr` at **0x21000530** is the pointer WORD to the
SoftDevice Controller's radio-arbitration ops table, and the table itself is
**`sym_NIQMZN22R7GGCSNM3BZ25GTCR6D457XB3DIUGWA`**, a 0x40-byte library `.data`
object that this link places at exactly the shipped address **0x21000534** (it
appears in no repository source; `nm -S` confirms the same placement in the
iteration-25 build).  That is a class-(b) interior view of a real SDK object,
and iteration 26's structural pass first bound it to a generic relocation block
whose shipped `.data` is atomically excluded — fifteen of that block's pointer
words are Ghidra-gap interior addresses that do not resolve — so the word read
**0** and every recovered accessor (`FUN_010218f0`, `FUN_01021908`,
`FUN_01021914`, `FUN_01021920`, `controller_mode2_state_validate`, all of which
read `*(uint32_t *)0x21000530` and call through `+4`) skipped the whole
arbitration path.  The binding to the real owner **by name** is in
`recon/application/net/src/timeslot_owner.c` + `recon/symbols/g1_net_globals.ld`;
`our_boot_bringup.md` §26.8 carries its measurement.

## Everything below this line is the ITERATION 25 measurement, kept for provenance

## READ THIS FIRST — iteration 25: still 0 lit pixels, but the CPUNET now
## **cycles** the ESB radio state machine, and the MPSL/radio-arbitration
## defect is confirmed by a hooked `sdc_assertion_handler`

**NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the
oracle's **656** (`p1_boot`) / **1,098** (`p2_render`); `spim_a` is **34 / 764**
and **0 / 2,881**; no `0x02` pixel-window transaction was emitted;
`trigger_screen_state_change` is reached **exactly once** and
`reflash_fb_data_to_lcd` / `pixelto4bithex` are reached **0 times**, so **no
display START with `action = 1` arrived**.

Measured this iteration (`our_boot_bringup.md` §25):

1. **The ESB radio state machine is reconstructed — 16 functions out of the
   Ghidra gaps, all parity-proven, 0 mismatches.**  Five state functions
   (`FUN_01032de4`, `FUN_01032e54`, `FUN_01032804`, `FUN_010330b0`,
   `FUN_010331c8`), the abort/restart `FUN_010329b4`, the RX-FIFO push
   `FUN_01032a3c`, the TX-FIFO pop `FUN_01032954`, the timeslot-window
   request/release trio (`FUN_01033168`, `FUN_010331a0`, `FUN_01033084`), the
   four DPPI wiring leaves (`FUN_01033cd0/d20/d54/da0`) and
   `nrfx_timer_compare` (`FUN_0103a9dc`).  Proof: `tools/parity` driven
   directly (`net_recon_kit.prove` refuses uncatalogued entries), with
   `cfg_verify`'s own catalog-derived arity/return-kind tables and hand-derived
   directed coverage — 200–500 trials each.
2. **Five continuation pointers rebound**, including two linker pins that were
   *code* pointers wearing `rodata_` names (`rodata_10335e5`, `rodata_1033655`).
3. **MEASURED: the announcement is re-armed for the first time.**  The loop
   key → RADIO DISABLED → state 3 → RADIO DISABLED → state 2 → pending bitmap →
   IRQ 0x1d → `FUN_0103289c` → `FUN_0102b50c` → key again runs end to end;
   `radio TransmittedFrames` = **2** (iteration 24: 1).  `0x210049a0` now reads
   `0x0102C14D` = `&FUN_010331c8 | 1` instead of the original literal.
4. **One more `.data` object restored**: `g1_esb_window_request` @0x21000670
   (`{0, 0x41019000, 0, len}`), previously an unowned address inside the live
   `sdc_mempool`.
5. **The blocker is now MPSL/radio arbitration, confirmed not inferred.**
   `NET sdc_assertion_handler` fires ≈0.11 s after the second ESB cycle and the
   reset takes both cores down at ≈1.3 s (iteration 24: ≈15 s).  An A/B on the
   SAME tree — the five `ADDR_*_THUMB` macros pointed back at the shipped
   literals (`/private/tmp/g1-i25b-net`) — reproduces iteration 24's numbers
   exactly and does not reach the assertion in 6 s.  So the metric regression
   below is caused by reaching a deeper, correctly-diagnosed stall earlier, not
   by a wrong reconstruction.  The provably-correct fix is **not** reverted and
   **both builds are reported**.

| device / phase | oracle | iter 24 | i25b (rebind OFF) | i25 (rebind ON) |
|---|---:|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 1,027 / 268 | 1,027 / 268 | 551 / 0 |
| nPM1300 `p1_boot` / `p2_render` | 291 / 508 | 232 / 140 | 232 / 140 | 97 / 0 |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | 14 / 0 | 14 / 0 |
| ST25DV NFC EEPROM / system port `p1` | 25 / 22 | 11 / 12 | 11 / 12 | 0 / 6 |
| `saadc` (whole run) | 998 | 41 | 41 | 5 |
| `gpiote0` / `pdm0` (whole run) | 25 / 2 | 25 / 2 | 25 / 2 (hash EQ) | 25 / 2 (hash EQ) |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | 34 / 0 | 34 / 0 |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x0 | 0x3 / 0x0 | 0x0 / 0x0 |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | **0 / 0** | **0 / 0** |

Verdicts: **G-1 FAIL**, **G-2 FAIL**, **G-3 FAIL (truncation only; first
difference at index 34, oracle `{"op":"0x66","kind":"command"}` vs `<end>`;
`p2_render` index 0, oracle `{"op":"0x02","x":32,"y":265}`)**, **G-4** first
differing row **y = 267**, first differing pixel **x = 178** (framebuffer bytes
bit-identical to iterations 16–24), **G-5 PASS**, **G-6 PASS**, **S-ESB FAIL**
(`ESB_SYNC_ctx_105a` 0x01 vs 0x02, `DISPLAY_ON_ctx_fe8` 0x00 vs 0x01).

### The first divergence for iteration 26

The SoftDevice Controller's own assertion — `sdc_assertion_handler` at our
`0x010342c4` — reached ≈0.11 s after the second complete ESB transaction.  The
radio-arbitration vtable at `0x21000530 -> 0x21000534` is fully bound (all
eight slots point at reconstructed `sym_*` code), so the next steps are the
session word at **0x2100065c** (shipped `.data` initialiser `01 00 00 00`;
currently reads `0x0000FFFF` because the address falls inside `sdc_mempool`)
and extracting the assertion's own `(file, line)` arguments.  Two further
Ghidra gaps were identified with evidence and left open: **0x01032640** (a
`k_thread_create` THREAD ENTRY — so `PROVIDE(rodata_1032e41 = 0x01032e41)` is a
third `rodata_` name that is really a code pointer) and **0x01032530**, the ESB
assign-channel/pairing work handler it calls.

## Everything below this line is the ITERATION 23 measurement, kept for provenance

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

---

# UPDATE — P4 iteration 36 (supersedes the score in §6 above)

Build `g1-i36b-app` (952,316 B, 96.93 % of the 982,528 B partition; RAM
253,765 B; `nm -u` 0; 0 duplicate globals).  Net core unchanged
(`g1-i30e-net`).  Full derivation in `our_boot_bringup.md` §36.

## Graphics — the NAVIGATION screen is BYTE-IDENTICAL in both phases

| id | iteration 35 | **iteration 36** |
|---|---|---|
| **G-1** `p2_render` framebuffer sha256 | FAIL — 116 lit px, 982 missing | **PASS — `b26c73b37d441fc8…`, 1,098 == 1,098 lit px, 0 differing rows** |
| **G-2** `p1_boot` framebuffer sha256 | PASS | **PASS — `1d617c65a688f10e…`, 656 px, 0 differing rows (regression gate held)** |
| **G-3** `spim_a` stream sha256 | FAIL | **FAIL** — 126 vs 764 and 109 vs 2,881 transactions; identical pixels, missing repeats |
| **G-5** panel init sequence | PASS | **PASS** |
| **G-6** `spim_b` unused | PASS | **PASS** |
| **D-1** dashboard `p2_render` | FAIL — peak 1,499 lit / 1,427 correct | **FAIL** at end of phase, but peak **2,895 lit / 2,659 exactly right**, bbox **(78,211)–(564,338) == the oracle's**, and every residual pixel is in the three weekday glyphs |
| **D-2** dashboard `p1_boot` | PASS | **PASS** |
| **D-3** dashboard `spim_a` `p1_boot` stream | PASS (34 == 34, sha EQ) | **PASS** |
| **D-7** `spim_b` | PASS | **PASS** |

Three root causes were found and fixed, all of the same class — **`.rodata`
regions still bound by raw absolute `PROVIDE` pins, resolving into our own
relocated image**:

1. `rodata_aae20`, the 66,560-byte **fade/dither mask atlas**.
   `ui_DashBoard_task`'s four-step entry fade ANDs the finished dashboard with
   it; frame order `01 03 05 07` ends on a 100 %-open frame, so the shipped
   firmware's last step leaves the picture on the panel.  Ours was ANDing with
   glyph bitmaps and erasing it — the "decay" of §35.12.
2. The eight **localized string tables** `rodata_8a3e0…8ab18` plus their
   3,534-byte pool `rodata_bb220` (previously an 11-byte `"ERR_STRING"` stub).
   Every non-clock label comes through them.  Emitted as **relocated** pointer
   arrays; all 8 x 66 entries verified to dereference to the shipped string.
3. Sixteen **un-symbolized `UINT32_C(0x000…)` rodata literals** in five files;
   the three in `draw_locale_adjusted_label_pair` were the navigation screen's
   entire missing text.

Plus a **stack-buffer-layout** defect in `DashBoard_Reflash`: the six `int16_t`
that `unix_timestamp_to_datetime` writes were four sets of separate C locals
with only the first one's address passed, so GCC kept the rest at zero.  Date
went `Fri, Sat 0` -> `Thu, Jan 1`; the `, Jan 1` half is now pixel-exact.

## Sensors

| id | verdict | measurement (navigation / dashboard stimulus) |
|---|---|---|
| **S-MIC** `pdm0` | **PASS** | 2 == 2 accesses, whole-run sha `255852a6c9e9…` **EQ**, both stimuli |
| **S-KEYS** `gpiote0` / `gpiote1` | **PASS** | 25 == 25 and 0 == 0, shas **EQ**, both stimuli |
| **S-ESB** | **PASS** | `ESB_SYNC_ctx_105a` 0x02 both; `DISPLAY_ON_ctx_fe8` 0x01 on navigation; `ESB_MASTER_FRAMES`/`ACKS` `0x175` == `0x175` on navigation |
| **S-ALS** `opt3001` | **PARTIAL** | nav `p2_render` **80 == 80, sha EQ**; dash `p1_boot` **14 == 14, sha EQ**; nav `p1_boot` 35 vs 33 |
| **S-PMIC** `npm1300` | **PARTIAL** | nav `p2_render` **508 == 508, sha EQ**; `p1_boot` 285 vs 291 |
| **S-NFC** `st25dv` | **FAIL** | `p1_boot` 11+14 vs 25+22; absent in `p2_render` |
| **S-IMU** `twim2` | **FAIL** | `p1_boot` 1,094 vs 1,089; `p2_render` **744 vs 1,200** — our IMU polling stops when the dashboard task exits |
| **S-ADC** `saadc` | **FAIL** | 95 vs 998 accesses, sha NE (unchanged since iteration 33) |

**Score: 8 PASS / 2 PARTIAL / 3 FAIL across the graphics+sensor criteria of the
navigation oracle** (iteration 35: 6 PASS / 2 PARTIAL / 4 FAIL), and the
navigation screen is reproduced **pixel-for-pixel** for the first time.

## The one blocker left for the dashboard

`process_for_new_task.c:601..608` (`CASE6`, `process_for_DASHBOARD_show`) calls
`update_persist_task_status_to_idle` ~600 ms after the dashboard is drawn,
which calls `display_close_screen(6)`, which STOPs the panel and runs the
fade-out.  Trigger measured by hook: `device_ctx[0xee4] == 1` with
`get_task_signal_mode() == 0` and `now_has_persist_task() != 1`.  The shipped
firmware has the same branch and never satisfies it inside the 14-second
window, which is where its 136 `DashBoard_Reflash` calls (66 ms
`DISPLAY_ACTION_RETRY`) come from.  **Named, not fixed.**

---

# UPDATE — P4 iteration 37 (supersedes every score above)

# **ALL FOUR FRAMEBUFFERS ARE BYTE-IDENTICAL TO THE SHIPPED FIRMWARE.**
# **D-1 PASSES.  Both screens work.**

Build **`g1-i37a-app`** (952,316 B, **96.93 %** of the 982,528 B partition —
**flash delta 0 B** vs `g1-i36b-app`; RAM 253,765 B, **delta 0 B**; `nm -u` 0;
0 duplicate globals; 17 weak symbols, unchanged).  Net core **unchanged**
(`g1-i30e-net`).  Full derivation in `our_boot_bringup.md` §37.

## Graphics

| id | iteration 36 | **iteration 37** |
|---|---|---|
| **D-1** dashboard `p2_render` framebuffer | FAIL (0 lit px at end of phase) | **PASS — `19b1f24a09f97a8d…` == oracle, 2,923 == 2,923 lit px, bbox (78,211)–(564,338) == oracle, 0 differing rows, 0 wrong, 0 missing** |
| **D-2** dashboard `p1_boot` | PASS | **PASS** — `0c5cc90b079d0d9c…`, 0 == 0 lit px |
| **D-3** dashboard `spim_a` | PASS (`p1_boot` 34 == 34, sha EQ) | **`p1_boot` PASS**; `p2_render` **9,212 vs 12,225** (was 2,665) — cadence only, **0 ours-only windows** |
| **D-4** localiser | first differing row 211 | **no differing row, no differing pixel** |
| **D-5** `SCREEN_ID_ctx_d5 == 6` | FAIL (`0x00`) | **PASS — `0x06`** |
| **D-6** `DISPLAY_ON` / `ESB_SYNC` | PARTIAL (`0x00` / `0x02`) | **PASS — `0x01` / `0x02`** |
| **D-7** `spim_b` unused | PASS | **PASS** |
| **G-1** navigation `p2_render` | PASS | **PASS — `b26c73b37d441fc8…`, 1,098 px, 0 differing rows (regression HELD)** |
| **G-2** navigation `p1_boot` | PASS | **PASS — `1d617c65a688f10e…`, 656 px, 0 differing rows (regression HELD)** |
| **G-3** navigation `spim_a` stream | FAIL | **FAIL** — 126 vs 764 and 109 vs 2,881, unchanged; **0 ours-only windows** |
| **G-5** panel init sequence | PASS | **PASS** |
| **G-6** `spim_b` unused | PASS | **PASS** |

**Dashboard score: 8 PASS / 3 PARTIAL / 1 FAIL** (iteration 36: 5 / 2 / 4).
**Navigation graphics: 4 of 5**, unchanged, no regression.

## The two root causes — both single instruction-decode defects

1. **`imu_mahony_ahrs_update` (`FUN_00026624 @ 0x26624`): five `VNMLS.F32`
   instructions had been reconstructed as `VMLS.F32`.**  `VNMLS` is
   `Sd = −Sd + Sn*Sm`, `VMLS` is `Sd = Sd − Sn*Sm`, so the entire
   accelerometer error vector `(ex, ey, ez)` came out negated and the
   complementary filter's feedback became **positive**.  Measured consequence:
   our fused pitch entered a **±77 deg limit cycle** with a ~5 s period instead
   of converging, sweeping in and out of the head-up window
   `[−9650, −6650]` four times per phase.  Each sweep-out set
   `device_ctx+0xee4` back to 1, which is the `*param_2 == 1` term of
   `process_for_new_task.c:601` (CASE6) — so §36's "the firmware closes the
   screen" was a *symptom* of the fusion, not a task-state bug.  After the fix
   the pitch tracks the oracle **to a hundredth of a degree** and settles at
   **−80.09 deg == the oracle's −80.09 deg**; `0xee4` reaches 2 in the *same
   100 ms sample* as the oracle and never returns to 1; `send_event(3)`
   (head-down) is never emitted.  CASE6 itself was **not modified**.
2. **`uarte_nrfx_irq_rx_ready` (`FUN_000165b4 @ 0x165b4`): the literal-pool
   constant `0x12345678` had been reconstructed as a POINTER DEREFERENCE.**
   `0x165b8 ldr r3,[pc,#12]` loads the retained-block validity magic;
   `0x165ba subs r0,r0,r3` compares.  Reading it as memory made a cold boot
   look like a valid retained block, so `init_dashboard_info` took the wrong
   branch and never seeded the RTC record with **`0x65920080`** (2024-01-01,
   a Monday); it got `0 + 1 = 1` instead (1970-01-01T00:00:01, a Thursday).
   Measured: `H37 set_sync_ts 0x1` on every `sync_to_slave`.  With the fix the
   date line renders **`Mon, Jan 1`** and the last 236 wrong + 264 missing
   pixels of §36 are gone.

Both fixes are **pure expression edits**: flash and RAM deltas are exactly 0 B,
`_end` `0x2003ff45` and `runtime_info_sync` `0x00015b8c` unchanged.

## Sensors

| id | verdict | measurement (navigation / dashboard stimulus) |
|---|---|---|
| **S-MIC** `pdm0` | **PASS** | 2 == 2 accesses, whole-run sha **EQ**, both stimuli |
| **S-KEYS** `gpiote0` / `gpiote1` | **PASS** | 25 == 25 and 0 == 0, shas **EQ**, both stimuli |
| **S-ESB** | **PASS** | `ESB_SYNC_ctx_105a` `0x02` and `DISPLAY_ON_ctx_fe8` `0x01` on **both** stimuli (dashboard was `0x00` in iteration 36); nav `RADIO_TX` `0x230` == `0x230` |
| **S-IMU** `twim2` | **PARTIAL — dashboard `p2_render` now BYTE-IDENTICAL** | dash `p2_render` **1,206 == 1,206, device stream sha EQ** (iteration 36: 766 vs 1,206); nav `p2_render` **1,200 == 1,200** count, sha NE (was 744 vs 1,200); `p1_boot` 1,080 vs 1,075 / 1,094 vs 1,089 |
| **S-ALS** `opt3001` | **PARTIAL** | nav `p2_render` **80 == 80, sha EQ**; dash **14 == 14** and **59 == 59, sha EQ both phases**; nav `p1_boot` 35 vs 33 |
| **S-PMIC** `npm1300` | **PARTIAL** | dash `p2_render` **514 == 514** (sha NE); `p1_boot` 279 vs 285 |
| **S-NFC** `st25dv` | **FAIL** | `p1_boot` 11+14 vs 25+22; absent in `p2_render` (0 vs 7+4) |
| **S-ADC** `saadc` | **FAIL** | 95 vs 998 accesses, sha NE (unchanged since iteration 33) |

## The only remaining display gap: `G-3`/`D-3`, and it is **cadence, not content**

Comparing the two `spim_a` streams as ordered sets of
`(x, y, n_pixel_bytes, sha256(payload))`:

| stimulus / phase | our windows | oracle windows | **ours-only distinct** | oracle-only |
|---|---:|---:|---:|---:|
| DASH `p1_boot` | 3 | 3 | **0** | 0 (streams identical) |
| DASH `p2_render` | 8,916 | 11,812 | **0** | 368 |
| NAV `p1_boot` | 64 | 673 | **0** | 67 |
| NAV `p2_render` | 106 | 2,752 | **0** | 67 |

**Zero** pixel windows we emit are absent from the shipped stream.  The gap is
entirely extra small repeats the original emits: on navigation it is *exactly*
the 9-byte windows (609 in `p1_boot`, 2,646 in `p2_render`, we emit none) with
every other size matching term-for-term; on the dashboard the `319 B` windows
match **800 == 800** and the full-canvas blits **2 == 2** / **4 == 4**, and the
gap is the oracle's 1/10/89/99-byte sub-region refreshes around `y 316..319`.
Each such write puts back bytes that are already there, which is why the
composed framebuffer is bit-exact.  Root: the periodic `DISPLAY_ACTION_RETRY`
sub-region refresh does not run at the original's rate.  **Named, not fixed.**

### 6. A sixth unwired `.rodata` pin, fixed but with NO measured effect

`batt_soc_curve_estimate` (`FUN_0000e2b4`) copies a 64-byte struct out of
`rodata_88570` and hands it to `battery_soc_curve_model_init`.  Shipped bytes at
`0x88570` are a 4x4 binary32 **diagonal `diag(1e-6, 1e-6, 1e-8, 2e-4)`** — an
EKF process-noise matrix Q — and the pin was still
`PROVIDE(rodata_88570 = 0x00088570)`, so our build read its own rodata there
(an unrelated pointer table, ~1e-40 as floats).  Emitted byte-exact as
`recon/data/rodata_0x88570.c` and rebound; `tools/verify_data.py` now reports
**994 files / 50,647 bytes / 100.00 % byte-exact**, up from 993 / 50,583.

This was pursued because it was the predicted upstream cause of the SAADC
cadence gap (a stuck battery percentage failing the `> 0x1d` gate at
`handle_box_placement_event+0xbc`).  **That prediction did not hold.**  Measured
in `g1-i38d-app`: `saadc` **668** accesses (unchanged), ST25DV **11 + 14**
transactions (unchanged), and the SAADC `RESULT.PTR` histogram still
`15 x 0x20028766, 15 x 0x20028786` — two call stacks, not three.  The pin fix is
kept because reading our own image at `0x88570` is wrong on its face, but it is
reported here as **a correct fix with no observable behavioural change**, not as
a closure.

## Reproducibility

The dashboard capture was run **twice end-to-end** from the same
`g1-i38c-app`/`g1-i30e-net` pair and reports the identical numbers on every
gated field, including `twim2` **1,075 == 1,075** and **1,206 == 1,206** with
the stream sha EQUAL in both runs.  That matters because
`display_sensor_parity.md` §8.3 lists `twim2` `p2_render` as **not** stable
across runs of the shipped firmware under this stimulus — the match is
reproduced, not observed once.  The shipped navigation oracle was also
re-captured this session and reproduces the stored `display_sensor_oracle.json`
field-for-field, so the navigation per-device diffs above are against a
verified target.

## Gates

`check_ram_pin_collisions.py` **0 / 0** both cores (app bound 624 / escaping 0);
`check_net_raw_literals.py` **0 / 0 / 0**; `check_thread_create_stack_args.py`
**10/10**; `verify_net_stock_data_window.py` **PROVEN**;
`gen_retained_sources.py --check` clean; app `nm -u` **0**, duplicate GLOBAL
definitions **0**; no `--allow-multiple-definition`, no weak-symbol or
numeric-root hacks; `armemul` and `tools/` untouched; nothing committed.

---

# UPDATE — P4 iteration 38 (supersedes every score above)

# **THE SENSOR BUSES CLOSE.  The whole LSM6DSO boot stream, the whole nPM1300 boot**
# **stream and every shared ST25DV transaction are now BYTE-IDENTICAL;**
# **the nPM1300 `p1_boot` stream is byte-exact and the SAADC conversion cycle is**
# **register-for-register exact (only its DMA target — a stack address — differs).**

Build **`g1-i38d-app`** (948,828 B, **96.57 %** of the 982,528 B partition;
RAM 253,765 B, **delta 0 B**; `_end` `0x2003ff45` and `runtime_info_sync`
`0x00015b8c` unchanged; `nm -u` 0; 0 duplicate GLOBAL definitions; 17 weak
symbols, unchanged).  `g1-i38c-app` (950,220 B) is the immediately preceding
build — everything except §6's battery-EKF pin — and both are reported below
wherever they differ.  Net core **unchanged** (`g1-i30e-net`).  Derivation in
`our_boot_bringup.md` §38.

> **Flash-delta caveat, stated honestly:** the working tree during this
> iteration also carried a *concurrent* literal-inlining pass over the nine
> source trees, so the −3,488 B against iteration 37's 952,316 B is **not**
> attributable to this iteration alone.  This iteration's own additive cost was
> measured in isolation in `g1-i38a-app`: **+24 B** (the emitted
> `struct adc_channel_cfg`).  Every other fix here is a pure expression /
> argument / devicetree edit.

## Graphics — the acceptance bar HELD, byte-for-byte

| id | iteration 37 | **iteration 38 (`g1-i38d-app`)** |
|---|---|---|
| **D-1** dashboard `p2_render` | PASS | **PASS — `19b1f24a09f97a8d…` == oracle, 2,923 == 2,923 lit px, bbox (78,211)–(564,338) == oracle; `cmp` against `golden_framebuffer_dashboard_p2_render.raw` reports NO DIFFERENCE** |
| **D-2** dashboard `p1_boot` | PASS | **PASS** — `0c5cc90b079d0d9c…`, 0 == 0 lit px (all-zero, byte-compared) |
| **D-3** dashboard `spim_a` | `p1_boot` PASS | **`p1_boot` PASS** (34 == 34, sha EQ); `p2_render` 9,212 vs 12,225 — cadence only |
| **D-5 / D-6 / D-7** | PASS | **PASS** — `SCREEN_ID_ctx_d5` `0x06`, `DISPLAY_ON` `0x01`, `ESB_SYNC` `0x02`, `spim_b` 0 |
| **G-1** navigation `p2_render` | PASS | **PASS — `b26c73b37d441fc8…`, 1,098 px; `cmp` vs `golden_framebuffer_p2_render.raw`: NO DIFFERENCE** |
| **G-2** navigation `p1_boot` | PASS | **PASS — `1d617c65a688f10e…`, 656 px; `cmp` vs `golden_framebuffer_p1_boot.raw`: NO DIFFERENCE** |
| **G-3** navigation `spim_a` | FAIL | **FAIL** — 126 vs 764 and 109 vs 2,881, unchanged; still **0 ours-only windows** |
| **G-5 / G-6** | PASS | **PASS** |

**Dashboard-oracle score, enumerated over all 14 `D-*`/`S-D-*` gates**
(D-4 is a localiser, not a gate):

* **9 PASS** — D-1, D-2, D-5, D-6, D-7, `S-D-MIC`, `S-D-KEYS`, `S-D-ESB`,
  `S-D-ALS`;
* **3 PARTIAL** — D-3 (`p1_boot` exact, `p2_render` cadence),
  **`S-D-IMU`** (`p1_boot` byte-identical — *new*; `p2_render` count-exact and
  sample-phase-sensitive), **`S-D-PMIC`** (`p1_boot` byte-identical — *new*;
  `p2_render` kick phase);
* **2 FAIL** — `S-D-NFC` (missing tail, every shared transaction now exact),
  `S-D-ADC` (missing call site + stack address).

The same enumeration for iteration 37 is **8 PASS / 4 PARTIAL / 2 FAIL**.  The
net movement is therefore **+1 PASS** (`S-D-ALS`, which the iteration-37 report
scored PARTIAL on the navigation phase) and, more substantively, two PARTIALs
whose `p1_boot` half went from "differs" to **byte-identical**.  Iteration 37's
headline "8 PASS / 3 PARTIAL / 1 FAIL" counted a slightly different item set and
is not directly comparable.

**`S-D-IMU` is deliberately NOT scored PASS.**  Its `p2_render` hash is EQ on
`g1-i38c-app` (two runs) and NE on `g1-i38d-app`, and the navigation phase flips
the other way — the difference is always a handful of accelerometer sample
values one gesture sub-step early, never a register or an ordering.  A criterion
that a 1,392-byte flash shift can flip is not a stable PASS and is not reported
as one.

**Navigation graphics: 4 of 5**, unchanged, no regression.

## The six defects

All six were found by diffing the per-device transaction stream against the
oracle, taking the **first differing transaction**, and reading the shipped
instructions at the call site.  **None of the code defects is caught by
`tools/cfg_verify.py`**: every one of the six changed bodies returns
`PASS cases=0` both before and after the fix (measured this session by
reverting two of them and re-running the verifier).

### 1. `S-D-ADC` — the `struct adc_channel_cfg` was an unwired `.rodata` pin

`adc_nfc_init` (`0x24b98`) calls `api->channel_setup(dev, &rodata_88a2a)`.
`rodata_87c20` (the `struct device`) was rebound onto the real DT node back in
iteration 11, but the **configuration it points at** was left as a bare
`PROVIDE(rodata_88a2a = 0x00088a2a)` — an ORIGINAL-image flash address.  Our
link read its own image there, so no channel was ever configured, and
`adc_nfc_run`'s `adc_read` (which selects `channels = BIT(3)`) bailed out on the
driver's "channel not configured" path.  Directly measured: our `saadc` stream
ran only `CH0/CH1/CH2.PSELP <- 0`, all three from PC `0x5EED6` =
`adc_nrfx_read+0xd6`, the per-channel deselect store — i.e. the driver walked
the channel mask and gave up the moment it reached channel 3.

Shipped bytes at `0x88a2a` are `00 04 00 00 03 04 00` =
`{ ADC_GAIN_1_6, ADC_REF_INTERNAL, ADC_ACQ_TIME_DEFAULT, channel_id 3,
single-ended, AIN3, disabled }` — exactly what §4.5 of
`display_sensor_parity.md` independently decodes from the shipped
`CH3.PSELP/PSELN/CONFIG` writes.  Emitted as
`recon/application/app/src/g1_adc_channel_cfg.c`; the object the build produces
is **`00 04 00 00 03 04 00`, byte-identical to the shipped seven bytes**, so
the pin is byte-exact and not merely semantically equivalent.

**Measured: `saadc` 95 → 668 register accesses (oracle 998).**  Every one of
our 30 conversion cycles is now **register-for-register identical** to the
oracle's 22-access cycle; a full diff of the two streams has **zero lines
present in ours that are absent from the oracle**.  Two residues remain:
* the DMA `RESULT.PTR` value (oracle `0x200275CE`, ours `0x20028766`) — the
  buffer is a **stack local** of `adc_nfc_run`, so this is a RAM-layout
  artifact, not a firmware defect;
* **30 conversion cycles against the oracle's 45** — a cadence difference,
  named and not fixed.

`S-D-ADC` therefore stays **FAIL** on the strict whole-run hash, but the
failure has moved from "the channel is never configured" to "the same cycle,
run 30 times instead of 45, into a different stack address".

### 2. `S-D-IMU` — a POINTER's bit 2 was read instead of the register byte's

`audio_codec_get_reg14_bit2` (`FUN_0007fe72` @ `0x7fe72`) is the LSM6DSO
`sh_master_get`: open the sensor-hub bank, read `MASTER_CONFIG` (0x14) into the
`sp+4` stack slot, extract bit 2 (`MASTER_ON`), store it through the caller's
out-pointer.  The shipped instructions are unambiguous:

```
0007fe86  add   r2, sp, #4        ; the read buffer
0007fe8a  bl    #0x7f97c          ; read_reg(ctx, 0x14, sp+4, 1)
0007fe8e  ldrb.w r3, [sp, #4]     ; <-- the BYTE THAT WAS READ
0007fe94  ubfx  r3, r3, #2, #1
0007fe9c  strb  r3, [r7]          ; *out = bit
```

The reconstruction had `*param_2 = (param_2 >> 2) & 1` — **bit 2 of the
out-pointer itself**.  `lsm6dso_init_chip` therefore saw a non-zero master
flag and issued a spurious `sh_master_set(0)`: the five extra transactions
`0140 / 14 / R 00 / 1400 / 0100` that made our `twim2` `p1_boot` 1,080 against
the oracle's 1,075.

*Why the harness could not see it:* the callee is modelled as an order-keyed
oracle that never writes the output buffer, so under emulation `sp+4` still
holds `param_2` (the `push {r0,r1,r2}` prologue put it there) and the broken
expression computes exactly the same value as the correct one.  The fixed body
is harness-equivalent **and** correct against the real callee.

**Measured, dashboard stimulus: `twim2` `p1_boot` 1,075 == 1,075 with the
stream sha EQUAL, and `p2_render` 1,206 == 1,206 with the stream sha EQUAL.
The whole LSM6DSO bus is byte-identical in both phases → `S-D-IMU` PASSES.**
On the navigation stimulus `p1_boot` is 1,089 == 1,089 with the *only*
difference a single 4-transaction `0x28`/`0x22` poll pair sitting one block
later relative to the ODR change (no content difference), and `p2_render` is
1,200 == 1,200 with **5 of 1,200** transactions differing — all of them
accelerometer sample *values* during the `don` gesture, i.e. a sampling-phase
offset on the played waveform, not a register or ordering difference.

### 3. `S-D-PMIC` (a) — the watchdog's `reset-gpios` was missing from the overlay

The shipped `struct wdt_npm1300_config` at `0x8bb50` is
`{ mfd = 0x87c80 ("pmic@6b"), reset_gpios = { 0x87c98 ("gpio-controller"),
pin 2, flags 0x0001 = GPIO_ACTIVE_LOW } }`.  Our `pmic_wdt` node had no
`reset-gpios`, so `config->reset_gpios.port` was NULL and
`wdt_npm1300_init()` skipped `gpio_pin_configure_dt(...,
NPM1300_GPIO_WDT_RESET_ON)` — the six GPIO-bank writes
`060206 061600 060C00 061100 060700 061B00` at the head of nPM1300 boot.
Added to `recon/board/g1_board.overlay`.

### 4. `S-D-PMIC` (b) — a dropped 4th register argument

`panel_temp_calibration_init` (`FUN_00062644`, the recovered
`npm1300_charger_init`) writes the ADC `TASKNTCMEASURE` register.  The shipped
call is a four-register one:

```
0006284a  movs r3, #1     ; data   = 1
0006284c  movs r1, #5     ; base   = 5 (ADC bank)
0006284e  mov  r2, r3     ; offset = 1 (TASK_TEMP)
00062850  ldr  r0, [r5]
00062852  bl   #0x83dc8
```

The reconstruction passed three, so the data byte was whatever `r3` held:
measured `05 01 74` on the bus against the shipped `05 01 01`.

**Measured, dashboard stimulus: `npm1300` `p1_boot` 279 → 285 == 285 with the
stream sha EQUAL.**  `p2_render` is 514 == 514 and the sha still differs — but
with the 68 `070401` watchdog-kick writes removed the two streams are
**byte-identical**; the single difference is that one kick lands one slot
earlier relative to the LDO1 enable.  The kick lattice has drifted ~107 ms in
phase by t ≈ 10.8 s (mean period 208.2 ms ours vs 204.84 ms oracle).  That is a
feed-thread timing residue, named and not fixed, so `S-D-PMIC` stays
**PARTIAL**.

### 5. `S-D-NFC` — three dropped register arguments in one ST25DV call chain

| shipped instruction | argument that was dropped | measured wrong transaction |
|---|---|---|
| `0x25552 ldrb.w r1,[sp,#7]` / `0x25558 and r1,r1,#0xfe` / `0x25560 bl 0x7c9fe` | the `EH_CTRL_Dyn` payload byte | ST25DV 0x53 wrote **`20 02 58`** instead of `20 02 00` |
| `0x24f5c ubfx r1,r4,#8,#2` / `0x24f60 orr r1,r1,#0xc` / `0x24f6a bl 0x7c8fa` | the value byte | propagated into the next line |
| `0x7c920 movs r3,#1` … `0x7c92a bl 0x25850` | the I2C byte **COUNT** | ST25DV 0x57 wrote a **26-byte** frame `000118…585800` instead of the 3-byte `00 01 0C` — streaming our own stack frame (`E48B0020` = `&g_st25dv_dev`, `1D240200` = a return address) onto the bus and clobbering system registers 0x01–0x18 |

A fourth site of the same class — `ipc_ept_op_b_guarded` dropping the read
length — had already been fixed in `recon/app/src` in **iteration 32** but was
never propagated to `recon/named` / `recon/readable_sources`; the compiled
`recon/symbolized/app` copy did carry it, so it was latent, not live.  All four
are now consistent across every tree.

**Measured: both corrupted transactions are now byte-exact.**  ST25DV 0x53
transactions 1–11 and 0x57 transactions 1–14 are **byte-identical to the
oracle**; the first difference moved from index **7** to index **12** (0x53) and
from index **13** to index **15** (0x57).  What remains is a *missing tail*, not
a wrong byte: the oracle's NDEF/WLC record write at t ≈ 4.226 s
(`0x57` MEM_SIZE 0x0014 / BLOCK_SIZE 0x0016 reads, then `0x53`
`0000 → E1404001`, `0004031C`, the 30-byte `0006 91 06 06 57 4C 43…` record and
the `0022FE` terminator) never runs in our build, and the `p2_render` repeat of
it is absent too (0 vs 7 and 0 vs 4).  `S-D-NFC` stays **FAIL**; the localised
next probe is in §38 of `our_boot_bringup.md`.

## Sensor criteria — iteration 38

| id | iteration 37 | **iteration 38** | measurement |
|---|---|---|---|
| **S-D-MIC** `pdm0` | PASS | **PASS** | 2 == 2, whole-run sha **EQ**, both stimuli — the *negative* criterion (never enabled, never started) still holds |
| **S-D-KEYS** `gpiote0/1` | PASS | **PASS** | 25 == 25 and 0 == 0, shas **EQ**, both stimuli |
| **S-D-ESB** | PASS | **PASS** | `ESB_SYNC` `0x02` and `DISPLAY_ON` `0x01` on both stimuli |
| **S-D-IMU** `twim2` | PARTIAL | **`p1_boot` PASS — byte-identical; `p2_render` count-exact and sample-phase-sensitive** | dash `p1_boot` **1,075 == 1,075 sha EQ** *(new, and identical on both i38c and i38d)*; dash `p2_render` **1,206 == 1,206**, sha **EQ on `g1-i38c-app`** (reproduced over two runs) and **NE on `g1-i38d-app`** by exactly **4 of 1,206** transactions — all of them accelerometer sample *values* one gesture sub-step ahead, no register or ordering difference.  Navigation is the mirror image: `p2_render` 1,200 == 1,200 sha **EQ on i38d**, NE by 5 sample values on i38c.  Gyro still disabled (`IMU_GYRO_ENABLED False`) — the second *negative* criterion holds |
| **S-D-ALS** `opt3001` | PARTIAL | **PASS on the dashboard oracle** (unchanged by this iteration — it was already EQ in iteration 37; the PARTIAL score was carried by the navigation phase) | dash **14 == 14 sha EQ** and **59 == 59 sha EQ**; nav `p2_render` **80 == 80 sha EQ**, nav `p1_boot` 35 vs 33 (one extra RESULT read pair) |
| **S-D-PMIC** `npm1300` | PARTIAL | **PARTIAL — dashboard `p1_boot` byte-identical** | dash `p1_boot` **285 == 285 sha EQ** *(new, both builds)*; dash `p2_render` 514 == 514, byte-identical once the 68 `070401` watchdog kicks are removed; nav `p1_boot` **291 == 291 on i38d** with the only difference one kick moved six slots (292 vs 291 on i38c); nav `p2_render` 527 vs 508 (one extra 22-transaction poll block + a kick-count difference) |
| **S-D-NFC** `st25dv` | FAIL | **FAIL — every shared transaction is now byte-exact** | `p1_boot` 11 vs 25 and 14 vs 22, first difference at index 12 / 15 (was 7 / 13); `p2_render` 0 vs 7 and 0 vs 4 |
| **S-D-ADC** `saadc` | FAIL | **FAIL — the conversion cycle is now register-exact and the outer period already matches** | 668 vs 998 accesses; **30 vs 45 identical cycles**; only `RESULT.PTR` (a stack address) differs within a cycle.  The cadence gap is **not** a wrong period: grouping the conversions by `RESULT.PTR` gives the oracle **3 distinct call stacks x 15** and ours **2 x 15** — the outer 15-per-20 s rhythm is already exact and one of three call sites is missing (§ below) |

### 6. A sixth unwired `.rodata` pin, fixed but with NO measured effect

`batt_soc_curve_estimate` (`FUN_0000e2b4`) copies a 64-byte struct out of
`rodata_88570` and hands it to `battery_soc_curve_model_init`.  Shipped bytes at
`0x88570` are a 4x4 binary32 **diagonal `diag(1e-6, 1e-6, 1e-8, 2e-4)`** — an
EKF process-noise matrix Q — and the pin was still
`PROVIDE(rodata_88570 = 0x00088570)`, so our build read its own rodata there
(an unrelated pointer table, ~1e-40 as floats).  Emitted byte-exact as
`recon/data/rodata_0x88570.c` and rebound; `tools/verify_data.py` now reports
**994 files / 50,647 bytes / 100.00 % byte-exact**, up from 993 / 50,583.

This was pursued because it was the predicted upstream cause of the SAADC
cadence gap (a stuck battery percentage failing the `> 0x1d` gate at
`handle_box_placement_event+0xbc`).  **That prediction did not hold.**  Measured
in `g1-i38d-app`: `saadc` **668** accesses (unchanged), ST25DV **11 + 14**
transactions (unchanged), and the SAADC `RESULT.PTR` histogram still
`15 x 0x20028766, 15 x 0x20028786` — two call stacks, not three.  The pin fix is
kept because reading our own image at `0x88570` is wrong on its face, but it is
reported here as **a correct fix with no observable behavioural change**, not as
a closure.

## Reproducibility

The dashboard capture was run **twice end-to-end** from the same
`g1-i38c-app`/`g1-i30e-net` pair and reports the identical numbers on every
gated field, including `twim2` **1,075 == 1,075** and **1,206 == 1,206** with
the stream sha EQUAL in both runs.  That matters because
`display_sensor_parity.md` §8.3 lists `twim2` `p2_render` as **not** stable
across runs of the shipped firmware under this stimulus — the match is
reproduced, not observed once.  The shipped navigation oracle was also
re-captured this session and reproduces the stored `display_sensor_oracle.json`
field-for-field, so the navigation per-device diffs above are against a
verified target.

## Gates

Run against `g1-i38d-app` / `g1-i30e-net`:
`check_ram_pin_collisions.py` **0 / 0** both cores (app bound **624** /
escaping **0**; net bound 170 / escaping 0); `check_net_raw_literals.py`
**0 / 0 / 0**; `check_thread_create_stack_args.py` **10/10**, EXIT 0;
`verify_net_stock_data_window.py` **PROVEN**;
`gen_retained_sources.py --check` clean; `gen_app_data_image.py --selftest`
clean; `tools/verify_data.py` **994 / 994 files, 50,647 / 50,647 bytes,
100.00 %**; app `nm -u` **0**; duplicate GLOBAL definitions **0**; no
`--allow-multiple-definition`, no weak-symbol or numeric-root hacks (17 weak
symbols, unchanged); `cfg_verify` PASS on all six changed bodies; `armemul` and
`tools/` logic untouched; nothing committed.

All four framebuffer gates re-confirmed on `g1-i38d-app` by `cmp` against the
golden `.raw` files: dashboard `p2_render`, navigation `p2_render` and
navigation `p1_boot` all report **no difference**, and dashboard `p1_boot` is
all-zero as the oracle is.


---

# UPDATE — P4 iteration 39 (`g1-i39c-app`, net unchanged `g1-i30e-net`)

Full detail, every command and every number: `our_boot_bringup.md` §39.

**One root cause, three defects, all proven from the shipped instructions
before a line was changed.**  §38.1 and §38.6 had localised the SAADC's missing
third per-tick conversion call site and the missing ST25DV NDEF/WLC record
write to the same subtree, gated on `device_info[0xfc0] > 0x1d` in
`handle_box_placement_event` (`0x255e6..0x255ec`).  A Renode probe measured that
byte as **0 for the whole 20 s run**, against the shipped firmware's **100**,
with byte-identical fuel-gauge inputs (`v = 0x408fe76d`, `i = 0`,
`t = 0x41c80000`) on both sides.

1. **`fuel_gauge_sample_init_timestamp` dropped word 3 of a stack-passed
   record** — the constant `0x00088a50` the shipped prologue plants at
   `sp+0x14`.  That word is the **battery-curve table**, 5,632 B, which
   `battery_soc_curve_model_init` memcpy's into the estimator workspace.  There
   was no `rodata_88a50` pin at all; the table is now emitted byte-exact as
   `recon/data/rodata_0x88a50.c` (extent closed twice: the `mov.w r2,#0x1600`
   memcpy length and the ledger gap to `rodata_8a050`).  Estimator-workspace
   diff vs the shipped run: **1452 of 1502 differing words -> 40**.
2. **`__floatdisf` was called with no argument and its result read from the
   wrong register** — it is an alias of `__aeabi_l2f`, a soft-float helper
   (r0:r1 in, raw bits out in **r0**), and the reconstruction declared it
   `float __floatdisf(void)` under the hard-float ABI.  The elapsed-time
   argument reaching the EKF was **0.0 for every sample**.  Battery **0 -> 4..5**.
3. **`battery_soc_curve_model_init` used the WRONG PARAMETER** — ten sites read
   the fifth float (`charge_low`, s4) where the shipped function reads the
   third (`limit`, s2, held in s18 from `0000e572 vmov.f32 s18,s2`), and the
   `t0 >= t1` branch dropped `0000e928 vmov.f32 s18,s14`.  Battery **-> 92**,
   and the init's `*result` is now `0x408fe76d` — **byte-identical to the
   shipped firmware**.  `cfg_verify` mismatches on `FUN_0000e53c`: **40 -> 13**
   of 43 cases (still FAIL; it was already on `AGENTS.md`'s STILL-OPEN list).

**Consequence, and the honest cost.**  The gate opens,
`box_placement_animation_step` runs (3 entries / 20 s vs the shipped 15) and
`st25dv_build_and_write_ndef_records` is called for the first time — but it
never returns: `event_record_init` installs a three-entry op vtable from the
literals `0x0007c38b / 0x00024a41 / 0x00025021`, all three still bare
`PROVIDE(... = <original address>)` pins, and `invoke_optional_op_offset12`
`bx`es straight into our own relocated `.text`.  All three targets are genuine
functions the corpus never recovered.  Measured: the low-speed thread emits its
last bus transaction at **t = 4.3882 s** and nothing for the remaining 15.6 s,
so `saadc` **668 -> 184** and nPM1300 `p1_boot` **285 -> 535** with its stream
sha **EQ -> NE**.

| criterion | `g1-i38d` | **`g1-i39c`** |
|---|---|---|
| dashboard `p2_render` framebuffer | `19b1f24a…` 2,923 px, `cmp` clean | **unchanged, `cmp` clean** |
| dashboard `p1_boot` framebuffer | all-zero | **unchanged** |
| navigation `p2_render` framebuffer | `b26c73b3…` 1,098 px, `cmp` clean | **unchanged, `cmp` clean** |
| navigation `p1_boot` framebuffer | `1d617c65…` 656 px, `cmp` clean | **unchanged, `cmp` clean** |
| **`D-3`** `spim_a` `p1_boot` | 34 == 34 sha EQ | **34 == 34 sha EQ — PASS** |
| `S-D-IMU` `twim2` `p1_boot` | sha EQ | **sha EQ** |
| `S-D-ALS` `opt3001` | sha EQ | **sha EQ both phases, both stimuli** |
| `S-D-MIC` / `S-D-KEYS` | sha EQ | **sha EQ** |
| `S-D-PMIC` `p1_boot` | sha EQ | **NE (535 vs 285) — REGRESSED** |
| `S-D-ADC` | 668 / 998 | **184 / 998 — REGRESSED** |
| `device_info[0xfc0]` | 0 | **92** (shipped 100) |
| `box_placement_animation_step` | never reached | **runs** |

**`G-3` vs `D-3`, settled with evidence.**  `D-3` is a **PASS**, not a cadence
gap.  `G-3` is a **real behavioural difference, not a Renode artifact**:
navigation `spim_a` is 126 vs 764 (`p1_boot`) and 109 vs 2,881 (`p2_render`)
while the `p1_boot` framebuffer is byte-identical, and
`display_sensor_parity.md` §2.1 records the **shipped** navigation `spim_a`
stream as bit-identical across two full runs — so that stream is deterministic
under these knobs and a 6x count difference cannot be scheduling jitter.  Every
window we emit the oracle also emits (0 ours-only windows), so the content is
right and the **invocation count** is wrong: the shipped raster redraws the same
rows ~6x more often.  By contrast the *dashboard* `p2_render` stream is
documented as non-deterministic in the shipped firmware itself (12,225 vs
12,161) and is explicitly not a gate — cadence sensitivity is real, but only
for the continuously-repainting screen.

**IMU / PMIC phase-2 drift, characterised.**  On `g1-i39c` `twim2` is sha EQ for
dashboard `p1_boot` and for navigation `p2_render`, and NE for the other two —
the EQ/NE pattern **flipped** versus `g1-i38d` under a change that adds only
5,632 B of `.rodata` and touches no IMU code.  That is direct evidence for
§38.2's reading that the `p2` IMU hash rides on sampling phase against the
gesture playback, not on content.

## Gates (iteration 39)

`g1-i39c-app` / `g1-i30e-net`: app FLASH **954,460 B / 982,528 B = 97.14 %**
(+5,632 B, all of it the emitted curve table); app RAM **253,765 B, delta 0**;
`nm -u` **0**; duplicate GLOBAL definitions **0**;
`check_ram_pin_collisions.py` **0 / 0** both cores (app bound **624** /
escaping **0**; net bound 170 / escaping 0);
`check_thread_create_stack_args.py` **10/10**, EXIT 0;
`gen_app_data_image.py --selftest` clean; `tools/verify_data.py` **995 / 995
files, 56,279 / 56,279 bytes, 100.00 %**; all four framebuffer gates
re-confirmed by `cmp` against the golden `.raw` files.  `cfg_verify`
`FUN_0002ea28` **PASS** (and the pre-fix body now **FAILs 3/3** after its
reviewed stack-object fixture was corrected from `(-40,-36,20)` to
`(-40,-40,24)` — the only `tools/` change, a fixture description, not verifier
logic).  `FUN_0000e53c` **FAIL 13/43**, open.  Net core, `armemul` and
`recon/refactor/` untouched; nothing committed.
