/* Recovered render_ancs_notification_animation <= FUN_00035f28 @ 0x00035f28.
 * Executable extent is exactly 0xe2 bytes through the tail branch at 0x36006;
 * 0x3600a is alignment and the literal pool starts at 0x3600c.
 * Durable reverse mapping: recon/catalogs/function_names_app.json.
 */
#include <stdint.h>

/* Semantic aliases retain exact raw linker identities. */
#define log_message DEBUG_PRINT
#define debug_print FUN_00019c70
#define gui_canvas_flags_clear_bit1 FUN_000432ec
#define gui_canvas_flags_set_bit1 FUN_000432d0
#define draw_message FUN_00035afc
#define get_device_info FUN_000167a8
#define reflash_fb_data_to_lcd FUN_00047260

extern void log_message(uintptr_t, ...);
extern void debug_print(uintptr_t, ...);
extern void gui_canvas_flags_clear_bit1(void);
extern void gui_canvas_flags_set_bit1(void);
extern void draw_message(uint32_t, int);
extern void FUN_00074844(uint32_t, uint32_t);
extern uint8_t *get_device_info(void);
extern void reflash_fb_data_to_lcd(uint32_t, uint32_t, uint32_t, uint32_t,
                                   uint32_t, uint32_t);

void render_ancs_notification_animation(uint8_t **framebuffer_rows,
                                        uint32_t message_kind,
                                        int display_enabled)
{
    volatile int32_t *const use_alternate_log_sink =
        (volatile int32_t *)0x20007554u;
    if (!display_enabled || !framebuffer_rows) {
        uintptr_t format = display_enabled ? 0x000a8c42u : 0x000a8bcdu;
        uint32_t line = display_enabled ? 0x157u : 0x152u;
        if (*use_alternate_log_sink)
            debug_print(format, 0x000a8cd1u, line);
        else
            log_message(format, 0x000a8cd1u, line);
        return;
    }

    gui_canvas_flags_clear_bit1();
    const uint8_t *const reveal_selectors = (const uint8_t *)0x000a8c57u;
    for (uint32_t pass = 0; pass < 8; ++pass) {
        draw_message(message_kind, display_enabled);
        uint8_t selector = reveal_selectors[pass];
        for (uint32_t row = 0; row < 199; ++row) {
            uint8_t *pixels = framebuffer_rows[row];
            const uint8_t *mask = (const uint8_t *)(0x000aae20u +
                (uint32_t)selector * 0x140u + (row % 26u) * 0xa00u);
            for (uint32_t column = 0; column < 0x140; ++column)
                if (pixels[column]) pixels[column] &= mask[column];
        }
        FUN_00074844(0xa4, 0);
        uint8_t *state = get_device_info();
        uint32_t first = *(uint32_t *)(state + 0xeb4);
        state = get_device_info();
        reflash_fb_data_to_lcd(first, *(uint32_t *)(state + 0xeb8),
                               0, 0, 0x280, 199);
    }
    gui_canvas_flags_set_bit1();
}
