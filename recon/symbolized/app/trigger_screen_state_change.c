#include "g1_app_symbols.h"
/* named: trigger_screen_state_change */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed trigger_screen_state_change @ 0x2bc2c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072880(unsigned int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int);

unsigned int trigger_screen_state_change(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    if ((unsigned int)(*(volatile unsigned char*)(param_2 + 0xfe8)) == param_3) {
        if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): %s: ignore:%d.\n" /*=0xa2470*/, "trigger_screen_state_change" /*=0xa254a*/, param_1, *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            } else {
                debug_print("%s(): %s: ignore:%d.\n" /*=0xa2470*/, "trigger_screen_state_change" /*=0xa254a*/, param_1);
            }
        }
        param_3 = 0xffffffff;
    } else {
        if (param_3 == 0) {
            *(volatile unsigned char*)(param_2 + 0xfe8) = 0;
        } else {
            *(volatile unsigned char*)(param_2 + 0xfe8) = 1;
            FUN_00072880(param_2 + 0x50);
        }
        if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): %s: trigger_on_screen -> %d\n" /*=0xa2486*/, "trigger_screen_state_change" /*=0xa254a*/, param_1, *(volatile unsigned char*)(param_2 + 0xfe8), param_4);
            } else {
                debug_print("%s(): %s: trigger_on_screen -> %d\n" /*=0xa2486*/, "trigger_screen_state_change" /*=0xa254a*/, param_1);
            }
        }
    }
    return param_3;
}

