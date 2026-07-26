/* readable reconstruction; identity: FUN_00044818 @ 0x00044818
 * public-name: gui_utf_draw_truncate
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_aaa58                             @ 0x000aaa58
 *   rodata_aaa7f                             @ 0x000aaa7f   [INLINED -- G6 literal batch]
 *   rodata_aab9e                             @ 0x000aab9e   [INLINED -- G6 literal batch]
 *   rodata_aabd2                             @ 0x000aabd2   [INLINED -- G6 literal batch]
 *   rodata_aad78                             @ 0x000aad78   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_gui_dark_light_dither_mask             @ 0x200034f6
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Recovered gui_utf_draw_truncate <= FUN_00044818 @ 0x00044818.
 * Reviewed executable extent: 0x3ac bytes through the callback/logger tail.
 * The historical 0x38a catalog extent stopped inside that live tail;
 * literals begin at 0x44bc4 and the next independent prologue is 0x44bd8.
 * Raw identities remain beside every semantic declaration for reversibility.
 */
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
extern void checked_bitmap_copy(void *, uint32_t, uint32_t, uint32_t);
    /* FUN_00086c1e */
extern void log_message(uint32_t format, uint32_t function,
                        uint32_t value, uint32_t extra); /* FUN_0007dda4 */

static volatile uint32_t *const active_canvas =
    (volatile uint32_t *)0x2000a034UL; /* g_gui_active_canvas */
static volatile int32_t *const log_level =
    (volatile int32_t *)0x2000230cUL; /* g_log_level */
static volatile int32_t *const use_alternate_log_sink =
    (volatile int32_t *)0x20007554UL; /* g_log_use_alt_sink */
static volatile uint8_t *const glyph_dither_mask =
    (volatile uint8_t *)0x200034f6UL; /* g_gui_dark_light_dither_mask */

uint32_t gui_utf_draw_truncate(uint32_t canvas, uint32_t utf8_text,
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
    uint32_t text_index = 0;
    uint32_t x_offset = 0;
    uint32_t measured_width = 0;
    uint32_t vertical_offset = 0;
    uint32_t line_count = 0;

    (void)canvas;

    if (callback != 0) {
        if (*log_level > 1) {
            if (*use_alternate_log_sink == 0) {
                log_message(((unsigned long)"%s(): exex process effect callback function\n"), 0x000aad78UL, 0, 0);
            } else {
                debug_print();
            }
        }
        return callback(0, utf8_text, font, left, top);
    }
    if (callback_mode != 0 || skip_builtin_rendering != 0) {
        return 0;
    }

    if ((int32_t)(get_display_atomic_state() << 30) < 0) {
        clean_fb_data(*active_canvas, 0, left, top, right, bottom);
    }

    for (;;) {
        uint32_t codepoint;
        int32_t character_class;

        if ((int32_t)utf16_count <= (int32_t)text_index) {
            break;
        }
        codepoint = *cursor;
        character_class = classify_text_character(codepoint);

        if (character_class == 0) {
            int32_t status = resource_manger_get(
                font, codepoint, &glyph_width, &glyph_height,
                &glyph_bitmap, 0);
            int32_t current_height = glyph_height;
            int32_t current_width = glyph_width;

            if (status < 0) {
                if (*log_level > 1) {
                    if (*use_alternate_log_sink == 0) {
                        log_message(0x000aaa58UL, 0x000aad78UL,
                                    codepoint, 0);
                    } else {
                        debug_print();
                    }
                }
            } else {
                int32_t width_bytes = glyph_width / 2;
                int32_t bitmap_bytes = glyph_height * width_bytes;
                int32_t pair_spacing;

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

                pair_spacing = (int32_t)get_glyph_pair_spacing(cursor[0],
                                                               cursor[1]);
                measured_width += (uint32_t)current_width +
                                  (uint32_t)pair_spacing;
                if ((uint32_t)(right - (int32_t)left) < measured_width) {
                    line_count++;
                    if (maximum_lines <= line_count ||
                        (uint32_t)(bottom - top) <= vertical_offset) {
                        uint32_t rewind_index = text_index;
                        uint16_t *rewind_cursor = cursor;

                        while (rewind_index != 0) {
                            if (3U < (uint32_t)((right - (int32_t)left) -
                                               (int32_t)x_offset)) {
                                break;
                            }
                            codepoint = rewind_cursor[-1];
                            status = resource_manger_get(
                                font, codepoint, &glyph_width, &glyph_height,
                                &glyph_bitmap, 0);
                            rewind_index--;
                            if (status < 0) {
                                if (*log_level > 1) {
                                    if (*use_alternate_log_sink == 0) {
                                        log_message(0x000aab9eUL,
                                                    0x000aad78UL,
                                                    rewind_index,
                                                    codepoint);
                                    } else {
                                        debug_print();
                                    }
                                }
                            } else {
                                pair_spacing = (int32_t)get_glyph_pair_spacing(
                                    rewind_cursor[-1], rewind_cursor[0]);
                                x_offset -= (uint32_t)glyph_width +
                                            (uint32_t)pair_spacing;
                                clean_fb_data(*active_canvas, 0,
                                              left + x_offset,
                                              top + (int32_t)vertical_offset,
                                              left + x_offset +
                                                  (uint32_t)glyph_width,
                                              top + (int32_t)vertical_offset +
                                                  glyph_height);
                            }
                            rewind_cursor--;
                        }

                        if (*log_level > 1) {
                            if (*use_alternate_log_sink == 0) {
                                log_message(0x000aabd2UL, 0x000aad78UL,
                                            x_offset, 0);
                            } else {
                                debug_print();
                            }
                        }
                        status = resource_manger_get(
                            font, 0x2026U, &glyph_width, &glyph_height,
                            &glyph_bitmap, 0);
                        current_height = glyph_height;
                        if (status < 0) {
                            if (*log_level > 1) {
                                if (*use_alternate_log_sink == 0) {
                                    log_message(0x000aaa58UL, 0x000aad78UL,
                                                0x2026U, 0);
                                } else {
                                    debug_print();
                                }
                            }
                            goto next_character;
                        } else {
                            int32_t ellipsis_width_bytes = glyph_width / 2;
                            int32_t ellipsis_bytes =
                                glyph_height * ellipsis_width_bytes;
                            checked_bitmap_copy(glyph_pixels, glyph_bitmap,
                                                (uint32_t)ellipsis_bytes, 676);
                            if (text_index < masked_glyph_count) {
                                uint8_t *pixel = glyph_pixels;
                                int32_t byte_index;
                                for (byte_index = 0;
                                     ellipsis_bytes - byte_index != 0 &&
                                         byte_index <= ellipsis_bytes;
                                     byte_index++) {
                                    *pixel++ &= *glyph_dither_mask;
                                }
                            }
                            fb_blit_rows_copy(*active_canvas, glyph_pixels,
                                              (uint32_t)ellipsis_width_bytes,
                                              (uint32_t)current_height,
                                              left + x_offset,
                                              top + vertical_offset);
                        }
                        goto rendering_done;
                    }

                    vertical_offset += (uint32_t)current_height;
                    if (font == 0) {
                        vertical_offset++;
                    }
                    fb_blit_rows_copy(*active_canvas, glyph_pixels,
                                      (uint32_t)width_bytes,
                                      (uint32_t)current_height, left,
                                      top + vertical_offset);
                    x_offset = (uint32_t)glyph_width +
                               get_glyph_pair_spacing(cursor[0], cursor[1]);
                    measured_width = x_offset;
                } else {
                    fb_blit_rows_copy(*active_canvas, glyph_pixels,
                                      (uint32_t)width_bytes,
                                      (uint32_t)current_height,
                                      left + x_offset, top + vertical_offset);
                    x_offset += (uint32_t)glyph_width +
                                get_glyph_pair_spacing(cursor[0], cursor[1]);
                }
            }
        } else if (character_class == -1 &&
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
            x_offset = 0;
            measured_width = 0;
        }

next_character:
        cursor++;
        text_index++;
    }

rendering_done:
    if ((int32_t)(get_display_atomic_state() << 30) < 0) {
        uint32_t device = get_device_info();
        uint32_t front = *(volatile uint32_t *)(device + 0xeb4U);
        device = get_device_info();
        reflash_fb_data_to_lcd(front,
                               *(volatile uint32_t *)(device + 0xeb8U),
                               left, top, right, bottom);
    }
    return 0;
}
