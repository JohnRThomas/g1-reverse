#include "g1_app_symbols.h"
#include "../../../../headers/g1_log.h"
#include "g1_navigation.h"
/* readable reconstruction; identity: FUN_0003dff8 @ 0x0003dff8
 * public-name: navigation_direction_img_display
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   gui_bmp_bitmap_draw                      <= FUN_00043484 @ 0x00043484
 *   device_info_text_width_get               <= FUN_0007d3ee @ 0x0007d3ee
 *   device_info_text_height_get_clamped      <= FUN_0007d446 @ 0x0007d446
 * address symbols (name @ address):
 *   rodata_a9e91                             @ 0x000a9e91   [INLINED -- G6 literal batch]
 *   rodata_aa466                             @ 0x000aa466   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed navigation_direction_img_display @ 0x3dff8  (parity: 300/300 trials, PROVEN) */

extern void gui_bmp_bitmap_draw(int a, int b, int c, int d, int e, int f, int g);

void navigation_direction_img_display(int param_1, int param_2, int param_3)
{
    unsigned int uVar1;
    int iVar2;

    if ((unsigned int)(param_1 - 1) < 0x23) {
        uVar1 = device_info_text_width_get();
        iVar2 = device_info_text_height_get_clamped();
        gui_bmp_bitmap_draw(param_1 + 0x55, uVar1, iVar2 + 0x39, 0, 0, 0, param_3);
    } else if (1 < *(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ != 0) {
            debug_print(((unsigned long)"%s(): navigation direction parampter error\n") /*=0xa9e91*/, ((unsigned long)"navigation_direction_img_display") /*=0xaa466*/);
        } else {
            log_message(((unsigned long)"%s(): navigation direction parampter error\n") /*=0xa9e91*/, ((unsigned long)"navigation_direction_img_display") /*=0xaa466*/);
        }
    }
}
