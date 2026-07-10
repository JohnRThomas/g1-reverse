#include "g1_app_symbols.h"
/* named: opt3007_chip_deinit */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed opt3007_chip_deinit @ 0x2e8b4  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(void);
void opt3007_chip_deinit(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    unsigned int v = *(volatile unsigned int*)((uintptr_t)&g_opt3007_dev) /*=0x20007b6c*/;
    if(v != 0){
        param_3 = 0;
        *(volatile unsigned int*)(v + 0x10) = 0;
    }
    if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2){
        if(*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/==0){
            DEBUG_PRINT("%s(): opt3007_chip_deinit done!\n" /*=0xa3cb9*/,"opt3007_chip_deinit" /*=0xa3cda*/,param_3,0,param_4);
        } else {
            debug_print();
        }
    }
    *(volatile unsigned char*)((uintptr_t)&g_opt3007_chip_ready) /*=0x20018da1*/ = 0;
}

