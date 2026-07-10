#include "g1_app_symbols.h"
/* named: register_ipc_service_context */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007a84  g_ipc0_endpoint              
*/
/* Reconstructed register_ipc_service_context @ 0x25d40  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(void);
unsigned int register_ipc_service_context(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    *(unsigned int*)(param_1+0x60) = ((uintptr_t)&rodata_25b79) /*=0x25b79*/;
    *(unsigned int*)(param_1+0x64) = ((uintptr_t)&tbl_25ad4) /*=0x25ae9*/;
    *(volatile unsigned int*)((uintptr_t)&g_ipc0_endpoint) /*=0x20007a84*/ = (unsigned int)param_1;
    if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 1){
        if(*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/==0){
            DEBUG_PRINT("%s(): exit\n\n" /*=0x9af2e*/,"register_ipc_service_context" /*=0x9f6c6*/,param_3,0,param_4);
        } else {
            debug_print();
        }
    }
    return 0;
}

