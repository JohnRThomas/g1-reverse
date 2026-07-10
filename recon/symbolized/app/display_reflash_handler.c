#include "g1_app_symbols.h"
/* named: display_reflash_handler */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed display_reflash_handler @ 0x48e28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern void ui_refalsh_warp(void);

unsigned display_reflash_handler(unsigned param_1, unsigned param_2, unsigned param_3, int param_4)
{
    volatile int *piVar3 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    volatile int *piVar2 = (volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    unsigned uVar4 = *(volatile uint8_t*)((uintptr_t)&g_display_last_reflash_id) /*=0x2001d448*/;

    if (param_4 == 2) {
        if (param_2 != uVar4 && uVar4 != 0) {
            if (0 < *piVar3) {
                if (*piVar2 == 0) DEBUG_PRINT(); else debug_print();
                if (0 < *piVar3) {
                    if (*piVar2 == 0) DEBUG_PRINT(); else debug_print();
                    if (0 < *piVar3) {
                        if (*piVar2 == 0) DEBUG_PRINT(); else debug_print();
                    }
                }
            }
            ui_refalsh_warp();
            return 0xffffffff;
        }
    } else if (param_4 == 1) {
        if (param_2 != uVar4 && uVar4 != 0) {
            if (0 < *piVar3) {
                if (*piVar2 == 0) DEBUG_PRINT(); else debug_print();
                if (0 < *piVar3) {
                    if (*piVar2 == 0) DEBUG_PRINT(); else debug_print();
                    if (0 < *piVar3) {
                        if (*piVar2 == 0) DEBUG_PRINT(); else debug_print();
                    }
                }
            }
            ui_refalsh_warp();
            if (0 < *piVar3) {
                if (*piVar2 == 0) DEBUG_PRINT(); else debug_print();
            }
            *(volatile uint8_t*)((uintptr_t)&g_display_last_reflash_id) /*=0x2001d448*/ = (uint8_t)param_2;
        }
    } else {
        if (param_2 != uVar4 && 0 < *piVar3) {
            if (*piVar2 == 0) DEBUG_PRINT(); else debug_print();
            if (0 < *piVar3) {
                if (*piVar2 == 0) DEBUG_PRINT(); else debug_print();
            }
        }
    }
    ui_refalsh_warp();
    return 0;
}

