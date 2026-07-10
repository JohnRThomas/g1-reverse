#include "g1_app_symbols.h"
/* named: gui_area_clear */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed gui_area_clear @ 0x43228  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);
extern uint32_t get_device_info(void);
extern void debug_print(void);
extern void clean_fb_data(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);
extern void reflash_fb_data_to_lcd(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);
extern uint32_t get_projector_controller(void);

uint32_t gui_area_clear(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    volatile int *piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    uint32_t iVar2;
    uint32_t uVar3;

    if (*piVar1 > 2) {
        if (*(volatile uint32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): exec area clear command....\n" /*=0xaa8c8*/, "gui_area_clear" /*=0xaae00*/, param_3, 0, param_1, param_2);
        } else {
            debug_print();
        }
    }
    iVar2 = get_projector_controller();
    if (*(uint32_t*)(iVar2 + 0x35c) == 0) {
        if (*piVar1 > 0) {
            if (*(volatile uint32_t*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): c->init_done = 0,init failed, can't write data!\n" /*=0xaa891*/, "gui_area_clear" /*=0xaae00*/, 0,0,0,0);
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffff;
    } else {
        iVar2 = get_device_info();
        clean_fb_data(iVar2 + 0xb90, 0, param_1, param_2, param_3, param_4);
        iVar2 = get_device_info();
        uVar3 = *(uint32_t*)(iVar2 + 0xeb4);
        iVar2 = get_device_info();
        reflash_fb_data_to_lcd(uVar3, *(uint32_t*)(iVar2 + 0xeb8), param_1, param_2, param_3, param_4);
        uVar3 = 0;
    }
    return uVar3;
}

