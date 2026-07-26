#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00036b3c @ 0x00036b3c
 * public-name: ui_new_message_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_message_pending_state                <= FUN_00034410 @ 0x00034410
 *   notification_icon_type_from_package      <= FUN_0003483c @ 0x0003483c
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 * address symbols (name @ address):
 *   rodata_a8e61                             @ 0x000a8e61   [INLINED -- G6 literal batch]
 *   rodata_a8e84                             @ 0x000a8e84   [INLINED -- G6 literal batch]
 *   rodata_a8e98                             @ 0x000a8e98
 *   rodata_aae20                             @ 0x000aae20
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_2001b812                               @ 0x2001b812
 *   g_2001b813                               @ 0x2001b813
 */
/* CPUAPP ui_new_message_task @ 0x00036b3c.
 * Raw/back-map identity: FUN_00036b3c, exact reachable extent 0x1fc bytes. */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern uintptr_t get_device_info(void);
extern uint32_t get_message_pending_state(void);
extern uint32_t notification_icon_type_from_package(uint32_t index);
extern void gui_screen_clear(void);
extern void gui_set_active_canvas(void *framebuffer);
extern void gui_canvas_flags_set_bit1(void);
extern void gui_canvas_flags_clear_bit1(void);
extern uint32_t device_info_text_width_get(void);
extern uint32_t device_info_text_height_get_clamped(void);
extern void gui_bmp_bitmap_draw(uint32_t glyph, uint32_t x, uint32_t y,
                         uint32_t a3, uint32_t a4, uint32_t a5);
extern void reflash_fb_data_to_lcd(uintptr_t left, uintptr_t right, uint32_t x,
                         uint32_t y, uint32_t width, uint32_t height);

#define LOG_ROUTE (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define MESSAGE_TASK_ACTIVE (*(volatile uint8_t *)((unsigned long)&g_2001b813) /*=0x2001b813*/)
#define MESSAGE_TASK_RENDERED (*(volatile uint8_t *)((unsigned long)&g_2001b812) /*=0x2001b812*/)
#define MASK_TABLE ((const uint8_t *)((unsigned long)&rodata_aae20) /*=0xaae20*/)
#define MASK_PHASE ((const uint8_t *)((unsigned long)&rodata_a8e98) /*=0xa8e98*/)

#define TASK_LOG(format, ...) do { \
    if (LOG_ROUTE == 0u) log_message((format), ##__VA_ARGS__); \
    else debug_print((format), ##__VA_ARGS__); \
} while (0)

uint32_t ui_new_message_task(uint8_t *canvas, uint32_t unused, uint32_t phase)
{
    uintptr_t state = get_device_info();
    uint32_t mode = get_message_pending_state();
    uint8_t was_active = MESSAGE_TASK_ACTIVE;

    (void)unused;
    if (mode == 4u)
        return 0u;
    if (phase == 2u) {
        TASK_LOG(((unsigned long)"ui_new_message_come_on_task exit !") /*=0xa8e61*/);
        gui_screen_clear();
        MESSAGE_TASK_ACTIVE = 0u;
        MESSAGE_TASK_RENDERED = 0u;
        return 0u;
    }
    if (phase == 0u)
        return 0u;

    if (MESSAGE_TASK_ACTIVE == 0u) {
        MESSAGE_TASK_ACTIVE = 1u;
        gui_set_active_canvas(canvas + 0x24);
        gui_canvas_flags_set_bit1();
        gui_screen_clear();
        MESSAGE_TASK_RENDERED = was_active;
    }
    if (*(volatile uint8_t *)(state + 0xf6u) < 2u) {
        MESSAGE_TASK_RENDERED = 0u;
        gui_screen_clear();
        return 0u;
    }

    state = get_device_info();
    uint32_t message_type = notification_icon_type_from_package(
        (uint8_t)(*(volatile uint8_t *)(state + 0xddu) - 1u));
    TASK_LOG(((unsigned long)"new msgType is %d \n") /*=0xa8e84*/, message_type);
    if (MESSAGE_TASK_RENDERED != 0u)
        return 0u;

    gui_canvas_flags_clear_bit1();
    for (uint32_t frame = 0u; frame != 8u; ++frame) {
        uint32_t glyph;
        switch (message_type) {
        case 1u: glyph = 0x37u; break;
        case 2u: glyph = 0x36u; break;
        case 3u: glyph = 0x3au; break;
        case 4u: glyph = 0x39u; break;
        default: glyph = 0x38u; break;
        }
        uint32_t x = device_info_text_width_get();
        uint32_t y = device_info_text_height_get_clamped() + 0x3au;
        gui_bmp_bitmap_draw(glyph, x, y, 0u, 0u, 0u);

        for (uint32_t row = 0u; row != 199u; ++row) {
            uint8_t *pixels = *(uint8_t **)(void *)(canvas + 0x24u + row * 4u);
            const uint8_t *mask = MASK_TABLE + (row % 26u) * 0xa00u +
                                  (uint32_t)MASK_PHASE[frame] * 0x140u;
            for (uint32_t column = 0u; column != 0x140u; ++column) {
                uint8_t pixel = pixels[column];
                if (pixel != 0u)
                    pixels[column] = (uint8_t)(pixel & mask[column]);
            }
        }
        state = get_device_info();
        uintptr_t left = *(volatile uintptr_t *)(state + 0xeb4u);
        state = get_device_info();
        reflash_fb_data_to_lcd(left, *(volatile uintptr_t *)(state + 0xeb8u),
                     0u, 0u, 0x280u, 199u);
    }
    gui_canvas_flags_set_bit1();
    MESSAGE_TASK_RENDERED = 1u;
    return 0u;
}
