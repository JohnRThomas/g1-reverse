#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00043228 @ 0x00043228
 * public-name: gui_area_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   clean_fb_data                            <= FUN_000471cc @ 0x000471cc
 *   reflash_fb_data_to_lcd                   <= FUN_00047260 @ 0x00047260
 *   get_projector_controller                 <= FUN_0007d4ec @ 0x0007d4ec
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   rodata_aa891                             @ 0x000aa891
 *   rodata_aa8c8                             @ 0x000aa8c8
 *   rodata_aae00                             @ 0x000aae00
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed gui_area_clear @ 0x43228  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint32_t;

extern void log_message(uint32_t message, uint32_t function);
extern uint32_t get_device_info(void);
extern void debug_print(void);
extern void clean_fb_data(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);
extern void reflash_fb_data_to_lcd(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);
extern uint32_t get_projector_controller(void);

uint32_t gui_area_clear(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    volatile int *piVar1 = (volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    uint32_t iVar2;
    uint32_t uVar3;

    if (*piVar1 > 2) {
        if (*(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_aa8c8) /*=0xaa8c8*/, ((unsigned long)&rodata_aae00) /*=0xaae00*/);
        } else {
            debug_print();
        }
    }
    iVar2 = get_projector_controller();
    if (*(uint32_t*)(iVar2 + 0x35c) == 0) {
        if (*piVar1 > 0) {
            if (*(volatile uint32_t*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)&rodata_aa891) /*=0xaa891*/, ((unsigned long)&rodata_aae00) /*=0xaae00*/);
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
