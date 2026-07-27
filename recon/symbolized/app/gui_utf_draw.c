#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00043e90 @ 0x00043e90
 * public-name: gui_utf_draw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   count_chars_in_default_font_table        <= FUN_00043e58 @ 0x00043e58
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   resource_manger_get                      <= FUN_0004588c @ 0x0004588c
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   utf8_string_to_utf16                     <= FUN_000478d8 @ 0x000478d8
 *   fb_blit_rows_copy                        <= FUN_0007d53a @ 0x0007d53a
 *   index_in_range32_mask                    <= FUN_0007d860 @ 0x0007d860
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 * address symbols (name @ address):
 *   rodata_aaa58                             @ 0x000aaa58
 *   rodata_aaa7f                             @ 0x000aaa7f   [INLINED -- G6 literal batch]
 *   rodata_aadac                             @ 0x000aadac   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_gui_dark_light_dither_mask             @ 0x200034f6
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Full reconstruction of FUN_00043e90 @ 0x43e90, exact extent 574 bytes.
 * CFG_VERIFY_CALL_ARITIES=2,2,4 */
#include <stdint.h>
#include "../../headers/g1_log.h"

typedef unsigned (*render_callback_t)(unsigned, uintptr_t, int, int, int);
extern void* utf8_string_to_utf16(unsigned int, unsigned short*);
extern int atomic_get_3_0(void);
extern unsigned int index_in_range32_mask(unsigned int);
extern long resource_manger_get(unsigned long, unsigned long, long*, long*, unsigned long*, unsigned long);
extern void safe_memcpy_checked(void *dst, uintptr_t src, int bytes, int limit);
extern int count_chars_in_default_font_table(unsigned int, unsigned int);
extern int fb_blit_rows_copy(int, int, int, int, int, int);
extern int get_device_info(void);
extern void clean_fb_data(uintptr_t, int, int, int, int, int);
extern void reflash_fb_data_to_lcd(uintptr_t, uintptr_t, int, int, int, int);

unsigned gui_utf_draw(unsigned unused, uintptr_t text, int font,
                      int left, int top, int right, int bottom,
                      unsigned max_lines, unsigned mask_before,
                      int callback_mode, render_callback_t callback,
                      int suppress_default)
{
    (void)unused;
    uint16_t count = 0;
    uint16_t *characters = utf8_string_to_utf16(text, &count);
    int glyph_width = 0, glyph_height = 0;
    uintptr_t glyph_bitmap = 0;
    uint8_t pixels[680];

    if (callback_mode != 0) {
        if (callback != 0) goto invoke_callback;
        return 0;
    }
    if (callback != 0) {
invoke_callback:
        if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
            if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                log_message(((unsigned long)"%s(): exex process effect callback function\n") /*=0xaaa7f*/, ((unsigned long)"gui_utf_draw") /*=0xaadac*/);
            else
                debug_print(((unsigned long)"%s(): exex process effect callback function\n") /*=0xaaa7f*/, ((unsigned long)"gui_utf_draw") /*=0xaadac*/);
        }
        return callback(0, text, font, left, top);
    }
    if (suppress_default != 0) return 0;

    if ((atomic_get_3_0() & 2) != 0)
        clean_fb_data(*(volatile uintptr_t *)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/, 0,
                     left, top, right, bottom);

    unsigned line = 0, y_offset = 0, line_x = 0, x_advance = 0;
    for (unsigned index = 0; index < count; ++index, ++characters) {
        uint16_t ch = characters[0];
        int classification = index_in_range32_mask(ch);
        if (classification == 0) {
            int rc = resource_manger_get(font, ch, &glyph_width, &glyph_height,
                                  &glyph_bitmap, 0);
            if (rc < 0) {
                if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
                    if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                        log_message(((unsigned long)&rodata_aaa58) /*=0xaaa58*/, ((unsigned long)"gui_utf_draw") /*=0xaadac*/, ch);
                    else
                        debug_print(((unsigned long)&rodata_aaa58) /*=0xaaa58*/, ((unsigned long)"gui_utf_draw") /*=0xaadac*/, ch);
                }
                continue;
            }

            int half_width = (glyph_width + (glyph_width < 0)) / 2;
            int bytes = glyph_height * half_width;
            safe_memcpy_checked(pixels, glyph_bitmap, bytes, 0x2a4);
            if (index < mask_before) {
                for (int i = 0; i < bytes; ++i)
                    pixels[i] &= *(volatile uint8_t *)((unsigned long)&g_gui_dark_light_dither_mask) /*=0x200034f6*/;
            }

            int spacing = count_chars_in_default_font_table(characters[0], characters[1]);
            unsigned candidate = x_advance + (unsigned)glyph_width + (unsigned)spacing;
            if ((unsigned)(right - left) < candidate) {
                y_offset += (unsigned)glyph_height;
                if (font == 0) ++y_offset;
                if (++line >= max_lines || (unsigned)(bottom - top) <= y_offset)
                    break;
                fb_blit_rows_copy(*(volatile uintptr_t *)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/, pixels,
                             half_width, glyph_height, left, top + (int)y_offset);
                x_advance = (unsigned)glyph_width +
                            (unsigned)count_chars_in_default_font_table(characters[0], characters[1]);
                line_x = x_advance;
            } else {
                fb_blit_rows_copy(*(volatile uintptr_t *)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/, pixels,
                             half_width, glyph_height, left + (int)line_x,
                             top + (int)y_offset);
                line_x += (unsigned)glyph_width +
                          (unsigned)count_chars_in_default_font_table(characters[0], characters[1]);
                x_advance = line_x;
            }
        } else if (classification == -1 && (ch == '\r' || ch == '\n')) {
            if (glyph_height == 0)
                y_offset += (font == 0) ? 0x1b : 0x1a;
            else {
                y_offset += (unsigned)glyph_height;
                if (font == 0) ++y_offset;
            }
            if (++line >= max_lines || (unsigned)(bottom - top) <= y_offset)
                break;
            line_x = x_advance = 0;
        }
    }

    if ((atomic_get_3_0() & 2) != 0) {
        uintptr_t state = get_device_info();
        uintptr_t display = *(uint32_t *)(state + 0xeb4);
        state = get_device_info();
        reflash_fb_data_to_lcd(display, *(uint32_t *)(state + 0xeb8),
                     left, top, right, bottom);
    }
    return 0;
}
