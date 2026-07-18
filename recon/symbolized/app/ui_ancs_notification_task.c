#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003603c @ 0x0003603c
 * public-name: ui_ancs_notification_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 *   pull_message                             <= FUN_000342e0 @ 0x000342e0
 *   draw_message                             <= FUN_00035afc @ 0x00035afc
 *   render_ancs_notification_animation       <= FUN_00035f28 @ 0x00035f28
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 * address symbols (name @ address):
 *   rodata_a8c60                             @ 0x000a8c60
 *   rodata_a8c80                             @ 0x000a8c80
 *   rodata_a8c97                             @ 0x000a8c97
 *   g_200033d2                               @ 0x200033d2
 *   g_200033d3                               @ 0x200033d3
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_esb_notify_slave_role_guard            @ 0x20018d9f
 *   g_new_message_pending_flag               @ 0x2001b80e
 *   g_dashboard_close_pending                @ 0x2001b80f
 */
/* CPUAPP ui_ancs_notification_task @ 0x0003603c.
 * Raw/back-map identity: FUN_0003603c, exact extent 0x128 bytes. */
#include <stdint.h>

extern void gui_screen_clear(void);
extern void FUN_000438d0(void);
extern void gui_set_active_canvas(void *framebuffer);
extern void gui_canvas_flags_set_bit1(void);
extern uint32_t FUN_00034390(void);
extern uint32_t msg_content_recalc_unread(void);
extern uint32_t pull_message(uintptr_t *message);
extern void render_ancs_notification_animation(void *framebuffer, uint32_t message_index);
extern void draw_message(uint32_t message_index, uintptr_t message);
extern void log_message(uintptr_t format, ...);
extern void debug_print(uintptr_t format, ...);

#define LOG_ROUTE (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
#define LAST_GROUP (*(volatile uint8_t *)((unsigned long)&g_200033d3) /*=0x200033d3*/)
#define LAST_INDEX (*(volatile uint8_t *)((unsigned long)&g_200033d2) /*=0x200033d2*/)
#define MESSAGE_ACTIVE (*(volatile uint8_t *)((unsigned long)&g_dashboard_close_pending) /*=0x2001b80f*/)
#define MESSAGE_MASK_ACTIVE (*(volatile uint8_t *)((unsigned long)&g_new_message_pending_flag) /*=0x2001b80e*/)
#define DISPLAY_DIRTY (*(volatile uint8_t *)((unsigned long)&g_esb_notify_slave_role_guard) /*=0x20018d9f*/)

#define TASK_LOG(format) do { \
    if (LOG_ROUTE == 0u) log_message((format)); \
    else debug_print((format)); \
} while (0)

uint32_t ui_ancs_notification_task(uint8_t *canvas, uint32_t unused,
                                   uint32_t phase)
{
    uintptr_t message = 0u;
    uint32_t group;
    uint32_t index;

    (void)unused;
    if (phase == 2u) {
        TASK_LOG(((unsigned long)&rodata_a8c60) /*=0xa8c60*/);
        LAST_GROUP = 0xffu;
        LAST_INDEX = 0xffu;
        if (MESSAGE_ACTIVE == 0u)
            gui_screen_clear();
        else {
            FUN_000438d0();
            MESSAGE_ACTIVE = 0u;
        }
        DISPLAY_DIRTY = 0u;
        return 0u;
    }
    if (phase == 0u)
        return 0u;

    if (LAST_GROUP == 0xffu) {
        gui_set_active_canvas(canvas + 0x24);
        gui_canvas_flags_set_bit1();
        gui_screen_clear();
    }
    group = FUN_00034390();
    index = msg_content_recalc_unread();
    if (LAST_GROUP == (uint8_t)group && LAST_INDEX == (uint8_t)index)
        return 0u;
    if (pull_message(&message) > 9u) {
        TASK_LOG(((unsigned long)&rodata_a8c80) /*=0xa8c80*/);
        LAST_GROUP = 0xffu;
        LAST_INDEX = 0xffu;
        return 0u;
    }
    if (*(volatile uint8_t *)(message + 0x0f) == 0u) {
        LAST_GROUP = 0xffu;
        LAST_INDEX = 0xffu;
        TASK_LOG(((unsigned long)&rodata_a8c97) /*=0xa8c97*/);
        return 0u;
    }
    if (*(volatile uint8_t *)(message + 0x0e) == 0u) {
        LAST_GROUP = 0xffu;
        LAST_INDEX = 0xffu;
        TASK_LOG(0x000a8cb6u);
        return 0u;
    }
    if (MESSAGE_MASK_ACTIVE != 0u) {
        render_ancs_notification_animation(canvas + 0x24, index);
        MESSAGE_MASK_ACTIVE = 0u;
    }
    draw_message(index, message);
    LAST_GROUP = (uint8_t)group;
    LAST_INDEX = (uint8_t)index;
    DISPLAY_DIRTY = 0u;
    return 0u;
}
