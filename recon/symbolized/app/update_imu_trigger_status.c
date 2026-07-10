#include "g1_app_symbols.h"
/* named: update_imu_trigger_status */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed update_imu_trigger_status @ 0x2bcbc  (parity: 300/300 trials, PROVEN) */

extern void FUN_00072880(unsigned int);
extern void DEBUG_PRINT(unsigned int, unsigned int, unsigned int, unsigned int);
extern void debug_print(unsigned int, unsigned int, unsigned int, unsigned int);

unsigned int update_imu_trigger_status(unsigned int param_1, int param_2, int param_3)
{
    unsigned int uVar2;

    if (*(volatile int*)(param_2 + 0xee8) == param_3) {
        uVar2 = 0xffffffff;
    } else {
        *(volatile int*)(param_2 + 0xee8) = param_3;
        if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): %s new status: %d\n\n" /*=0xa24a9*/, "update_imu_trigger_status" /*=0xa2530*/, param_1, param_3);
            } else {
                debug_print("%s(): %s new status: %d\n\n" /*=0xa24a9*/, "update_imu_trigger_status" /*=0xa2530*/, param_1, param_3);
            }
        }
        if ((*(volatile unsigned char*)(param_2 + 0xfea) == 0xa) && (param_3 != 0) &&
            (*(volatile unsigned char*)(param_2 + 0xb0c) == 0)) {
            if (2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
                if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT("%s(): imu wakeup thd-> \n" /*=0xa24c3*/, "update_imu_trigger_status" /*=0xa2530*/, 0, 0);
                } else {
                    debug_print("%s(): imu wakeup thd-> \n" /*=0xa24c3*/, "update_imu_trigger_status" /*=0xa2530*/, 0, 0);
                }
            }
            *(volatile unsigned char*)(param_2 + 0xfe9) = 1;
            FUN_00072880(param_2 + 0xaf4);
        }
        uVar2 = 0;
    }
    return uVar2;
}

