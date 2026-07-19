#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000430c0 @ 0x000430c0
 * public-name: ui_raster_height_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   ui_DashBoard_task                        <= FUN_0003af78 @ 0x0003af78
 *   cal_panel_canvas_coord                   <= FUN_00042fb0 @ 0x00042fb0
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_aa7f2                             @ 0x000aa7f2
 *   rodata_aa817                             @ 0x000aa817
 *   rodata_aa83f                             @ 0x000aa83f
 *   g_log_level                              @ 0x2000230c
 *   g_display_canvas_y_cache                 @ 0x2000253c
 *   g_display_canvas_x_cache                 @ 0x20002540
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed ui_raster_height_task @ 0x430c0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void log_message(uint32_t, ...);
extern void *get_device_info(void);
extern void debug_print(uint32_t, ...);
extern void ui_DashBoard_task(uint32_t, uint32_t, int);
extern void cal_panel_canvas_coord(int*, int*);
extern void gui_screen_clear(void);
extern void k_sem_give(int);

unsigned int ui_raster_height_task(unsigned int param_1, unsigned int param_2, int param_3)
{
    volatile int *piVar2 = (volatile int*)((unsigned long)&g_display_canvas_x_cache) /*=0x20002540*/;
    volatile int *piVar1 = (volatile int*)((unsigned long)&g_display_canvas_y_cache) /*=0x2000253c*/;
    int iVar3;
    int iVar4;
    int iVar5;
    int local_20 = -1;
    int local_1c = -1;

    if (param_3 == 2) {
        if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_aa7f2) /*=0xaa7f2*/, ((unsigned long)&rodata_aa83f) /*=0xaa83f*/);
            } else {
                debug_print(((unsigned long)&rodata_aa7f2) /*=0xaa7f2*/, ((unsigned long)&rodata_aa83f) /*=0xaa83f*/);
            }
        }
        ui_DashBoard_task(param_1, param_2, 2);
        *piVar2 = -1;
        *piVar1 = -1;
    } else {
        cal_panel_canvas_coord(&local_20, &local_1c);
        iVar5 = local_20;
        if ((local_20 != *piVar2) || (local_1c != *piVar1)) {
            if (2 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
                if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    log_message(((unsigned long)&rodata_aa817) /*=0xaa817*/, ((unsigned long)&rodata_aa83f) /*=0xaa83f*/);
                } else {
                    debug_print(((unsigned long)&rodata_aa817) /*=0xaa817*/, ((unsigned long)&rodata_aa83f) /*=0xaa83f*/);
                }
            }
            gui_screen_clear();
            iVar3 = local_1c;
            *piVar2 = iVar5;
            *piVar1 = local_1c;
            iVar4 = (int)(intptr_t)get_device_info();
            *(int*)(intptr_t)(iVar4 + 0xec4) = iVar5;
            iVar5 = (int)(intptr_t)get_device_info();
            *(int*)(intptr_t)(iVar5 + 0xeb8) = iVar3;
            ui_DashBoard_task(param_1, param_2, 1);
            iVar5 = (int)(intptr_t)get_device_info();
            *(unsigned int*)(intptr_t)(iVar5 + 0x104c) = 0x26;
            iVar5 = (int)(intptr_t)get_device_info();
            k_sem_give(iVar5 + 0x80);
        }
    }
    return 0;
}
