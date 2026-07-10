#include "g1_app_symbols.h"
/* named: clean_dmic_msgq */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007b7c  g_dmic_msgq                  
*/
/* Reconstructed clean_dmic_msgq @ 0x2ec1c  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_cleanup(unsigned int);
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(void);
int clean_dmic_msgq(void){
    int iVar1 = k_msgq_cleanup(((uintptr_t)&g_dmic_msgq) /*=0x20007b7c*/);
    if(iVar1!=0 && *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0){
        if(*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/==0){
            DEBUG_PRINT("%s(): dmic cleanup failed\n" /*=0xa3efc*/,"clean_dmic_msgq" /*=0xa41ef*/);
        } else {
            debug_print();
        }
    }
    return iVar1;
}

