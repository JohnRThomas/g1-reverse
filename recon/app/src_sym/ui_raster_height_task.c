/* Reconstructed ui_raster_height_task @ 0x430c0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void *get_device_info(void);
extern void debug_print(unsigned long, ...);
extern void ui_DashBoard_task(uint32_t, uint32_t, int);
extern void cal_panel_canvas_coord(int*, int*);
extern void gui_screen_clear(void);
extern void FUN_00072880(int);

unsigned int ui_raster_height_task(unsigned int param_1, unsigned int param_2, int param_3)
{
    volatile int *piVar2 = (volatile int*)0x20002540UL;
    volatile int *piVar1 = (volatile int*)0x2000253cUL;
    int iVar3;
    int iVar4;
    int iVar5;
    int local_20 = -1;
    int local_1c = -1;

    if (param_3 == 2) {
        if (2 < *(volatile int*)0x2000230cUL) {
            if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                DEBUG_PRINT(0x000aa7f2UL, 0x000aa83fUL);
            } else {
                debug_print(0x000aa7f2UL, 0x000aa83fUL);
            }
        }
        ui_DashBoard_task(param_1, param_2, 2);
        *piVar2 = -1;
        *piVar1 = -1;
    } else {
        cal_panel_canvas_coord(&local_20, &local_1c);
        iVar5 = local_20;
        if ((local_20 != *piVar2) || (local_1c != *piVar1)) {
            if (2 < *(volatile int*)0x2000230cUL) {
                if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xb58 */ == 0) {
                    DEBUG_PRINT(0x000aa817UL, 0x000aa83fUL);
                } else {
                    debug_print(0x000aa817UL, 0x000aa83fUL);
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
            FUN_00072880(iVar5 + 0x80);
        }
    }
    return 0;
}

