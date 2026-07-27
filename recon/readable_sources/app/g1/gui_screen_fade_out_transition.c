#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004382c @ 0x0004382c
 * public-name: gui_screen_fade_out_transition
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_screen_fade_out_transition           <= FUN_0004382c @ 0x0004382c
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   delay_scaled_busy_wait                   <= FUN_00086384 @ 0x00086384
 * address symbols (name @ address):
 *   rodata_aae20                             @ 0x000aae20
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Full reconstruction of FUN_0004382c @ 0x4382c (164 bytes). */
#include <stdint.h>

extern int get_device_info(void);
extern void reflash_fb_data_to_lcd(uint32_t left, uint32_t right, uint32_t x,
                        uint32_t y, uint32_t width, uint32_t height);
extern void delay_scaled_busy_wait(int);
extern void gui_screen_clear(void);

int gui_screen_fade_out_transition(void)
{
    int32_t mask_row = 0;
    do {
        uint32_t **rows = *(uint32_t ***)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/;
        for (uint32_t row = 0; row != 199; ++row) {
            uint8_t *destination = (uint8_t *)rows[row];
            const uint8_t *mask = (const uint8_t *)(((unsigned long)&rodata_aae20) /*=0xaae20*/ + 0x8c0u +
                (row % 26u) * 0xa00u + mask_row);
            for (uint32_t column = 0; column != 0x140; ++column) {
                if (destination[column] != 0)
                    destination[column] &= mask[column];
            }
        }

        const uint8_t *display = (const uint8_t *)get_device_info();
        uint32_t left = *(const uint32_t *)(display + 0xeb4);
        display = (const uint8_t *)get_device_info();
        uint32_t right = *(const uint32_t *)(display + 0xeb8);
        reflash_fb_data_to_lcd(left, right, 0, 0, 0x280, 199);
        mask_row -= 0x140;
        delay_scaled_busy_wait(5000);
    } while (mask_row != -0xa00);

    gui_screen_clear();
    return 0;
}
