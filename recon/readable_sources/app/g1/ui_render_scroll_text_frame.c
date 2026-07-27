#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x000442b4       => struct g1_layout_scroll_text_frame_idx_table__global_1019 [global_1019; G1-original]
 *   local_4c         => struct g1_layout_scroll_text_frame_ctx__stack_1018      [stack_1018; G1-original]
 * Raw function identity: 0x000440ec.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000440ec @ 0x000440ec
 * public-name: ui_render_scroll_text_frame
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   ui_render_scroll_text_frame              <= FUN_000440ec @ 0x000440ec
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd_ex                <= FUN_000473c8 @ 0x000473c8
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   fb_blit_rows_halved                      <= FUN_0007d5f2 @ 0x0007d5f2
 * address symbols (name @ address):
 *   rodata_883ec                             @ 0x000883ec
 *   rodata_88410                             @ 0x00088410
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Full reconstruction of FUN_000440ec @ 0x440ec, exact extent 450 bytes.
 * Call arities are derived by target so optional calls cannot shift ordinal
 * metadata onto unrelated callees. */
#include <stdint.h>

extern int device_info_text_height_get_clamped(void);
extern int atomic_get_3_0(void);
extern void gui_canvas_flags_clear_bit1(void);
extern void gui_canvas_flags_set_bit1(void);
extern uintptr_t get_device_info(void);
extern void clean_fb_data(uintptr_t, int, int, int, int, int);
extern unsigned gui_utf_draw(unsigned, uintptr_t, unsigned, int, int, int, int,
                            unsigned, unsigned, int, void *, int);
extern void reflash_fb_data_to_lcd_ex(uintptr_t, uintptr_t, int, int, int, int, uint32_t);
extern void fb_blit_rows_halved(int, int, int, int, int, int, int);

static uintptr_t display(void) { return *(volatile uintptr_t *)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/; }

void ui_render_scroll_text_frame(int unused, uintptr_t text, int unused2, int left, int top,
                  int right, int bottom, unsigned rows, unsigned mask)
{
    (void)unused; (void)unused2;
    uint32_t glyphs[9];
    if (device_info_text_height_get_clamped() <= 0x20) {
        int shifted_top = top + 0x1b;
        int shifted_bottom = bottom + 0x1b;
        if ((atomic_get_3_0() & 2) != 0)
            clean_fb_data(display(), 0, left, shifted_top, right, shifted_bottom);
        gui_canvas_flags_clear_bit1();
        gui_utf_draw(0, text, 0, left, shifted_top, right, shifted_bottom,
                     rows, mask, 0, 0, 0);
        gui_canvas_flags_set_bit1();
        for (unsigned i = 0; i < 9; ++i) glyphs[i] = ((const uint32_t *)((unsigned long)&rodata_883ec) /*=0x883ec*/)[i];
        for (unsigned i = 0; i < 9; ++i) {
            uintptr_t s = get_device_info(); uintptr_t d = get_device_info();
            reflash_fb_data_to_lcd_ex(*(uint32_t *)(s + 0xeb4), *(uint32_t *)(d + 0xeb8),
                         left, top, right, bottom, glyphs[i]);
        }
        fb_blit_rows_halved(display(), left, top, left, shifted_top, 0x1b, right - left);
        if ((atomic_get_3_0() & 2) != 0)
            clean_fb_data(display(), 0, left, bottom, right, shifted_bottom);
        return;
    }

    if (device_info_text_height_get_clamped() > 0x20) {
        fb_blit_rows_halved(display(), left, top - 0x1b, left, top, 0x1b, right - left);
        if ((atomic_get_3_0() & 2) != 0)
            clean_fb_data(display(), 0, left, top, right, bottom);
        gui_canvas_flags_clear_bit1();
        gui_utf_draw(0, text, 0, left, top, right, bottom, rows, mask, 0, 0, 0);
        gui_canvas_flags_set_bit1();
        for (unsigned i = 0; i < 9; ++i) glyphs[i] = ((const uint32_t *)((unsigned long)&rodata_88410) /*=0x88410*/)[i];
        for (unsigned i = 0; i < 9; ++i) {
            uintptr_t s = get_device_info(); uintptr_t d = get_device_info();
            reflash_fb_data_to_lcd_ex(*(uint32_t *)(s + 0xeb4), *(uint32_t *)(d + 0xeb8),
                         left, top, right, bottom, glyphs[i]);
        }
        if ((atomic_get_3_0() & 2) != 0)
            clean_fb_data(display(), 0, left, top, right, top);
    }
}
