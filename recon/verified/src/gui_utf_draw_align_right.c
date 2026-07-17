/* Reconstructed gui_utf_draw_align_right @ 0x44ec4 (raw FUN_00044ec4).
 * Reviewed executable extent: 0x30a bytes through the callback/logger tail;
 * literals follow at 0x451d0 and gui_utf_Wordwrap_draw starts at 0x451e0. */
#include <stdint.h>

typedef uint32_t (*text_draw_callback_t)(uint32_t canvas, uint32_t utf8_text,
                                        int32_t font, uint32_t left,
                                        int32_t top);

extern uint32_t get_device_info(void); /* FUN_000167a8 */
extern void debug_print(void); /* FUN_00019c70 */
extern uint32_t get_display_atomic_state(void); /* FUN_000431a8 */
extern uint32_t get_glyph_pair_spacing(uint32_t, uint32_t); /* FUN_00043e58 */
extern int32_t resource_manger_get(uint32_t font, uint32_t codepoint,
                                   int32_t *width, int32_t *height,
                                   uint32_t *bitmap, uint32_t flags);
    /* FUN_0004588c */
extern void clean_fb_data(uint32_t framebuffer, uint32_t fill,
                          uint32_t left, int32_t top,
                          int32_t right, int32_t bottom); /* FUN_000471cc */
extern void reflash_fb_data_to_lcd(uint32_t front, uint32_t back,
                                   uint32_t left, int32_t top,
                                   int32_t right, int32_t bottom);
    /* FUN_00047260 */
extern uint16_t *utf8_string_to_utf16(uint32_t utf8_text,
                                      uint16_t *count); /* FUN_000478d8 */
extern void fb_blit_rows_copy(uint32_t framebuffer, void *pixels,
                              uint32_t width_bytes, uint32_t height,
                              uint32_t x, uint32_t y); /* FUN_0007d53a */
extern int32_t classify_text_character(uint32_t); /* FUN_0007d860 */
extern void checked_bitmap_copy(void *, uint32_t, uint32_t, uint32_t); /* FUN_00086c1e */
extern void log_message(uint32_t format, uint32_t function,
                        uint32_t value, uint32_t unused); /* FUN_0007dda4 */

static volatile uint32_t *const active_canvas =
    (volatile uint32_t *)0x2000a034UL; /* g_gui_active_canvas */
static volatile int32_t *const log_level =
    (volatile int32_t *)0x2000230cUL; /* g_log_level */
static volatile int32_t *const use_alternate_log_sink =
    (volatile int32_t *)0x20007554UL; /* g_log_use_alt_sink */
static volatile uint8_t *const glyph_dither_mask =
    (volatile uint8_t *)0x200034f6UL; /* g_gui_dark_light_dither_mask */

uint32_t gui_utf_draw_align_right(uint32_t canvas, uint32_t utf8_text,
                                  int32_t font, uint32_t left, int32_t top,
                                  int32_t right, int32_t bottom,
                                  uint32_t maximum_lines,
                                  uint32_t masked_glyph_count,
                                  int32_t callback_mode,
                                  text_draw_callback_t callback,
                                  int32_t skip_builtin_rendering)
{
    uint16_t utf16_count = 0;
    uint32_t glyph_bitmap = 0;
    int32_t glyph_width = 0;
    int32_t glyph_height = 0;
    uint8_t glyph_pixels[680];
    uint16_t *cursor = utf8_string_to_utf16(utf8_text, &utf16_count);
    uint32_t text_index;
    uint32_t x_offset = 0;
    uint32_t line_width = 0;
    uint32_t aligned_x = left;
    uint32_t vertical_offset = 0;
    uint32_t line_count = 0;
    int measure_line = 1;

    (void)canvas;

    if (callback_mode == 0) {
        if (callback != 0) {
            goto invoke_callback;
        }
        if (skip_builtin_rendering != 0) {
            return 0;
        }

        if ((int32_t)(get_display_atomic_state() << 30) < 0) {
            clean_fb_data(*active_canvas, 0, left, top, right, bottom);
        }

        for (text_index = 0; (int32_t)text_index < (int32_t)utf16_count;
             text_index++) {
            if (measure_line) {
                uint32_t measured_width = 0;
                uint32_t scan_index = text_index;
                uint16_t *scan = cursor;

                while ((int32_t)scan_index < (int32_t)utf16_count &&
                       *scan != '\r' && *scan != '\n') {
                    uint32_t codepoint = *scan;
                    if (classify_text_character(codepoint) == 0) {
                        int32_t status = resource_manger_get(
                            font, codepoint, &glyph_width, &glyph_height,
                            &glyph_bitmap, 0);
                        if (status < 0) {
                            if (*log_level > 1) {
                                if (*use_alternate_log_sink == 0) {
                                    log_message(0x000aaa58UL, 0x000aad4bUL,
                                                codepoint, 0);
                                } else {
                                    debug_print();
                                }
                            }
                        } else {
                            measured_width += (uint32_t)glyph_width;
                            measured_width =
                                ((measured_width & 0xffffU) +
                                 get_glyph_pair_spacing(scan[0], scan[1])) &
                                0xffffU;
                        }
                    }
                    scan_index++;
                    scan++;
                }

                aligned_x = left;
                if (measured_width <= (uint32_t)(right - (int32_t)left)) {
                    aligned_x = (uint32_t)(right - (int32_t)measured_width);
                }
                aligned_x &= ~1U;
            }

            {
                uint16_t codepoint = *cursor++;
                int32_t character_class = classify_text_character(codepoint);

                if (character_class == 0) {
                    int32_t status = resource_manger_get(
                        font, codepoint, &glyph_width, &glyph_height,
                        &glyph_bitmap, 0);
                    int32_t current_height = glyph_height;
                    int32_t current_width = glyph_width;

                    if (status < 0) {
                        if (*log_level > 1) {
                            if (*use_alternate_log_sink == 0) {
                                log_message(0x000aaa58UL, 0x000aad4bUL,
                                            codepoint, 0);
                            } else {
                                debug_print();
                            }
                        }
                    } else {
                        int32_t width_bytes = glyph_width / 2;
                        int32_t bitmap_bytes = glyph_height * width_bytes;
                        checked_bitmap_copy(glyph_pixels, glyph_bitmap,
                                            (uint32_t)bitmap_bytes, 676);

                        if (text_index < masked_glyph_count) {
                            uint8_t *pixel = glyph_pixels;
                            int32_t byte_index;
                            for (byte_index = 0; byte_index < bitmap_bytes;
                                 byte_index++) {
                                *pixel++ &= *glyph_dither_mask;
                            }
                        }

                        line_width +=
                            get_glyph_pair_spacing(cursor[-1], cursor[0]) +
                            (uint32_t)current_width;
                        if ((uint32_t)(right - (int32_t)left) < line_width) {
                            vertical_offset += (uint32_t)current_height;
                            if (font == 0) {
                                vertical_offset++;
                            }
                            line_count++;
                            if (maximum_lines <= line_count ||
                                (uint32_t)(bottom - top) <= vertical_offset) {
                                break;
                            }
                            fb_blit_rows_copy(*active_canvas, glyph_pixels,
                                              (uint32_t)width_bytes,
                                              (uint32_t)current_height,
                                              aligned_x,
                                              vertical_offset + (uint32_t)top);
                            x_offset = get_glyph_pair_spacing(
                                           cursor[-1], cursor[0]) +
                                       (uint32_t)glyph_width;
                            line_width = x_offset;
                        } else {
                            fb_blit_rows_copy(*active_canvas, glyph_pixels,
                                              (uint32_t)width_bytes,
                                              (uint32_t)current_height,
                                              aligned_x + x_offset,
                                              vertical_offset + (uint32_t)top);
                            x_offset += get_glyph_pair_spacing(
                                            cursor[-1], cursor[0]) +
                                        (uint32_t)glyph_width;
                        }
                    }
                    measure_line = 0;
                } else {
                    if (character_class == -1 &&
                        (codepoint == '\r' || codepoint == '\n')) {
                        if (glyph_height == 0) {
                            vertical_offset += (font == 0) ? 27U : 26U;
                        } else {
                            vertical_offset += (uint32_t)glyph_height;
                            if (font == 0) {
                                vertical_offset++;
                            }
                        }
                        line_count++;
                        if (maximum_lines <= line_count ||
                            (uint32_t)(bottom - top) <= vertical_offset) {
                            break;
                        }
                        measure_line = 1;
                        x_offset = 0;
                        line_width = 0;
                    } else {
                        measure_line = 0;
                    }
                }
            }
        }

        if ((int32_t)(get_display_atomic_state() << 30) < 0) {
            uint32_t device = get_device_info();
            uint32_t front = *(uint32_t *)(device + 0xeb4U);
            device = get_device_info();
            reflash_fb_data_to_lcd(front, *(uint32_t *)(device + 0xeb8U),
                                   left, top, right, bottom);
        }
        return 0;
    }

    if (callback == 0) {
        return 0;
    }

invoke_callback:
    if (*log_level > 1) {
        if (*use_alternate_log_sink == 0) {
            log_message(0x000aaa7fUL, 0x000aad4bUL, 0, 0);
        } else {
            debug_print();
        }
    }
    return callback(0, utf8_text, font, left, top);
}
