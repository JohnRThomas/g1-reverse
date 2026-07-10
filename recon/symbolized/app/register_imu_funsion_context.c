#include "g1_app_symbols.h"
/* named: register_imu_funsion_context */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed register_imu_funsion_context @ 0x26250  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned int register_imu_funsion_context(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    *(unsigned int*)(param_1+0x8c) = ((uintptr_t)&tbl_25f90) /*=0x25fad*/;
    *(unsigned int*)(param_1+0x90) = ((uintptr_t)&tbl_25d0c) /*=0x25df9*/;
    *(unsigned int*)(param_1+0x94) = ((uintptr_t)&tbl_25d0c) /*=0x25dc5*/;
    *(unsigned int*)(param_1+0x98) = ((uintptr_t)&tbl_25d0c) /*=0x25d8d*/;
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 1) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    return 0;
}

