#include "g1_app_symbols.h"
/* named: setDelayExitValue */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x2000a094  g_delay_exit_value           [g_obj_2000a018.f_7c]
*/
/* Reconstructed setDelayExitValue @ 0x49000  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int);
extern void debug_print(void);
unsigned int setDelayExitValue(unsigned int param_1){
    if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2){
        if(*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/==0){
            DEBUG_PRINT("%s(): set delay exit time = %d\n" /*=0xefb0e*/,"setDelayExitValue" /*=0xf01c1*/,param_1);
        } else {
            debug_print();
        }
    }
    *(volatile unsigned int*)((uintptr_t)&g_delayexitvalue) /*=0x2000a094*/ = param_1;
    return 0;
}

