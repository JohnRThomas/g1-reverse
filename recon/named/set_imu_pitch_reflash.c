/* named: set_imu_pitch_reflash */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed set_imu_pitch_reflash @ 0x469bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern int get_device_info(void);
extern void debug_print(void);
extern int FUN_00023ee0(void);
extern void gui_screen_clear(void);
extern void gui_bmp_bitmap_draw(void);
extern void gui_utf_draw(void);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern int get_localized_weekday_name(void);

unsigned set_imu_pitch_reflash(void)
{
    int iVar1 = get_device_info();
    if (*(volatile uint8_t*)(iVar1 + 0xf0) < 2) {
        if (*(volatile uint8_t*)0x2001cf91 != *(volatile uint8_t*)(iVar1 + 0xf0)) {
            gui_screen_clear();
            *(volatile uint8_t*)0x2001cf91 = *(volatile uint8_t*)(iVar1 + 0xf0);
        }
        if (*(volatile int8_t*)(iVar1 + 0xf0) == 1) {
            device_info_text_width_get(); device_info_text_height_get_clamped(); gui_bmp_bitmap_draw();
            FUN_00023ee0(); get_localized_weekday_name();
            device_info_text_width_get(); device_info_text_height_get_clamped(); device_info_text_width_get(); device_info_text_height_get_clamped();
            gui_utf_draw(); FUN_00023ee0();
        } else {
            device_info_text_width_get(); device_info_text_height_get_clamped(); gui_bmp_bitmap_draw();
            FUN_00023ee0(); get_localized_weekday_name();
            device_info_text_width_get(); device_info_text_height_get_clamped(); device_info_text_width_get(); device_info_text_height_get_clamped();
            gui_utf_draw(); FUN_00023ee0();
        }
        get_localized_weekday_name();
        device_info_text_width_get(); device_info_text_height_get_clamped(); device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw();
        return 0;
    } else {
        if (0 < *(volatile int*)0x2000230c) {
            if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT();
            else debug_print();
        }
        return 0xffffffff;
    }
}

