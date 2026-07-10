/*
 * gui_text: bitmap-font + bitmap-graphics rendering into the projector canvas.
 *
 * The glyph/graphics layer that draws into the RAM framebuffer that `display`
 * then blits to the monochrome projector panel. It decodes UTF-8
 * (utf8_to_unicode), looks up Latin and CJK glyphs from a packed font/resource
 * blob (resource_manger_get, find_chinese_bitmap_by_unicode), and rasterises
 * them with a family of gui_utf_draw_* renderers (word-wrap, truncate,
 * middle/right align, dark/light split). It also has a bitmap blitter family
 * (gui_bmp_bitmap_draw*, gui_bitmap_draw, 1-bit and 4-bit) for icons/images, a
 * clock renderer, a vertical progress bar, and canvas area-clear helpers. It
 * sits above `display` and is driven by the app UI screen tasks
 * (ui_even_ai_task, draw_message, and the per-app screens dispatched through
 * the UI command table).
 *
 * PUBLIC API vs INTERNAL
 * ----------------------
 * The reference call-graph reports only the functions below the "public API"
 * banner as being called from *other* modules. Everything under "internal" is
 * either (a) reached only from within gui_text, or (b) a module-external entry
 * point (a thread main or a UI-dispatch-table target) that is invoked
 * indirectly rather than through a direct call — those keep external linkage
 * but are NOT a stable callable API. Shared C-runtime helpers that merely got
 * topic-clustered here are tagged [runtime].
 *
 * Type notes: several signatures keep Ghidra decompiler aliases (undefined4,
 * codeptr, u32/i32); see the typedef block below.
 */
#ifndef G1_GUI_TEXT_H
#define G1_GUI_TEXT_H

#include <stdint.h>

/* Ghidra-decompiler type aliases (signatures are as-reconstructed) */
typedef uint8_t  u8; typedef uint8_t  undefined1; typedef uint8_t byte;
typedef uint16_t ushort;
typedef uint32_t u32; typedef int32_t i32; typedef uint32_t uint; typedef uint32_t undefined4;
typedef void    *codeptr;   /* per-glyph draw callback */
typedef void    *codef;
typedef void    *fnptr_t;

/* ===========================================================================
 * PUBLIC API  — functions the reference graph shows called from other modules.
 * These 16 are the real cross-module surface of gui_text.
 * ===========================================================================*/

/* --- glyph/text drawing (called by many app-screen modules) --------------- */
/* gui_utf_draw @0x43e90 — plain left-aligned UTF-8 run into the canvas.       */
undefined4 gui_utf_draw(undefined4 canvas, unsigned s, int x, int y, int w, int h, int a,
                        uint b, uint c, int d, codef cb, int e);
/* gui_clock_draw @0x442bc — render HH:MM clock glyphs (dashboard/idle).       */
undefined4 gui_clock_draw(undefined4 canvas, int a, undefined4 b, undefined4 c,
                          undefined4 d, undefined4 e, char f);

/* --- bitmap / icon blitting ------------------------------------------------ */
/* gui_bmp_bitmap_draw @0x43484 — blit a packed 1-bit bitmap at (x,y,w,h).     */
int      gui_bmp_bitmap_draw(unsigned int canvas, int x, int y, int w, int h, int data);
/* gui_bmp_dynamic_bitmap_draw @0x4334c — blit a streamed/animated frame.      */
unsigned gui_bmp_dynamic_bitmap_draw(unsigned canvas, int x, int y, int w, int h, int data, unsigned char f);

/* --- canvas maintenance ---------------------------------------------------- */
/* clean_fb_data @0x471cc — clear a rectangle of a framebuffer/canvas.         */
int      clean_fb_data(int canvas, void *buf, int a, int b, int c, int d);

/* --- glyph lookup / decode (font subsystem entry points) ------------------- */
/* find_chinese_bitmap_by_unicode @0x4792c — locate a CJK glyph by codepoint.  */
unsigned int find_chinese_bitmap_by_unicode(unsigned int codepoint, short a, short b);
/* FUN_000478d8 @0x478d8 — decode a UTF-8 string into a 16-bit glyph-index      */
/*   buffer (scratch @0x2000f704, up to 0x400 entries); *out_count set.        */
unsigned int gui_utf8_to_glyphbuf(unsigned int utf8, unsigned short *out_count);
/* FUN_00047a4c @0x47a4c — fetch/expand one ASCII (or 4-bpp) glyph bitmap into  */
/*   scratch @0x2001d142; returns the scratch pointer.                         */
int      gui_ascii_glyph_fetch(int bpp, int stride, int a, int b);
/* FUN_00023ee0 @0x23ee0 — read the global UI mode/sub-mode flag (0x20018463). */
unsigned char gui_get_ui_mode_flag(void);

/* --- panel canvas cursor / low-level dot blit ------------------------------ */
/* FUN_0007d3ee @0x7d3ee — panel column cursor: clamp & return canvas base+col.*/
int      gui_panel_col_cursor(void);
/* FUN_0007d446 @0x7d446 — panel row cursor: clamp & return current row.        */
uint16_t gui_panel_row_cursor(void);
/* FUN_0007d53a @0x7d53a — blit a glyph's set-dot column offsets into rows.     */
int      gui_glyph_column_blit(int rows, int y, int step, int n, int x, int col);

/* --- shared C-runtime helpers [runtime] (topic-clustered, not gui-specific) */
/* FUN_00086c1e @0x86c1e — overlap-guarded memmove/memcpy.                      */
void     rt_guarded_memmove(unsigned int dst, unsigned int src, unsigned int n, unsigned int m);
/* FUN_00086f00 @0x86f00 — buffered stream write + flush / region accounting.  */
void     rt_stream_write_flush(int fp, int a, int len, int buf);
/* FUN_00077c30 @0x77c30 — low-level stream/file write via fd handle.           */
void     rt_stream_write(int a, int b, int c, int d);
/* FUN_00051164 @0x51164 — SVC #2: (re)configure MPU memory regions.           */
void     rt_config_mem_regions(void);

/* ===========================================================================
 * INTERNAL — reached only within gui_text, or module-external entry points
 * (thread mains / UI-dispatch targets). Declared for the wiring/link step;
 * NOT part of the public API. Bodies in recon/named/ and recon/verified/src/.
 * ===========================================================================*/

/* text-renderer variants — invoked internally by the screen tasks and by
 * draw_message; not called cross-module directly. */
undefined4 gui_utf_draw_dark_light_split(undefined4 canvas, undefined4 s, int x, int y, int w, int h,
                        int a, uint b, ushort c, int d, codeptr cb, int e); /* @0x44544 (entry) */
u32        gui_utf_draw_truncate(u32 canvas, u32 s, i32 x, i32 y, i32 w, i32 h, i32 a,
                        u32 b, u32 c, i32 d, fnptr_t cb, i32 e);             /* @0x44818 */
undefined4 gui_utf_draw_middle(undefined4 canvas, undefined4 s, int x, int y, int w, int h,
                        int a, uint b, uint c, int d, codeptr cb, int e);   /* @0x44bd8 */
u32        gui_utf_draw_align_right(u32 canvas, u32 s, i32 x, u32 y, i32 w, i32 h, i32 a,
                        u32 b, u32 c, i32 d, fnptr_t cb, i32 e);            /* @0x44ec4 */
u32        gui_utf_Wordwrap_draw(u32 canvas, u32 s, i32 x, i32 y, i32 w, i32 h, i32 a,
                        u32 b, u32 c, i32 d, fnptr_t cb, i32 e);            /* @0x451e0 */

/* bitmap blitter variants — UI-dispatch-table entry points (indirect). */
unsigned int gui_bmp_bitmap_draw_ex(unsigned int canvas, int x, int y, int data, unsigned char f); /* @0x435d4 (entry) */
unsigned   gui_bitmap_draw(uint canvas, int x, int y, int w, int h, byte f);        /* @0x43a68 (entry) */
int        gui_bitmps_merge_draw(unsigned int canvas, int x, int y, int w, int h, int d,
                        unsigned char e, unsigned char f);                          /* @0x43bd8 (entry) */
unsigned int gui_4bit_bitmap_override(unsigned int canvas, unsigned int a, unsigned int b); /* @0x43d78 (entry) */
uint32_t   gui_verticalLine_process_bar(uint canvas, int x, uint y, int h, uint32_t v, uint8_t f); /* @0x4396c */
uint32_t   gui_area_clear(uint32_t canvas, uint32_t x, uint32_t y, uint32_t wh);    /* @0x43228 (entry) */

/* resource / decode helpers — internal to the font subsystem. */
uint       utf8_to_unicode(byte *utf8, int *consumed);                              /* @0x477a0 */
int        resource_manger_get(uint kind, uint id, uint *out_w, uint *out_h, int *out_len, undefined1 *out_ptr); /* @0x4588c */

/* module-external entry points (thread main / UI-dispatch / notification). */
undefined4 ui_even_ai_task(int a, undefined4 b, int c); /* @0x3bfe0 — Even-AI streaming-text screen thread */
void       draw_message(undefined4 arg, undefined4 *msg); /* @0x35afc — notification message screen (entry) */

#endif /* G1_GUI_TEXT_H */
