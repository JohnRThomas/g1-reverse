/* readable reconstruction; identity: FUN_000455cc @ 0x000455cc
 * public-name: gui_string_draw
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   atomic_get_3_0                           <= FUN_000431a8 @ 0x000431a8
 *   count_chars_in_default_font_table        <= FUN_00043e58 @ 0x00043e58
 *   resource_manger_get                      <= FUN_0004588c @ 0x0004588c
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   fb_blit_rows_copy                        <= FUN_0007d53a @ 0x0007d53a
 * address symbols (name @ address):
 *   rodata_aac62                             @ 0x000aac62
 *   rodata_aac9f                             @ 0x000aac9f
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Full reconstruction of gui_string_draw @ 0x455cc (280 bytes). */
#include <stdint.h>

extern int strlen(const uint8_t *s);
extern uint32_t atomic_get_3_0(void);
extern uintptr_t get_device_info(void);
extern void clean_fb_data(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern void reflash_fb_data_to_lcd(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern int resource_manger_get(uint32_t, uint32_t, int32_t *, int32_t *, uint32_t *, uint32_t);
extern void fb_blit_rows_copy(uint32_t, uint32_t, int32_t, int32_t, int32_t, uint32_t);
extern int count_chars_in_default_font_table(uint32_t, uint32_t);
extern void log_message(uint32_t, uint32_t);
extern void debug_print(uint32_t, uint32_t);

int gui_string_draw(uint32_t font, const uint8_t *text, int32_t x, uint32_t y,
                    uint32_t arg5, uint32_t arg6, int32_t *width_out)
{
    int32_t glyph_width = 0, glyph_height = 0;
    uint32_t bitmap = 0;
    int length = strlen(text);
    int32_t cursor = x;

    if (atomic_get_3_0() & 2u)
        clean_fb_data(*(volatile uint32_t *)0x2000a034u, 0, x, y, arg5, arg6);

    for (const uint8_t *p = text; p != text + length; ++p) {
        if (*p < 0x20u) {
            if (*(volatile int32_t *)0x2000230cu > 0) {
                if (*(volatile uint32_t *)0x20007554u == 0)
                    log_message(0x000aac83u, 0x000aac9fu);
                else
                    debug_print(0x000aac83u, 0x000aac9fu);
            }
            continue;
        }

        if (resource_manger_get(font, *p, &glyph_width, &glyph_height, &bitmap, 0) != 0 || bitmap == 0) {
            if (*(volatile int32_t *)0x2000230cu > 1) {
                if (*(volatile uint32_t *)0x20007554u == 0)
                    log_message(0x000aac62u, 0x000aac9fu);
                else
                    debug_print(0x000aac62u, 0x000aac9fu);
            }
            continue;
        }

        fb_blit_rows_copy(*(volatile uint32_t *)0x2000a034u, bitmap,
                     (glyph_width + (glyph_width < 0)) / 2, glyph_height,
                     cursor, y);
        if ((uint32_t)(*p - 0x20u) <= 0x5eu && font == 3)
            cursor += glyph_width + 3;
        else
            cursor += glyph_width + count_chars_in_default_font_table(*p, p[1]);
    }

    if (atomic_get_3_0() & 2u) {
        uintptr_t state = get_device_info();
        uint32_t left = *(volatile uint32_t *)(state + 0xeb4);
        state = get_device_info();
        reflash_fb_data_to_lcd(left, *(volatile uint32_t *)(state + 0xeb8), x, y, arg5, arg6);
    }
    if (width_out)
        *width_out = cursor - x;
    return 0;
}
