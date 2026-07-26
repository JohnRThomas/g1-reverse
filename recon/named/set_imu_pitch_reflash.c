/* readable reconstruction; identity: FUN_000469bc @ 0x000469bc
 * public-name: set_imu_pitch_reflash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_ui_mode_flag_byte1                   <= FUN_00023ee0 @ 0x00023ee0
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   gui_utf_draw                             <= FUN_00043e90 @ 0x00043e90
 *   set_imu_pitch_reflash                    <= FUN_000469bc @ 0x000469bc
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 *   get_localized_weekday_name               <= FUN_0007d4b2 @ 0x0007d4b2
 * address symbols (name @ address):
 *   rodata_d7173                             @ 0x000d7173   [INLINED -- G6 literal batch]
 *   rodata_d71f9                             @ 0x000d71f9   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_imu_pitch_last_state                   @ 0x2001cf91
 */
/* Full reconstruction of FUN_000469bc @ 0x469bc, exact extent 430 bytes.
 * Call arities are derived by target because optional logging and cache
 * refresh calls do not have stable ordinals. */
#include <stdint.h>
#include "../headers/g1_log.h"

extern uintptr_t get_device_info(void);
extern void gui_screen_clear(void);
extern int get_ui_mode_flag_byte1(void);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern uintptr_t get_localized_weekday_name(unsigned id);
extern void gui_bmp_bitmap_draw(int, int, int, int, int, int);
extern unsigned gui_utf_draw(unsigned, uintptr_t, unsigned, int, int, int, int,
                            unsigned, unsigned, int, void *, int);

static __attribute__((always_inline)) inline void draw_pair(uintptr_t text, int x, unsigned second_id)
{
    int y0 = device_info_text_width_get();
    int x0 = device_info_text_height_get_clamped();
    int y1 = device_info_text_width_get();
    int x1 = device_info_text_height_get_clamped();
    gui_utf_draw(0, text, 0, x + y0, x0 + 0x3c, y1 + 0x240,
                 x1 + 0x57, 1, 0, 0, 0, 0);

    x = (get_ui_mode_flag_byte1() == 6)
        ? (second_id == 5 ? 0x78 : 0x22)
        : (second_id == 5 ? 0x9e : 0x6e);
    text = get_localized_weekday_name(second_id);
    y0 = device_info_text_width_get(); x0 = device_info_text_height_get_clamped();
    y1 = device_info_text_width_get(); x1 = device_info_text_height_get_clamped();
    gui_utf_draw(0, text, 0, x + y0, x0 + 0x71, y1 + 0x240,
                 x1 + 0x8c, 1, 0, 0, 0, 0);
}

unsigned set_imu_pitch_reflash(void)
{
    uintptr_t state = get_device_info();
    uint8_t mode = *(volatile uint8_t *)(state + 0xf0);
    volatile uint8_t *cached_mode = (volatile uint8_t *)0x2001cf91u;

    if (mode >= 2) {
        if (*(volatile int *)0x2000230cu > 0) {
            if (*(volatile int *)0x20007554u == 0)
                log_message(0x000d7173u, 0x000d71f9u);
            else
                debug_print(0x000d7173u, 0x000d71f9u);
        }
        return UINT32_MAX;
    }
    if (*cached_mode != mode) {
        gui_screen_clear();
        *cached_mode = *(volatile uint8_t *)(state + 0xf0);
    }

    int y = device_info_text_width_get();
    int x = device_info_text_height_get_clamped();
    gui_bmp_bitmap_draw(0x7c, y + 0x52, x + 0x65, 0, 0, 0);

    if (*(volatile int8_t *)(state + 0xf0) == 1) {
        int first_x = (get_ui_mode_flag_byte1() == 6) ? 0xb6 : 0xba;
        draw_pair(get_localized_weekday_name(4), first_x, 5);
    } else {
        int first_x = (get_ui_mode_flag_byte1() == 6) ? 0xd0 : 0xc0;
        draw_pair(get_localized_weekday_name(2), first_x, 3);
    }
    return 0;
}
