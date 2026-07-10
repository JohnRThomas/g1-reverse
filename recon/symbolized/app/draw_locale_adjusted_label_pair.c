#include "g1_app_symbols.h"
/* named: draw_locale_adjusted_label_pair */
/* Reconstructed draw_locale_adjusted_label_pair @ 0x3f2a8  (parity: 200/200 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00023ee0(void);
extern int device_info_text_width_get(void);
extern int device_info_text_height_get_clamped(void);
extern int gui_utf_draw(int,...);
void draw_locale_adjusted_label_pair(void){
    int iVar1 = FUN_00023ee0();
    if (iVar1 == 6){
        device_info_text_width_get(); device_info_text_height_get_clamped(); device_info_text_width_get(); device_info_text_height_get_clamped();
        gui_utf_draw(0,"Navigation aufgrund einer" /*=0xaa056*/,0,0,0,0,0,1,0,0,0,0);
        device_info_text_width_get(); device_info_text_height_get_clamped(); device_info_text_width_get(); device_info_text_height_get_clamped();
    } else {
        device_info_text_width_get(); device_info_text_height_get_clamped(); device_info_text_width_get(); device_info_text_height_get_clamped();
    }
    gui_utf_draw(0,0,0,0,0,0,0,1,0,0,0,0);
}

