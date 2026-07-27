#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00035f28 @ 0x00035f28
 * public-name: render_ancs_notification_animation
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   draw_message                             <= FUN_00035afc @ 0x00035afc
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 * address symbols (name @ address):
 *   rodata_a8bcd                             @ 0x000a8bcd   [INLINED -- G6 literal batch]
 *   rodata_a8c57                             @ 0x000a8c57
 *   rodata_a8cd1                             @ 0x000a8cd1   [INLINED -- G6 literal batch]
 *   rodata_aae20                             @ 0x000aae20
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Recovered render_ancs_notification_animation <= FUN_00035f28 @ 0x00035f28.
 * Executable extent is exactly 0xe2 bytes through the tail branch at 0x36006;
 * 0x3600a is alignment and the literal pool starts at 0x3600c.
 * Durable reverse mapping: recon/catalogs/function_names_app.json.
 */
#include <stdint.h>
#include "../../../headers/g1_log.h"

/* Semantic aliases retain exact raw linker identities. */
#define log_message log_message
#define debug_print debug_print
#define gui_canvas_flags_clear_bit1 gui_canvas_flags_clear_bit1
#define gui_canvas_flags_set_bit1 gui_canvas_flags_set_bit1
#define draw_message draw_message
#define get_device_info get_device_info
#define reflash_fb_data_to_lcd reflash_fb_data_to_lcd

extern void gui_canvas_flags_clear_bit1(void);
extern void gui_canvas_flags_set_bit1(void);
extern void draw_message(uint32_t, int);
extern int32_t k_sleep(k_timeout_t);
extern int get_device_info(void);
extern void reflash_fb_data_to_lcd(uint32_t, uint32_t, uint32_t, uint32_t,
                                   uint32_t, uint32_t);

void render_ancs_notification_animation(uint8_t **framebuffer_rows,
                                        uint32_t message_kind,
                                        int display_enabled)
{
    volatile int32_t *const use_alternate_log_sink =
        (volatile int32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    if (!display_enabled || !framebuffer_rows) {
        uintptr_t format = display_enabled ? 0x000a8c42u : ((unsigned long)"[%s-%d]curMsg is NULL !\n") /*=0xa8bcd*/;
        uint32_t line = display_enabled ? 0x157u : 0x152u;
        if (*use_alternate_log_sink)
            debug_print(format, ((unsigned long)"draw_particle_effects") /*=0xa8cd1*/, line);
        else
            log_message(format, ((unsigned long)"draw_particle_effects") /*=0xa8cd1*/, line);
        return;
    }

    gui_canvas_flags_clear_bit1();
    const uint8_t *const reveal_selectors = (const uint8_t *)((unsigned long)&rodata_a8c57) /*=0xa8c57*/;
    for (uint32_t pass = 0; pass < 8; ++pass) {
        draw_message(message_kind, display_enabled);
        uint8_t selector = reveal_selectors[pass];
        for (uint32_t row = 0; row < 199; ++row) {
            uint8_t *pixels = framebuffer_rows[row];
            const uint8_t *mask = (const uint8_t *)(((unsigned long)&rodata_aae20) /*=0xaae20*/ +
                (uint32_t)selector * 0x140u + (row % 26u) * 0xa00u);
            for (uint32_t column = 0; column < 0x140; ++column)
                if (pixels[column]) pixels[column] &= mask[column];
        }
        k_sleep(0xa4, 0);
        uint8_t *state = get_device_info();
        uint32_t first = *(uint32_t *)(state + 0xeb4);
        state = get_device_info();
        reflash_fb_data_to_lcd(first, *(uint32_t *)(state + 0xeb8),
                               0, 0, 0x280, 199);
    }
    gui_canvas_flags_set_bit1();
}
