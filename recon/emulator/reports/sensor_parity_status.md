# Sensor + graphics parity status — OUR rebuilt firmware vs the shipped oracle

**Eighteenth measurement of `display_sensor_parity.md`'s criteria against our
rebuild** (iteration 31; previous measurements were iterations 14–30).

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
