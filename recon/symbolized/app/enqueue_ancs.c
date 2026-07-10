#include "g1_app_symbols.h"
/* named: enqueue_ancs */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006a6c  g_ancs_msgq                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed enqueue_ancs @ 0x18bb4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern void k_msgq_get(unsigned int, void*, int, int);
extern void memcpy(void*, unsigned int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

int enqueue_ancs(unsigned int param_1)
{
    int iVar1;
    unsigned char buf[436];

    memset_bytes(buf, 0, 0x1b4);
    if (*(volatile int*)(((uintptr_t)&g_ancs_msgq) /*=0x20006a6c*/ + 0x10) == 0) {
        iVar1 = 1;
    } else {
        if (*(volatile int*)(((uintptr_t)&g_ancs_msgq) /*=0x20006a6c*/ + 0x24) == 10) {
            k_msgq_get(((uintptr_t)&g_ancs_msgq) /*=0x20006a6c*/, buf, 0, 0);
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("enqueue ancs drop package! \n" /*=0x9a964*/, 0, 0);
            } else {
                debug_print();
            }
        }
        memcpy(buf, param_1, 0x1b4);
        iVar1 = k_msgq_put(((uintptr_t)&g_ancs_msgq) /*=0x20006a6c*/, buf, 0, 0);
        if ((iVar1 != 0) && (0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/)) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): en ancs F\n" /*=0x9a981*/, "enqueue_ancs" /*=0x9b19d*/);
            } else {
                debug_print();
            }
        }
    }
    return iVar1;
}

