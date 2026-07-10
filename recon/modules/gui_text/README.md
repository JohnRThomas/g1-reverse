# gui_text — bitmap font & graphics rendering

## Responsibility
The glyph and bitmap rendering layer of the G1 app core. It decodes UTF-8 text,
looks up glyph bitmaps (Latin + CJK) from the packed font/resource blob, and
rasterises them into the RAM canvas with word-wrap, truncation and alignment.
It also blits icon/image bitmaps (1-bit and 4-bit) and draws composite widgets
(clock, vertical progress bar). Everything it produces lands in the framebuffer
that `display` blits to the monochrome projector panel — this module writes
pixels, it does not own or flush the panel.

## Public API (cross-module surface)
The reference call-graph shows exactly these 16 functions called from other
modules. Four are shared C-runtime helpers that happen to be topic-clustered
here (`[runtime]`); the rest are the genuine text/graphics surface.

- `gui_utf_draw` (0x43e90) — plain left-aligned UTF-8 run into the canvas.
- `gui_clock_draw` (0x442bc) — render the HH:MM clock (dashboard/idle).
- `gui_bmp_bitmap_draw` (0x43484) — blit a packed 1-bit bitmap at (x,y,w,h).
- `gui_bmp_dynamic_bitmap_draw` (0x4334c) — blit a streamed/animated frame.
- `clean_fb_data` (0x471cc) — clear a rectangle of a framebuffer/canvas.
- `find_chinese_bitmap_by_unicode` (0x4792c) — locate a CJK glyph by codepoint.
- `gui_utf8_to_glyphbuf` (FUN_000478d8, 0x478d8) — decode a UTF-8 string into a
  16-bit glyph-index buffer (scratch @0x2000f704, ≤0x400 entries); writes count.
- `gui_ascii_glyph_fetch` (FUN_00047a4c, 0x47a4c) — fetch/expand one ASCII (or
  4-bpp) glyph bitmap into scratch @0x2001d142; returns that pointer.
- `gui_get_ui_mode_flag` (FUN_00023ee0, 0x23ee0) — read the global UI mode byte
  at 0x20018463 (renderers branch layout on it).
- `gui_panel_col_cursor` (FUN_0007d3ee, 0x7d3ee) — panel column cursor: clamp to
  ≤0x40, return canvas base + column.
- `gui_panel_row_cursor` (FUN_0007d446, 0x7d446) — panel row cursor: clamp, wrap.
- `gui_glyph_column_blit` (FUN_0007d53a, 0x7d53a) — write one glyph's set-dot
  column offsets into a run of canvas rows.
- `rt_guarded_memmove` (FUN_00086c1e, 0x86c1e) — overlap-guarded memmove `[runtime]`.
- `rt_stream_write_flush` (FUN_00086f00, 0x86f00) — buffered write + flush `[runtime]`.
- `rt_stream_write` (FUN_00077c30, 0x77c30) — low-level fd write `[runtime]`.
- `rt_config_mem_regions` (FUN_00051164, 0x51164) — SVC#2 MPU region config `[runtime]`.

## Text rendering pipeline
```
UTF-8 bytes ─> utf8_to_unicode (0x477a0) ─> codepoint
                    │
                    ├─ ASCII/Latin ─> gui_ascii_glyph_fetch (0x47a4c) ─┐
                    └─ CJK: find_chinese_bitmap_by_unicode (0x4792c) ──┤
                                                                        ▼
resource_manger_get (0x4588c) ─> glyph bitmap ─> gui_utf_draw_* ─> canvas
                                                        │
                              gui_glyph_column_blit (0x7d53a) writes the dots
```
The `gui_utf_draw_*` family shares one signature (canvas, string, x, y, w, h,
color/flags, per-glyph callback) and differs only in layout policy:
- `gui_utf_draw` (0x43e90) — plain left-aligned run.
- `gui_utf_Wordwrap_draw` (0x451e0) — multi-line word wrap into a width box.
- `gui_utf_draw_truncate` (0x44818) — single line, clip/ellipsis on overflow.
- `gui_utf_draw_middle` (0x44bd8) — horizontally centred.
- `gui_utf_draw_align_right` (0x44ec4) — right-aligned.
- `gui_utf_draw_dark_light_split` (0x44544) — split a line into highlighted vs
  dim segments (the Even-AI "already spoken vs upcoming" text style); uses the
  glyph-count classifier FUN_00043e58 (0x43e58) to decide the split point.

## Font / resource subsystem
- `resource_manger_get` (0x4588c) dispatches to four per-font lookup helpers,
  one per font table, each keyed by codepoint and returning the glyph's byte
  offset + width:
  - FUN_00045764 (0x45764) — font table @0x98fe8 (cnt 0x8ac34), stride 0x27.
  - FUN_000457b0 (0x457b0) — font table @0x98fbc (cnt 0x8ac30), stride 0x20.
  - FUN_000457f4 (0x457f4) — font table @0x98e3c (cnt 0x8ac2c).
  - FUN_00045840 (0x45840) — font table @0x9890c (cnt 0x8ac28).
- `utf8_to_unicode` (0x477a0) decodes one sequence; `FUN_00047844` (0x47844)
  runs it over a whole string to build the glyph-index array;
  `FUN_000478d8` (gui_utf8_to_glyphbuf) is the public wrapper that zeroes the
  0x800-byte scratch and fills it.
- `FUN_0004790c` (0x4790c) expands a glyph's per-byte 4-word entries from table
  @0xd753a (used by both the CJK path and gui_ascii_glyph_fetch).

## Key internal helpers (deduced from callers/callees/data)
- `FUN_000357dc` (0x357dc) — layout worker for `draw_message`: composes the
  notification block (calls gui_utf_draw_align_right, clean_fb_data, cursor
  helpers). Sole caller is draw_message.
- `FUN_0003be18` (0x3be18) — `ui_even_ai_task`'s status-icon painter (bmp draws);
  sole caller is ui_even_ai_task.
- `FUN_0003cb58` (0x3cb58) — a status/connection screen renderer (bmp + utf draw).
- `FUN_0003f2a8` (0x3f2a8) — navigation-direction text screen (string 0xaa091
  "navigation direction parampter error"); calls gui_utf_draw.
- `FUN_0003f380` (0x3f380) — disconnection-status text screen (strings 0xaa056/
  0xaa070 "…shuts down due to disconnection"); calls gui_utf_draw.
- `FUN_00034390` (0x34390) — getter for g_message_pool_index byte (0x2001a22a).
- `FUN_00043324` (0x43324) — clear a 0x28×0x28 (40×40) icon area via clean_fb_data.
- `FUN_00043e58` (0x43e58) — glyph classifier: counts how many of two codepoints
  are in the special table @0x9890c (returns 0..2) for the dark/light split.
- `FUN_0007d586` (0x7d586) — rectangular glyph blit (OR bitmap bytes into rows),
  used by gui_4bit_bitmap_override.
- `FUN_0007d860` (0x7d860) — codepoint range check (returns 0 iff ≥0x20).
- `FUN_0007d84c` (0x7d84c) — stub returning 0.
- `[runtime]` stream/file plumbing: `FUN_0007797c` (0x7797c), `FUN_00077c78`
  (0x77c78), `FUN_00079528` (0x79528) — fd/handle I/O behind the rt_* writers.

## Globals / structs owned
- The packed font/resource blob in flash (font tables @0x98e3c/0x98fbc/0x98fe8/
  0x9890c, glyph data around 0xe0000–0xe6000) accessed via `resource_manger_get`;
  the flash loader lives in `flash_store`.
- Scratch buffers this module owns in RAM: the glyph-index decode buffer
  @0x2000f704 (0x800 bytes) and the single-glyph bitmap scratch @0x2001d142.
- Canvas/framebuffer memory is owned by `display` (device_info + projector
  controller); gui_text writes into it, it does not allocate the panel.

## Entry points
- **Thread:** `ui_even_ai_task` (0x3bfe0) — the Even-AI streaming-text screen.
  Consumes text chunks arriving over BLE and renders them with the wrap /
  dark-light renderers. Guards a shared ~400-byte text buffer with an external
  mutex (see wiring.md).
- **UI-dispatch / notification entry points** (invoked indirectly from the UI
  command table in another module, so they show no direct in-module caller):
  `draw_message` (0x35afc), `gui_area_clear` (0x43228), `gui_bmp_bitmap_draw_ex`
  (0x435d4), `gui_bitmap_draw` (0x43a68), `gui_bitmps_merge_draw` (0x43bd8),
  `gui_4bit_bitmap_override` (0x43d78), `gui_clock_draw` (0x442bc),
  `gui_utf_draw_dark_light_split` (0x44544), `find_chinese_bitmap_by_unicode`
  (0x4792c), `FUN_0003cb58`, `FUN_0003f2a8`, `FUN_0003f380`.
- After drawing, callers ask `display` to reflash the panel (gui_area_clear
  itself calls reflash_fb_data_to_lcd).

## Notes
This module DEFINES no RTOS objects of its own — it is a pure rendering library
driven by other modules' threads. See wiring.md for the one external RTOS object
it depends on.
