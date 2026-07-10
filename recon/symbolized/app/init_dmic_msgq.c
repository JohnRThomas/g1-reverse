#include "g1_app_symbols.h"
/* named: init_dmic_msgq */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007b7c  g_dmic_msgq                  
*/
/* Reconstructed init_dmic_msgq @ 0x2ebd8  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(unsigned int,int,int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(void);
int init_dmic_msgq(void){
    int iVar1 = z_impl_k_msgq_alloc_init(((uintptr_t)&g_dmic_msgq) /*=0x20007b7c*/,200,8);
    if(iVar1!=0 && *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/>0){
        if(*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/==0){
            DEBUG_PRINT("%s(): dmic init failed\n" /*=0xa3ee4*/,"init_dmic_msgq" /*=0xa41ff*/);
        } else { debug_print(); }
    }
    return iVar1;
}

