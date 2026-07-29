# Display driver naming proposal — grounded in the JBD013VGA-4010 datasheet

**Status: PROPOSAL ONLY. No source file was edited by this pass.**

Sources used, and how each claim is cited below:

| tag | source |
|---|---|
| `[DS §x]` | `~/Projects/frame-codebase/g1/datasheets/JBD013VGA-4010_datasheet_text.txt` (v2.21, Jan 2022), section number as printed in the datasheet |
| `[DS T5]` | Instruction Table (Table 5), `JBD013VGA_instruction_table.txt` |
| `[BIN 0x…]` | Thumb disassembly of the shipped `app_update.bin`, read through `tools/extract.py` (link base 0xC200, MCUboot header 0x200). Every opcode quoted below was read out of the image in this pass, not taken from a name. |
| `[TRACE]` | `recon/emulator/reports/display_sensor_parity.md` / `recon/analysis/staged_refactor_r7_validation.md` — Renode SPI captures of the **shipped** firmware |

Disassembly helper used (scratchpad, capstone THUMB/MCLASS over `extract.read(va, n)`):
`/private/tmp/claude-501/.../scratchpad/dis.py`.

No `cfg_verify` result is cited anywhere in this document.

---

## 0. The part is confirmed, not assumed

`spi_read_id` @ `0x47724` sends `9F 00 00 00`, takes the 4 received bytes and
returns `(rx[2] << 8) | rx[3]`. `jdb_panel_init` @ `0x46fc0` compares that
against **`0x4010`** and logs *"JBD PANEL init failure!"* otherwise.

`[DS §7.3.1]` RDID: `SI = 9FH, 00H, 00H, 00H` → `SO = —, (MF7-MF0), (ID15-ID8), (ID7-ID0)`.
`[DS Table 4]` Device ID **JBD013VGA = 0x4010**, manufacturer `0xBD`.

The firmware reads the ID from exactly the two bytes the datasheet places it on,
and hard-compares it to the datasheet's device ID. **The panel is a JBD013VGA.**
`[TRACE]` confirms the live exchange: `0x9F tx=9F000000 rx=…4010`.

---

## 1. Function-by-function mapping

Addresses are app-core VAs. "Opcode on the wire" is the literal that reaches
byte 0 of the SPI transaction, read from the shipped image.

### 1.1 Transport primitives

| addr | current name | opcode on the wire | datasheet meaning | proposed name | conf |
|---|---|---|---|---|---|
| `0x7d82e` | `projector_send_command` | *(caller-supplied)* cmd byte then `len` payload bytes, one CS-framed transaction | `[DS §4.3.1]` standard-SPI instruction framing | `jbd_spi_cmd_write` | high |
| `0x7d77c` | `projector_send_cmd_immediate` | 1 byte, no payload | `[DS T5]` the "single commands" class (`66/99/97/A3/A9/71/72/73/06/04`) | `jbd_spi_cmd_single` | high |
| `0x7d7b6` | `projector_spi_write_chunked` | — (splits any buffer into ≤`0xF000`-byte transactions) | — (SPIM EasyDMA limit, not a panel limit) | keep, or `jbd_spi_write_split` | high |
| `0x47698` / `0x476a8` | `projector_bus_lock` / `_unlock` | — | — | keep | high |
| `0x7d772` | `delay_ms` | — | `k_busy_wait(ms*1000)`; see §3.1 for why it is always 1 ms | keep | high |
| `0x7d63e` | `thunk_FUN_0007d77c` | `b.w 0x7d77c` | tail-call thunk | `jbd_spi_cmd_single_thunk` | high |

`[BIN 0x7d82e]` `strb r0,[sp]` (cmd) → `bl 0x86c1e` (memcpy of `len` bytes to `sp+1`)
→ `bl 0x7d7b6` with `r1 = len + 1`. So: **one transaction = opcode byte followed
by the payload, nothing else**, matching `[DS §4.3.1]`.

### 1.2 Register writes — the renames that matter

| addr | current name | opcode | datasheet | proposed name | conf |
|---|---|---|---|---|---|
| `0x7d67e` | `projector_send_cmd_0x46` | **`0x46`** + 1 byte | `[DS §7.3.11 / §6.4]` Current Register Write, `CUR[5:0]` = µLED bias current | **`jbd_write_current_reg`** | **high** |
| `0x7d696` | **`net_pkt_write_be16`** ← WRONG | **`0x36`** + 2 bytes, `rev16` first | `[DS §7.3.9 / §6.3]` Luminance Register Write, `LUM15-LUM8` then `LUM7-LUM0` | **`jbd_write_luminance_reg`** | **high** |
| `0x7d658` | `projector_send_cmd_c0` | **`0xC0`** + 2 bytes, then `0x97`, then 1 ms | `[DS §7.3.13 / §6.5]` Display Center (Offset) Register Write, `R4-R0` then `C4-C0` | **`jbd_set_display_center`** | **high** |
| `0x7d642` | `projector_send_cmd1` | *(caller-supplied)* + 1 byte | generic 8-bit register write; only ever called with `0x01` and `0x31` = `[DS §7.3.21/§7.3.23]` Write Status Register 1 / 2 | **`jbd_write_reg8`** | high |

Evidence, verbatim from the image:

```
[BIN 0x7d67e]  push {r0,r1,r2,lr} ; movs r2,#1 ; strb.w r0,[sp,#7]
               add.w r1,sp,#7 ; movs r0,#0x46 ; bl 0x7d82e
[BIN 0x7d696]  push {r0,r1,r2,lr} ; rev16 r0,r0 ; strh.w r0,[sp,#4]
               movs r2,#2 ; movs r0,#0x36 ; add r1,sp,#4 ; bl 0x7d82e
[BIN 0x7d658]  movs r2,#2 ; strb.w r0,[sp,#4] ; strb.w r1,[sp,#5]
               movs r0,#0xc0 ; bl 0x7d82e ; movs r0,#0x97 ; bl 0x7d77c
               movs r0,#1 ; bl 0x7d772
[BIN 0x7d642]  movs r2,#1 ; strb.w r1,[sp,#7] ; add.w r1,sp,#7 ; bl 0x7d82e
               (r0 = caller's opcode, untouched)
```

**`FUN_0007d696` is not a networking function.** It is the panel luminance
write. The `rev16` is not a network byte order conversion — it is there because
`[DS T5]` orders the luminance bytes **LUM15-LUM8 first**, and the value lives
in a little-endian halfword. It is currently declared in
`.../display/g1_display.h` as `extern void net_pkt_write_be16(unsigned int);`,
inside the display module, called only from `panel_write_xy_reg_cached` and
`set_brightness_to_panel_reg`. This is the single highest-value rename in the set.

Corollary: **`panel_write_xy_reg_cached` @ `0x47028` is also misnamed.** It has
nothing to do with X/Y. `[BIN 0x47028]` it caches two values in
`g_panel_reg_x_cache` / `g_panel_reg_y_cache` and, on change, calls
`0x7d696` (**luminance**) for the first and `0x7d67e` (**current**) for the
second. Proposed: **`jbd_set_brightness_cached(uint16_t luminance, uint8_t current)`**,
with the globals renamed `g_jbd_luminance_cache` / `g_jbd_current_cache`.

### 1.3 Display-state commands

| addr | current name | opcodes | datasheet | proposed name | conf |
|---|---|---|---|---|---|
| `0x7d74e` | `projector_reset_sequence` | `0x66` then `0x99` | `[DS §7.3.4]` Enable Reset then Reset — and the datasheet *mandates* this two-command order | **`jbd_software_reset`** (keep semantics) | high |
| `0x475f0` | `jbd_panel_suspend` | `0xB9` + 1 dummy byte (`0xFF`) | `[DS §7.3.5 / T5]` Deep Power Down `B9H` + Dummy | keep — **already correct** | high |
| `0x47638` | `jbd_panel_resume` | — (calls `panel_init` + brightness) | `[DS §4.4.2]` release from DPD. Note: it does **not** send `ABH`; it re-inits. See §5.3 | `jbd_panel_resume` (keep, add comment) | high |
| `0x47724` | `spi_read_id` | `0x9F` | `[DS §7.3.1]` RDID | **`jbd_read_device_id`** | high |
| `0x47538` | `panel_init` | full init block, see below | `[DS §4.1.4]` Display Process Flow | **`jbd_panel_program_init_sequence`** (or keep `panel_init`) | high |
| `0x46fc0` | `jdb_panel_init` | — | (typo: **jdb** → **jbd**) | **`jbd_panel_init`** | high |

### 1.4 Pixel path

| addr | current name | opcode | datasheet | proposed name | conf |
|---|---|---|---|---|---|
| `0x476b4` | `projector_transfer_pixel_chunk` | **`0x02`** + 3 address bytes + `0xFF` dummy + N payload + 1 trailing byte | `[DS §7.3.15]` SPI Write Buffer Data | **`jbd_buffer_write_window`** | **high** |
| `0x7d70a` | `projector_write_pixel_data` | `0x02` ×k then `0x97` + 1 ms | `[DS §4.2.2]` partial refresh + `[DS §7.3.6]` Sync | **`jbd_buffer_write_and_sync`** | high |
| `0x7d6ae` | `projector_fill_framebuffer` | `0x02` ×3 (61440 + 61440 + 30720 B) | full 640×480 @ 4 bpp = 153 600 B `[DS §1]` | **`jbd_buffer_fill_full_frame`** | high |
| `0x7d6f4` | `projector_fill_and_sync` | above + `0x97` + 1 ms | | **`jbd_clear_screen`** | high |
| `0x47260` | `reflash_fb_data_to_lcd` | `0x02` ×rows then **one** `0x97` + 1 ms | `[DS §4.2.2]` partial refresh, `[DS §4.1.4]` one Sync per frame | **`jbd_blit_rows_and_sync`** | high |
| `0x473c8` | `reflash_fb_data_to_lcd_ex` | same, plus a source-row bias | | **`jbd_blit_rows_and_sync_offset`** | high |
| `0x7d4d6` | `projector_flush_canvas` | via `0x7d70a` | | keep | high |

The `0x02` header is the strongest single piece of evidence in this document.

`[BIN 0x476b4]`:
```
ldr r1, [pc, #0x54]          ; literal @0x47720 = 0x0007FC00
and.w r1, r1, sb, lsl #10    ; sb = row  ->  row << 10, masked to 9 bits
ubfx  r4, r4, #0, #0xa       ; r4 = col, masked to 10 bits
orrs  r4, r1
strb r3, [r5, #-0x5]  (r3=2)   <- opcode 0x02
strb  ..., [r5, #-0x4]  = addr >> 16     <- A23-A16
strb  ..., [r5, #-0x3]  = addr >> 8      <- A15-A8
strb  ..., [r5, #-0x2]  = addr           <- A7-A0
strb r3, [r5, #-0x1]  (r3=0xFF)          <- Dummy
... transceive(dev, r5-5, byte_count + 6, ...)
```
`[DS §7.3.15]` gives, for `02H`: `Byte1 = 02H, Byte2..4 = A23-A16 / A15-A8 / A7-A0,
Byte5 = Dummy`, and the note **“Address = {5'b00000, ROW[8:0], COL[9:0]}”**.

`0x0007FC00` is exactly a 9-bit field starting at bit 10. The shipped constant
**is** the datasheet's address format, bit for bit. The `0xFF` at `[r5,#-1]` is
the datasheet's `Dummy` byte. The `+6` length is `5 header + N payload + 1`,
where the trailing `1` covers `[DS §7.3.15]` *“Final 4 dummy clocks are needed.”*

---

## 2. `panel_init` decoded line by line

`[BIN 0x47538]`, cross-checked against `[TRACE]` §3.1 (the same block appears on
the wire twice, at t≈0.1017 s and t≈3.9242 s).

| call in the shipped code | wire bytes | `[DS]` meaning |
|---|---|---|
| `projector_reset_sequence()` | `66` , `99` | §7.3.4 Enable Reset + Reset |
| `send_cmd_immediate(0x06)` | `06` | §7.3.19 Write Enable (WEL — **required before any status-register write**) |
| `send_cmd1(0x01, 0x10)` | `01 10` | §7.3.21 Write Status Register 1 ← **decoded in §2.1** |
| `fill_framebuffer(0)` | `02` ×3, 61440+61440+30720 B | §7.3.15, clears all 153 600 B = 640×480 @ 4 bpp |
| `send_cmd_c0(0x00,0x00)` | `C0 00 00` + `97` | §7.3.13 Display Center = (row 0, col 0) |
| `send_cmd_c0(0x00,0x14)` | `C0 00 14` + `97` | (row 0, col 20) |
| `send_cmd_c0(0x18,0x00)` | `C0 18 00` + `97` | (row 24, col 0) |
| `send_cmd_c0(0x18,0x14)` | `C0 18 14` + `97` | (row 24, col 20) |
| `send_cmd_c0(0x0C,0x0A)` | `C0 0C 0A` + `97` | (row 12, col 10) |
| `send_cmd_immediate(0x71)` + `0x97` | `71` , `97` | §7.3.25 Display Default Mode (mirror off) — “After mirror command, the SYNC command is needed” |
| `send_cmd_immediate(0x73)` + `0x97` | `73` , `97` | §7.3.25 Display **RIGHTLEFT** mirror + required Sync |
| `send_cmd_0x46(0x0F)` | `46 0F` | §7.3.11 Current Register `CUR[5:0] = 15` |
| `send_cmd1(0x31, 0x04)` | `31 04` | §7.3.23 Write Status Register 2 ← **decoded in §2.2** |
| `send_cmd_immediate(0xA3)` + `0x97` | `A3` , `97` | §7.3.7 Display Enable, then the Sync it requires |

### 2.1 The `C0` sweep proves the argument order — and the panel geometry

`[DS §6.5]` Offset Register **reset values: ROW = 0x0C, COL = 0x0A**.
`[DS §4.1.2]` “Total number of pixels: 660x504, **extra 20 columns and 24 rows**
pixels for optical alignment purpose.”

The shipped sequence walks `(0,0) → (0,20) → (24,0) → (24,20) → (12,10)`:
the four corners of the legal offset rectangle (`0..24` rows × `0..20` columns —
exactly the datasheet's alignment margin) and then the datasheet's own reset
value, which is its geometric centre. This is an alignment-servo exercise, and
it pins the parameter order: **first argument = ROW, second = COLUMN**, agreeing
with `[DS T5]` (`C0H | R4-R0 | C4-C0`).

> Note a real inconsistency **inside the datasheet**: Table 5 orders the C0H
> payload `R4-R0` then `C4-C0`, while the text extraction of Figure 26 lists
> `C4-C0` before `R4-R0`. The shipped firmware, read against the reset values
> `ROW=0x0C / COL=0x0A` and the 24-row/20-column margin, agrees with **Table 5**.
> Confidence high but not certain: `0x0C, 0x0A` is also self-consistent under a
> swap; the discriminator is the corner sweep, where `0x18 = 24` can only be a
> ROW value (COL max is 20) and `0x14 = 20` can only be a COLUMN value.
> That is decisive.

### 2.2 The two status-register writes, decoded

**`01 10` — Status Register 1** `[DS §6.2]`, layout `W0 | GMAEN | RFFQ[2:0] | Reserved[2:0]`:

```
0x10 = 0b0 0 010 000
        │ │  │    └── Reserved = 000                (datasheet: "need to write 3'b000") OK
        │ │  └─────── RFFQ[2:0] = 010  -> panel refresh 90 Hz @ 9.6 MHz internal OSC
        │ └────────── GMAEN = 0        -> gamma correction DISABLED
        └──────────── W0 = 0           -> demura DISABLED (reset value is 1)
```

Three separately checkable facts fall out:
* the panel's **own** scan rate is **90 Hz** — see §3.2;
* `[DS §6.2]` note: at `RFFQ = 010` the legal luminance range is **0…7109**;
  the measured luminance on the wire is `0x0612 = 1554` `[TRACE]`, in range;
* demura is switched **off** by the firmware even though the datasheet's reset
  value enables it. `[DS §6.2]` bit 7 is described twice and contradictorily
  (“W0: Write 0 at any reset release status” vs “1: Enable demura (default)”).
  The firmware follows the *first* reading.

**`31 04` — Status Register 2** `[DS §6.2]`, layout `…| SPF | RFHF | PORF | SYNC_S | OSCS[1:0]`:

```
0x04 = 0b0000 0 1 00
                │ └── OSCS[1:0] = 00 -> internal oscillator 9.6 MHz (datasheet default)
                └──── SYNC_S   = 1   -> "SYNC command has NO screen-off function (suggestion)"
```

Both bits are load-bearing for §3:
* `OSCS = 00` ⇒ 9.6 MHz ⇒ `[DS §7.3.6]` Sync reload time = **0.83 ms**;
* `SYNC_S = 1` ⇒ Sync does **not** blank the screen, so the host may Sync often
  without visible flicker. `[DS §4.1.4]` warns the screen is off ~1 ms during
  Sync *in the default mode*; the firmware opts out of exactly that.

### 2.3 The brightness ladder

`set_brightness_to_panel_reg` @ `0x46e3c` `[BIN]`:

```
06                     Write Enable            [DS §7.3.19]
A9                     Display Disable         [DS §7.3.8]
36 <lum15:8> <lum7:0>  Luminance Register      [DS §7.3.9]   (via 0x7d696)
46 <cur>               Current Register        [DS §7.3.11]  (via 0x7d67e)
31 04                  Status Register 2       [DS §7.3.23]
A3                     Display Enable          [DS §7.3.7]
97 + delay_ms(1)       Sync                    [DS §7.3.6]
```

The ladder is two-stage and it matches the register widths:
* levels **0…5** modulate `LUM[15:0]` and leave `CUR = 0`;
* levels **≥6** pin luminance at its calibrated maximum and set
  `CUR = level − 6`. `[DS §6.4]` `CUR` is **6 bits (0…63)** — so the current
  stage has exactly 64 steps, and `level − 6` cannot overflow the field for
  levels 6…69. The field width and the code's range agree.
* the luminance quantum is `0x6F = 111`; the captured value `0x0612 = 1554 = 14 × 111`
  `[TRACE]`, and `[BIN]` computes it as `(cal + 1) * 0x6F` with the per-device
  calibration halfword at `device_info + 0xED8` (= 13 on the captured unit).
  `[DS §7.3.8]` also explains the `A9`/`A3` bracket: “In order to release from
  this status and restore display, Display enable and SYNC command is needed.”

`[DS §7.3.19]` explains the leading `06`: “The WEL bit must be set prior to write
status registers instruction.” The firmware issues `06` before every `01`/`31`.

---

## 3. The two unexplained measurements

### 3.1 The `0x97` that terminates each 21-blit group — **explained**

`[DS §7.3.6]` Sync (97H): *“Reload buffer data to Pixel latch, and start to scan
screen”*, and *“data transfer to the buffer during synchronization is prohibited,
which can lead to unexpected errors”*, with a table giving **0.83 ms @ 9.6 MHz**.
`[DS §4.1.4]`: write the frame into the buffer, **then one SYNC updates the panel**.
`[DS §4.2.2]`: partial refresh — you may write only the rows you changed.

The shipped code is a literal implementation of that paragraph:

`[BIN 0x47260]` `reflash_fb_data_to_lcd` loops `for (row = y0; row <= y1; row++)`,
emitting **one `0x02` SPI Cache Write per row**, and then, **once, after the
loop**, `projector_send_cmd_immediate(0x97); delay_ms(1);`.

So a “21-blit group” is not a mystery cadence at all — it is **one `reflash`
call covering 21 rows**. `[TRACE]` measured the animated cell at rows
**265…285 inclusive = exactly 21 rows**, 9 pixel bytes each. One buffer fill,
one Sync. That is the datasheet's frame protocol, unmodified.

Two further confirmations that this reading is right, both from the same trace:

* the boot groups are `3, 0×8, 3, 0×8, 3, 55`. The `3`s are
  `projector_fill_framebuffer`'s three clear bands (192 + 192 + 96 rows), which
  send no Sync of their own, so the group is closed by the *next* command's Sync.
  The eight zero-blit groups that follow are then fully accounted for, one
  datasheet requirement each: **seven** from `panel_init` — the five `C0`
  writes `[DS §7.3.13]`, the `71` and `73` mirror commands (“After mirror
  command, the SYNC command is needed” `[DS §7.3.25]`) and the `A3` Display
  Enable (“SYNC command is needed to active LEDs driving signal” `[DS §7.3.7]`),
  minus the one that closed the 3-blit group — plus **one** from
  `set_brightness_to_panel_reg`, which `jdb_panel_init` calls immediately after
  `panel_init` and which ends `A3, 97` `[DS §7.3.8]`. 7 + 1 = 8, on the wire and
  in the datasheet. `[TRACE]` §3.1 shows exactly this two-column block.
* **every single `0x97` in this firmware is followed by `delay_ms(1)`**, in all
  six call sites (`0x7d658`, `0x7d6f4`, `0x7d70a`, `0x47260`, `0x473c8`,
  `0x47538`/`0x46e3c`). `[BIN 0x7d772]` `delay_ms` is `k_busy_wait(ms * 1000)` —
  a **busy** wait, not a sleep. `[DS §7.3.6]` requires 0.83 ms of bus silence at
  9.6 MHz, and the firmware selects 9.6 MHz in §2.2. **1 ms is 0.83 ms rounded up**,
  and busy-waiting is how you guarantee the prohibited window stays empty.

This is a complete, mechanical explanation of the `0x97` cadence: **one Sync per
completed partial-frame, followed by the datasheet's mandatory reload window.**

### 3.2 The 66.62 ms / 15.01 Hz refresh — **the datasheet positively excludes a panel origin**

It does *not* explain the number, and that is itself the result.

`[DS §6.2]` the panel's own scan frequency is `RFFQ[2:0]`, and at 9.6 MHz the
eight legal values are **30 / 60 / 90 / 120 / 150 / 180 / 210 / 240 Hz**
(at 19.2 MHz: 60…480 Hz). **15.01 Hz is not among them, and is not a divisor of
any of them by an integer the register can express.** The firmware writes
`RFFQ = 010` (§2.1) and `OSCS = 00` (§2.2), i.e. **the panel is scanning at 90 Hz**
the entire time the host is submitting at 15.01 Hz.

The datasheet says this is the intended arrangement, not a bug:
* Features, p.1: *“ULED panels can self-refresh internally and increase the frame
  rate above 60Hz.”*
* `[DS §4.1.4]`: *“Master device can transfer subsequent frame data during the
  period of panel display, another SYNC command will update the panel image.”*

So **66.62 ms is a host-side content-submission period, not a display refresh
period.** The panel holds the last Sync'd frame in its pixel latch and keeps
scanning it at 90 Hz; the host repaints a 640×21-pixel cell 15 times a second.
Calling it “the display refresh cadence” in earlier reports was a category error:
the display refresh is 90 Hz and is set by a register write we can now read.

What 66.62 ms *is*: `recon/analysis/staged_refactor_r7_validation.md` §5.2
localises the 155 groups to `ui_navigation_task`'s animation, over
`10.43246 s` — the same 10 s window as that task's `SYNC_RETRIES = 10` countdown.
That is a Zephyr timer question, not a panel question, and this pass did not
close it. `66.62 ms ≈ 2183 ticks` at Zephyr's 32768 Hz tick, which is **not**
`K_MSEC(66)` (2163 ticks) and not `32768/15` (2184.5); the residue is presumably
the per-iteration work (21 SPI rows + one 1 ms busy-wait). **Flagged as not
identified — see §6.**

---

## 4. Proposed constants — ready to paste

Derived from `[DS T5]` and `[DS §6.x]`. Names use the `JBD_` prefix so they never
collide with Zephyr/NCS symbols. Only opcodes and fields the shipped firmware
actually uses are marked `/* used */`.

```c
/* recon/headers/jbd013vga.h  -- JBD013VGA-4010 uLED panel, datasheet v2.21.
 * Command opcodes: datasheet Table 5 (section 7.2).
 * This header names constants; it asserts nothing about the firmware. */
#ifndef JBD013VGA_H
#define JBD013VGA_H

#include <stdint.h>

/* ---- Read ID / power-down -------------------------------------- 7.3.1-7.3.5 */
#define JBD_CMD_READ_ID                 0x9Fu  /* used: spi_read_id      */
#define JBD_CMD_RELEASE_POWER_DOWN      0xABu
#define JBD_CMD_DEEP_POWER_DOWN         0xB9u  /* used: jbd_panel_suspend, +1 dummy */

/* ---- Software reset ------------------------------------------------- 7.3.4 */
#define JBD_CMD_RESET_ENABLE            0x66u  /* used */
#define JBD_CMD_RESET                   0x99u  /* used; must follow 0x66  */

/* ---- Display operations --------------------------------------- 7.3.6-7.3.8 */
#define JBD_CMD_SYNC                    0x97u  /* used; needs the reload window */
#define JBD_CMD_DISPLAY_ENABLE          0xA3u  /* used */
#define JBD_CMD_DISPLAY_DISABLE         0xA9u  /* used */

/* ---- Mirror ------------------------------------------------------- 7.3.25 */
#define JBD_CMD_MIRROR_DEFAULT          0x71u  /* used; Sync required after */
#define JBD_CMD_MIRROR_UPDOWN           0x72u
#define JBD_CMD_MIRROR_RIGHTLEFT        0x73u  /* used; Sync required after */

/* ---- Brightness --------------------------------------------- 7.3.9-7.3.12 */
#define JBD_CMD_LUMINANCE_WRITE         0x36u  /* used; LUM15:8 then LUM7:0  */
#define JBD_CMD_LUMINANCE_READ          0x37u
#define JBD_CMD_CURRENT_WRITE           0x46u  /* used; CUR[5:0]             */
#define JBD_CMD_CURRENT_READ            0x47u

/* ---- Display centre / offset ------------------------------ 7.3.13-7.3.14 */
#define JBD_CMD_DISPLAY_CENTER_WRITE    0xC0u  /* used; ROW[4:0] then COL[4:0] */
#define JBD_CMD_DISPLAY_CENTER_READ     0xC1u

/* ---- Buffer (cache) access ------------------------------- 7.3.15-7.3.18 */
#define JBD_CMD_BUFFER_WRITE            0x02u  /* used; SPI, 4 bpp           */
#define JBD_CMD_BUFFER_READ             0x03u
#define JBD_CMD_BUFFER_WRITE_QSPI       0x62u
#define JBD_CMD_BUFFER_READ_QSPI        0x63u
#define JBD_CMD_BUFFER_WRITE_QSPI_1BIT  0x52u
#define JBD_CMD_BUFFER_READ_QSPI_1BIT   0x53u
#define JBD_CMD_BUFFER_FAST_WRITE_1BIT  0x54u

/* ---- Protect / status ------------------------------------ 7.3.19-7.3.24 */
#define JBD_CMD_WRITE_ENABLE            0x06u  /* used; sets WEL before 0x01/0x31 */
#define JBD_CMD_WRITE_DISABLE           0x04u
#define JBD_CMD_STATUS1_WRITE           0x01u  /* used */
#define JBD_CMD_STATUS1_READ            0x05u
#define JBD_CMD_STATUS2_WRITE           0x31u  /* used */
#define JBD_CMD_STATUS2_READ            0x35u
#define JBD_CMD_STATUS3_WRITE           0x57u
#define JBD_CMD_STATUS3_READ            0x59u

/* ---- Self test ---------------------------------------------------- 7.3.26 */
#define JBD_CMD_SELFTEST_ALL_OFF        0x13u
#define JBD_CMD_SELFTEST_ALL_ON         0x14u
#define JBD_CMD_SELFTEST_CHK1           0x15u
#define JBD_CMD_SELFTEST_CHK2           0x16u

/* ---- Misc (documented, unused by this firmware) --------- 7.3.3/7.3.27/28 */
#define JBD_CMD_READ_CHIP_INFO          0x81u  /* also "OTP read", 7.3.28 */
#define JBD_CMD_TEMPERATURE_READ        0x26u  /* 7.3.27 */

/* ================= geometry (section 1, 4.1.2, 5) ======================== */
#define JBD_ACTIVE_WIDTH        640u
#define JBD_ACTIVE_HEIGHT       480u
#define JBD_TOTAL_WIDTH         660u   /* +20 columns of alignment margin */
#define JBD_TOTAL_HEIGHT        504u   /* +24 rows    of alignment margin */
#define JBD_BITS_PER_PIXEL      4u
#define JBD_BYTES_PER_ROW       (JBD_ACTIVE_WIDTH * JBD_BITS_PER_PIXEL / 8u) /* 320 */
#define JBD_FRAME_BYTES         (JBD_BYTES_PER_ROW * JBD_ACTIVE_HEIGHT)      /* 153600 */

#define JBD_MANUFACTURER_ID     0xBDu   /* Table 4 */
#define JBD_DEVICE_ID_013VGA    0x4010u /* Table 4; jdb_panel_init compares this */

/* ============ buffer address word, section 7.3.15 note ================== */
/* Address = {5'b00000, ROW[8:0], COL[9:0]} */
#define JBD_ADDR_COL_POS        0u
#define JBD_ADDR_COL_MSK        0x0003FFu
#define JBD_ADDR_ROW_POS        10u
#define JBD_ADDR_ROW_MSK        0x07FC00u   /* <- the literal at 0x47720 */

static inline uint32_t jbd_buffer_addr(uint16_t row, uint16_t col)
{
    return (((uint32_t)row << JBD_ADDR_ROW_POS) & JBD_ADDR_ROW_MSK)
         |  ((uint32_t)col & JBD_ADDR_COL_MSK);
}
#define JBD_BUFFER_WRITE_DUMMY  0xFFu  /* Byte5 of the 02H header */
#define JBD_BUFFER_HEADER_BYTES 5u     /* 02H + A23:16 + A15:8 + A7:0 + dummy */
#define JBD_BUFFER_TRAIL_BYTES  1u     /* "Final 4 dummy clocks are needed"   */

/* ================= Status Register 1 (6.2) — 0x01 / 0x05 =============== */
#define JBD_ST1_DEMURA_EN_POS   7u
#define JBD_ST1_DEMURA_EN_MSK   0x80u
#define JBD_ST1_GAMMA_EN_POS    6u
#define JBD_ST1_GAMMA_EN_MSK    0x40u
#define JBD_ST1_RFFQ_POS        3u
#define JBD_ST1_RFFQ_MSK        0x38u
#define JBD_ST1_RESERVED_MSK    0x07u   /* must be written 0 */
#define JBD_ST1_RESET_VALUE     0x90u

/* RFFQ codes.  Hz depends on OSCS: value(9.6 MHz) / 2*value(19.2 MHz). */
#define JBD_RFFQ_30HZ           0u
#define JBD_RFFQ_60HZ           1u
#define JBD_RFFQ_90HZ           2u   /* <- what panel_init programs */
#define JBD_RFFQ_120HZ          3u
#define JBD_RFFQ_150HZ          4u
#define JBD_RFFQ_180HZ          5u
#define JBD_RFFQ_210HZ          6u
#define JBD_RFFQ_240HZ          7u

/* Max legal LUM per RFFQ code (6.2 note) — index with JBD_RFFQ_*. */
#define JBD_LUM_MAX_BY_RFFQ  { 21331u, 10664u, 7109u, 5331u, \
                                4264u,  3366u, 2907u, 2558u }

/* ================= Status Register 2 (6.2) — 0x31 / 0x35 =============== */
#define JBD_ST2_SPF_MSK         0x20u   /* r/o: panel is scanning            */
#define JBD_ST2_RFHF_MSK        0x10u   /* r/o: reload-to-pixel-latch active */
#define JBD_ST2_PORF_MSK        0x08u   /* power-on-reset flag, write 0      */
#define JBD_ST2_SYNC_S_MSK      0x04u   /* 1 = SYNC does NOT blank screen    */
#define JBD_ST2_OSCS_MSK        0x03u
#define JBD_ST2_OSC_INT_9M6     0u      /* <- what panel_init programs */
#define JBD_ST2_OSC_INT_19M2    1u
#define JBD_ST2_OSC_EXTERNAL    2u
#define JBD_ST2_RESET_VALUE     0x00u

/* ================= Luminance / Current / Offset (6.3-6.5) ============== */
#define JBD_LUM_RESET_VALUE     0x1BC5u        /* Lum_H 0x1B, Lum_L 0xC5 */
#define JBD_CUR_MSK             0x3Fu          /* CUR[5:0]               */
#define JBD_CUR_RESET_VALUE     0x00u
#define JBD_OFFSET_ROW_MSK      0x1Fu          /* ROW[4:0] */
#define JBD_OFFSET_COL_MSK      0x1Fu          /* COL[4:0] */
#define JBD_OFFSET_ROW_RESET    0x0Cu          /* = 24/2, geometric centre */
#define JBD_OFFSET_COL_RESET    0x0Au          /* = 20/2, geometric centre */
#define JBD_OFFSET_ROW_MAX      24u            /* 504 - 480 (4.1.2) */
#define JBD_OFFSET_COL_MAX      20u            /* 660 - 640 (4.1.2) */

/* ================= timing (7.3.6, 4.3.3) =============================== */
#define JBD_SYNC_RELOAD_US_9M6   830u   /* 0.83 ms  */
#define JBD_SYNC_RELOAD_US_19M2  420u   /* 0.42 ms  */
#define JBD_INTER_COMMAND_US       1u   /* Tint > 1 us, CSB high between cmds */
#define JBD_CMD_HOLD_US            1u   /* Tcmdh > 1 us after single commands */

#endif /* JBD013VGA_H */
```

Accessors the datasheet justifies (bit layouts are all from `[DS §6.x]`):

```c
static inline uint8_t jbd_st1(uint8_t rffq, bool gamma, bool demura)
{ return (uint8_t)((demura << 7) | (gamma << 6) | ((rffq & 7u) << 3)); }
/* panel_init writes jbd_st1(JBD_RFFQ_90HZ, false, false) == 0x10  */

static inline uint8_t jbd_st2(uint8_t oscs, bool sync_no_blank)
{ return (uint8_t)((sync_no_blank << 2) | (oscs & 3u)); }
/* panel_init writes jbd_st2(JBD_ST2_OSC_INT_9M6, true) == 0x04    */

/* 36H payload is big-endian: LUM15-8 then LUM7-0 (Table 5). */
static inline void jbd_lum_bytes(uint16_t lum, uint8_t out[2])
{ out[0] = (uint8_t)(lum >> 8); out[1] = (uint8_t)lum; }
```

---

## 5. Contradictions found

### 5.1 `net_pkt_write_be16` is a panel luminance write — **naming defect, high confidence**

Stated above (§1.2). The catalogue entry
(`recon/catalogs/function_names_app.json`, `0x0007d696`) is marked
`"human": true, "source": "committed durable map"`, i.e. a human confirmed a name
that the shipped bytes contradict. `[BIN 0x7d696]` puts `0x36` on the wire and
`[DS §7.3.9]` calls `36H` Luminance Register Write. There is no networking in
this function, and its only two callers are panel-brightness code.

### 5.2 The trailing dummy byte: the firmware disagrees with **itself**, and the emulator model with both

`[DS §7.3.15]`, note under the `02H` diagram: *“Final 4 dummy clocks are needed.”*

* `projector_transfer_pixel_chunk` @ `0x476b4` sends `5 + N + 1` bytes
  (`[BIN] add.w r2, r8, #6`, buffer starts 5 bytes before the payload) — it
  **does** clock the trailing byte. Datasheet-compliant.
* `reflash_fb_data_to_lcd` @ `0x47260` sends `5 + N` bytes
  (`[BIN 0x472bc] rsb.w r4, r4, #5 ; add.w r4, r4, r3, asr #1` → length
  `= 5 − x/2 + width/2`, then `mov r2, r4` into the transfer) — it **does not**.
  Curiously it *saves, zeroes and restores* the byte at `buf[len]`
  (`[BIN 0x47340] ldrb.w sl,[r5,r4] ; strb r3,[r5,r4]` with `r3 = 0`,
  restored at `0x47396`) — the exact preparation for a trailing zero byte that
  is then not transmitted. That looks like a length that was decremented and a
  cleanup that was not.
  **Consequence if the datasheet is right: the last pixel pair of every
  `reflash`-drawn row may not latch on real hardware.**
* `~/Projects/armemul/models/JBD_Display.cs` holds back the final byte of *every*
  `0x02` transaction unconditionally (`State.PixelData`, one-byte lookahead;
  `FinishTransmission` drops it as “the trailing dummy”). For the
  `transfer_pixel_chunk` path that is correct. For the `reflash` path there is no
  trailing dummy, so **the model silently discards one real pixel byte (2 pixels)
  from every reflashed row**, and the “9 pixel bytes” window shapes in
  `recon/emulator/reports/display_sensor_parity.md` §3.2 are therefore probably
  10 bytes on the wire.
  That those windows come from the `reflash` path and not the chunk path is
  forced, not assumed: `projector_transfer_pixel_chunk` has exactly **two**
  callers in the whole image — `projector_fill_framebuffer` (always `x=0`,
  always 61440/30720 B) and `projector_write_pixel_data` (which emits a `0x97`
  after *every* call). Neither can produce 21 consecutive `0x02` transactions at
  `x=32` closed by a single `0x97`. Only `reflash_fb_data_to_lcd(_ex)`'s
  row loop can, and `[TRACE]` measured exactly 21 rows, 265…285.
  *Not edited* (per instruction, and the file carries uncommitted `TraceFile`
  hooks). The fix, when someone takes it, is to make the drop conditional — e.g.
  hold back the last byte only if the payload length is one more than the
  window's natural width — or simply to journal both counts.

### 5.3 `jbd_panel_resume` never sends `ABH`

`[DS §4.4.2]` and `[DS §7.3.2]`: the device leaves Deep Power-Down on an external
`RSTN` **or** the `ABH` Release command; `[DS §7.3.5]` adds that in DPD *“all
commands are ignored except … ABH or Enable Reset (66H) and Reset (99H)”*.

`[BIN 0x47638]` `jbd_panel_resume` logs *“release from deep power down”* and then
calls `panel_init()`, whose first act is `66H`/`99H` `[BIN 0x7d74e]`. So the
firmware uses the **reset** escape hatch rather than `ABH`. That is legal by the
datasheet, but the log string is misleading and the name should carry a comment.
Not a defect — a documentation gap.

### 5.4 Datasheet-internal contradiction on the `C0H` payload order

See §2.1. Table 5 says `R4-R0` then `C4-C0`; the Figure 26 text extraction lists
`C4-C0` first. Resolved in favour of Table 5 by the shipped corner sweep
(`0x18 = 24` can only be a row offset, `0x14 = 20` only a column offset).

### 5.5 Datasheet-internal contradiction on Status Register 1 bit 7

`[DS §6.2]` names bit 7 `W0` — *“Write 0 at any reset release status”* — and then
documents it as demura enable with **1** as the default. The reset value `0x90`
has it set. The firmware writes `0x10`, i.e. **0**. Both readings cannot be right;
the firmware follows “write 0 after reset”.

### 5.6 The emulator's `9F` response omits the manufacturer byte

`[DS §7.3.1]` RDID returns `MF7-MF0` (= `0xBD`, Table 4) on byte 2, then
`ID15-ID8`, `ID7-ID0`. `JBD_Display.cs` emits only the two ID bytes after
`IdReadLatency` dummies (`IdValue = 0x4010`, `CommandId = 0x9F`) and never
`0xBD`. Parity-invisible — `[BIN 0x47724]` reads only `rx[2]`/`rx[3]` — but the
model is not datasheet-faithful here.

### 5.7 “640×200” is the canvas, not the panel — already corrected, recorded here for the record

`JBD_Display.cs` header comment still says *“the 640x200 framebuffer”* while the
code below it says `Height = 480` with an explicit correction note. The shipped
firmware settles it three independent ways:
* `[BIN 0x7d6ae]` `memset`s the host canvas with `0xFA00 = 64 000` bytes
  (`= 320 × 200`, i.e. the canvas is exactly 640×200) and then pushes
  `0xF000 + 0xF000 + 0x7800 = 153 600` bytes out of it in three bands at panel
  rows `0 / 0xC0 / 0x180` — 192 + 192 + 96 = **480 rows**. The same 64 000-byte
  source buffer is re-sent three times; the *panel* address space is three times
  the canvas;
* `[BIN 0x7d70a]` advances the row cursor by `0xC0 = 192` per `0xF000`-byte
  chunk ⇒ `61440 / 192 = 320` bytes per row ⇒ **640 px at 4 bpp**;
* `[DS §1]` 640×480, 16 grey levels (4 bit).

The **canvas** is 640×200: `[BIN 0x472ac]` clamps the row argument to `0xC8 = 200`
and `[BIN 0x472c0]` clamps the width to `0x280 = 640`, with a `0x140 = 320`-byte
stride. So the host keeps a 640×200 buffer and paints it into a 640×480 panel —
the visible content lives at panel rows 265…287 `[TRACE]`, i.e. **below** row 200.
The two numbers are both right and describe different things; the stale header
comment in the model should be updated when someone touches that file.

### 5.8 `panel_temp_calibration_init` is not a panel function at all

`recon/refactor/stage_09_call_cohesion/tree/.../display/panel_temp_calibration_init.c`
(`FUN_00062644` @ `0x62644`) sits inside the display module. It touches **no SPI
opcode and no projector symbol**. Its callees are `exp()`, the soft-float
helpers, `dev_write_reg3/dev_write_reg4`, `flash_page_index_lookup` and
`layout_select_region`; its body programs a table of eight thresholds at register
base `3`, offsets `0x10, 0x12 … 0x16`, each computed through
`exp(β·(1/T − 1/T0))` — the Beta equation for an **NTC thermistor**, i.e. a
battery-charger JEITA window, not a display.

The repo already knows this and the knowledge did not propagate:
`recon/symbolized/app/layout_select_region.c:29` says
*“-EINVAL made npm1300_charger_init (panel_temp_calibration_init, 0x62644)…”*.

`[DS §7.3.27]` the JBD panel *does* have a temperature sensor, read with `26H`.
**`26H` never appears in the shipped image** (see §6.6). So there is no panel
temperature path at all, and this function's name asserts one.

Proposed: rename to **`npm1300_charger_ntc_init`** and move it out of the
`display` module. Confidence high on “not a panel function”; medium on the exact
PMIC part, which this pass did not re-derive.

---

## 6. What I could not identify, and why

1. **The 66.62 ms period itself.** Established above only as *not* a panel
   property (§3.2). Its true source is a Zephyr timer inside `ui_navigation_task`;
   pinning it needs the task's disassembly and Zephyr tick arithmetic, which is
   outside a display-driver naming pass.
2. **Which of the two `reflash` transaction lengths the panel actually accepts.**
   §5.2 is a documented three-way disagreement, not a resolved one. Settling it
   needs either the raw byte-level SPI journal (transaction lengths, not the
   model's post-drop pixel counts) or hardware.
3. **`device_info + 0xED8`** — the per-device luminance calibration halfword
   (13 on the captured unit). It scales `LUM` by `0x6F = 111` per step. The
   datasheet gives no such constant; `111 × (cal+1)` staying under the
   `RFFQ=010` ceiling of 7109 is consistent but not proof of the formula's
   intent. Left unnamed beyond `g_lum_calibration_steps`.
4. **`0x86c1e`, `0x86c78`, `0x86384`** (memcpy / memset / `k_busy_wait`) are
   assumed from shape and call sites; they are libc/kernel, not panel, and were
   not re-proven here.
5. **`fb_blit_rows_wrap320` / `fb_blit_rows_halved` / `fb_blit_rows_copy`**
   (`0x7d4f8`, `0x7d5f2`, `0x7d53a`) are host-side canvas compositors — they
   touch no panel opcode, so the datasheet says nothing about them and they are
   out of scope for this pass.
6. **`0x52`/`0x53`/`0x54`/`0x62`/`0x63` (Quad-SPI paths), `0x26` temperature
   read, `0x81` OTP/chip-info, `0x13`–`0x16` self-test, `0x72` up-down mirror,
   `0x04` write-disable, `0xAB` release-DPD, `0x03` buffer read, `0x05`/`0x35`/
   `0x57`/`0x59` status reads** — documented in the header of §4 but **absent
   from the shipped image**. No firmware function maps to them.
   Notably `panel_temp_calibration_init.c` does **not** use the panel's own
   `26H` temperature sensor; it is a host-side thermal path.

---

## 7. Renames for the merged units

The `g1_display_NN.c` / `g1_display_ccNN.c` names are stage-09 cohesion-cluster
serial numbers. Below, each unit's members were read and the unit named for what
they collectively do. Members that carry a panel opcode are marked ★.

| unit | members | what the members actually are | proposed unit name |
|---|---|---|---|
| `g1_display_01.c` | `compute_lux_brightness_bucket`, `power_for_panel` | ALS lux → brightness-level quantiser + the panel power rail enable | **`display_power_and_als.c`** |
| `g1_display_02.c` | `panel_pwr_gpio_deassert`, `gpio_dt_spec_activate`, `brightness_level` | panel supply GPIO helpers + brightness-level accessor | **`display_power_gpio.c`** |
| `g1_display_05.c` | `trigger_screen_state_change`, `display_panel_is_secondary`, `clear_pending_message_flag`, `display_dev_reg_config`, `set_brightness_lum_base` | screen-state signalling + the BLE `0x36` **test-mode** luminance-base setter | **`display_state_and_test_cmds.c`** |
| `g1_display_06.c` | `set_display_brightness`, `set_panel_voltage`, `get_message_entry`, `get_message_pool_index`, `render_device_info_float_screen`, `display_idle_countdown_tick`, `pixelto4bithex` | brightness/voltage setters, message-pool accessors, the 4-bpp nibble packer | **`display_brightness_and_message_pool.c`** |
| `g1_display_09.c` ★ | `panel_write_xy_reg_cached`, `set_brightness_to_panel_reg_in_running`, `reflash_fb_data_to_lcd` | **JBD brightness register cache** (`36H`/`46H`) + the per-row `02H` blit loop terminated by one `97H` | **`jbd_brightness_and_blit.c`** |
| `g1_display_10.c` ★ | `panel_init`, `jbd_panel_suspend`, `jbd_panel_resume`, `projector_bus_lock/_unlock`, `projector_transfer_pixel_chunk` | the JBD init/DPD/resume lifecycle + the `02H` buffer-write transport | **`jbd_panel_lifecycle.c`** |
| `g1_display_12.c` | `display_reflash`, `display_close` | display-service entry points (message/event level) | **`display_service_entry.c`** |
| `g1_display_13.c` | `display_DelayClose`, `display_inputEvent`, `display_MasterSendClose`, `display_powerEvent` | display state-machine event handlers | **`display_event_handlers.c`** |
| `g1_display_cc01.c` ★ | `power_down_panel`, `display_fade_out_mask_bands`, `set_imu_pitch_reflash`, `panel_off`, `panel_on`, `set_brightness_to_panel_reg`, `jdb_panel_init`, **`net_pkt_write_be16` (= `36H` luminance)**, `delay_ms`, `projector_send_cmd_immediate`, `projector_spi_write_chunked`, `projector_send_command`, `projector_reflash_and_release`, `dev_write_reg4`, `uptime_ticks_get` | the whole JBD **SPI command layer** plus the panel power on/off path | **`jbd_panel_core.c`** — splitting the pure transport (`send_command`, `send_cmd_immediate`, `spi_write_chunked`, `delay_ms`) into **`jbd_spi_transport.c`** would be better still |
| `g1_display_cc02.c` ★ | `get_box_field_state`, `refresh_box_field_timer`, `is_box_field_timer_expired`, `update_box_field_debounce`, `process_box_event`, `panel_level_calc_cached`, `ui_state_mutex_unlock`, `read_nfc_adc_scaled`, `box_field_state_to_display_code`, `update_display_status`, `get_projector_controller`, `fb_blit_rows_wrap320`, `projector_send_cmd1`, `projector_fill_framebuffer`, `projector_fill_and_sync` | **genuinely two things**: the charging-case ("box") state machine, and the panel clear path (`02H`×3 + `97H`) | **split**: `case_dock_state.c` + **`jbd_screen_clear.c`** |
| `g1_display_cc03.c` ★ | `get_demo_image_source`, `set_display_page_index`, `advance_display_page_index`, `update_demo_image_display`, `ui_raster_height_task`, `display_mode_globals_configure`, **`spi_read_id`** (`9FH`), `demo_image_get_position`, `display_reflash_handler`, `stop_some_timer`, `setDelayExitValue`, `submit_display_reflash_work` | the demo-image / page-index UI driver, plus the one `9FH` ID probe | **`display_demo_and_reflash_dispatch.c`**, with `spi_read_id` moved to `jbd_panel_lifecycle.c` where its only caller `jdb_panel_init` lives |

Two structural observations that fall out of the datasheet reading:

* **`g1_display_09`, `_10`, `cc01`, `cc02`, `cc03` each hold a slice of the JBD
  command layer.** All sixteen opcodes the firmware ever emits
  (`01 02 06 31 36 46 66 71 73 97 99 9F A3 A9 B9 C0`) are spread across five
  units. A single `jbd013vga/` sub-module holding the transport + the command
  wrappers + `jbd013vga.h` from §4 would make the driver legible; everything
  else in these units is host-side UI.
* **`panel_temp_calibration_init.c` does not belong in this module at all** (§5.8).

### 7.1 Standalone files in `.../display/` — proposed renames

| current file | proposed file | reason |
|---|---|---|
| `projector_send_cmd_0x46.c` | `jbd_write_current_reg.c` | `46H` = Current Register Write `[DS §7.3.11]` |
| `projector_send_cmd_c0.c` | `jbd_set_display_center.c` | `C0H` = Display Center Register Write `[DS §7.3.13]` |
| `projector_reset_sequence.c` | `jbd_software_reset.c` | `66H`+`99H` `[DS §7.3.4]` |
| `projector_write_pixel_data.c` | `jbd_buffer_write_and_sync.c` | `02H`×k + `97H` `[DS §7.3.15, §7.3.6]` |
| `reflash_fb_data_to_lcd_ex.c` | `jbd_blit_rows_and_sync_offset.c` | per-row `02H` + one `97H` |
| `panel_temp_calibration_init.c` | `npm1300_charger_ntc_init.c` **and move out of `display/`** | §5.8 |
| `display_dispatch_thread.c`, `master_display_thread.c`, `slave_display_thread.c`, `wake_display_thread_on_reflash.c`, `display_thread_handler.c`, `display_close_screen.c`, `spawn_display_thread.c`, `spawn_flash_ops_and_brightness_threads.c`, `float_to_ascii_signed_2dp.c` | *(unchanged)* | host-side threading/formatting; they carry no panel opcode, so the datasheet has nothing to say about them |

Inside `projector_write_pixel_data.c` the existing local enum should be replaced
by the §4 names, and one of its members is currently misdescribed:

```c
/* current                                   proposed                          */
PROJECTOR_MAX_TRANSFER_BYTES = (0xf0u << 8)  /* 0xF000 = 61440 B = 192 rows.
                                                This is the SPIM/EasyDMA chunk
                                                ceiling, NOT a panel limit --
                                                the datasheet imposes none.    */
PROJECTOR_ROWS_PER_TRANSFER  = 0xc0          /* 192 = 61440 / JBD_BYTES_PER_ROW */
PROJECTOR_DISPLAY_UPDATE_COMMAND = 0x97      /* -> JBD_CMD_SYNC.  "display
                                                update" is wrong: 97H does not
                                                update anything, it reloads the
                                                buffer into the pixel latch
                                                [DS 7.3.6].                    */
```

---

## Correction (coordinator, 2026-07-29): the `human: true` flag is NOT verification

This report described `FUN_0007d696` as catalogued `net_pkt_write_be16` with
`human: true` in the committed durable map, and the commit message repeated that
as if the name had survived human review. **That is a misreading of the flag.**

`tools/build_function_names.py`:

```python
def is_human(name):
    return bool(name and not re.match(r"^(?:FUN_|sub_)0*[0-9a-fA-F]+$", name))
```

`human` means only **"this name is not a raw `FUN_xxxx` / `sub_xxxx` address
stub."** It records the *shape* of the string, not its provenance and not any
review. No human confirmed `net_pkt_write_be16`.

**Why this matters more than the single rename.** The bad name is not an
exception that slipped past a check — there is no check. Every non-`FUN_` name in
`function_names_app.json` carries the same zero verification weight, including
the ~25 other display names in this report's mapping table. The datasheet pass is
the **first external authority** ever applied to any of them, and the first name
it checked was wrong.

Consequences for how this report should be read:
- The confidence column reflects *this pass's* evidence, and is independent of
  whatever the prior name was. Do not treat an existing name's agreement with a
  proposal as corroboration — it is not a second source.
- Consumers of `human: true` elsewhere in the toolchain
  (`tools/apply_names.py:190`, `tools/build_app_address_taken_roots.py:259,265`)
  are selecting on name shape. That may still be the right predicate for their
  purpose, but it must not be read as a trust signal.
