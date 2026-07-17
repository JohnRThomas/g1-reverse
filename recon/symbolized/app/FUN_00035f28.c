#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00035f28 @ 0x00035f28
 * public-name: FUN_00035f28
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   draw_message                             <= FUN_00035afc @ 0x00035afc
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 * address symbols (name @ address):
 *   rodata_a8bcd                             @ 0x000a8bcd
 *   rodata_a8c57                             @ 0x000a8c57
 *   rodata_a8cd1                             @ 0x000a8cd1
 *   rodata_aae20                             @ 0x000aae20
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full reconstruction FUN_00035f28 @ 0x00035f28 (226-byte exact extent). */
#include <stdint.h>

extern void DEBUG_PRINT(uintptr_t, ...);
extern void debug_print(uintptr_t, ...);
extern void gui_canvas_flags_clear_bit1(void);
extern void gui_canvas_flags_set_bit1(void);
extern void draw_message(uint32_t, int);
extern void FUN_00074844(uint32_t, uint32_t);
extern uint8_t *get_device_info(void);
extern void reflash_fb_data_to_lcd(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

void FUN_00035f28(uint8_t **planes, uint32_t second, int enabled)
{
    if (!enabled || !planes) {
        uintptr_t format = enabled ? 0x000a8c42u : ((unsigned long)&rodata_a8bcd) /*=0xa8bcd*/;
        uint32_t line = enabled ? 0x157u : 0x152u;
        if (*(volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
            debug_print(format, ((unsigned long)&rodata_a8cd1) /*=0xa8cd1*/, line);
        else
            DEBUG_PRINT(format, ((unsigned long)&rodata_a8cd1) /*=0xa8cd1*/, line);
        return;
    }

    gui_canvas_flags_clear_bit1();
    const uint32_t *masks = (const uint32_t *)((unsigned long)&rodata_a8c57) /*=0xa8c57*/;
    for (uint32_t pass = 0; pass < 8; ++pass) {
        draw_message(second, enabled);
        uint64_t packed = ((uint64_t)masks[1] << 32) | masks[0];
        for (uint32_t row = 0; row < 199; ++row) {
            uint8_t *pixels = planes[row];
            uint8_t selector = (packed >> (pass * 8)) & 0xffu;
            const uint8_t *mask = (const uint8_t *)(((unsigned long)&rodata_aae20) /*=0xaae20*/ +
                (uint32_t)selector * 0x140u + (row % 26u) * 0xa00u);
            for (uint32_t column = 0; column < 0x140; ++column)
                if (pixels[column]) pixels[column] &= mask[column];
        }
        FUN_00074844(0xa4, 0);
        uint8_t *state = get_device_info();
        uint32_t first = *(uint32_t *)(state + 0xeb4);
        state = get_device_info();
        reflash_fb_data_to_lcd(first, *(uint32_t *)(state + 0xeb8), 0, 0, 0x280, 199);
    }
    gui_canvas_flags_set_bit1();
}
