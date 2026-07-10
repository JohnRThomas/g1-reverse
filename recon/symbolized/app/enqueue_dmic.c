#include "g1_app_symbols.h"
/* named: enqueue_dmic */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007b7c  g_dmic_msgq                  
*/
/* Reconstructed enqueue_dmic @ 0x2ec5c  (parity: 300/300 trials, PROVEN) */

extern void memcpy(void*, unsigned int, int);
extern void k_msgq_get(unsigned int, void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

int enqueue_dmic(unsigned int param_1)
{
    int iVar1;
    unsigned char buf[204];

    memcpy(buf, ((uintptr_t)&tbl_88340) /*=0x885cc*/, 200);
    if (*(volatile int*)(((uintptr_t)&g_dmic_msgq) /*=0x20007b7c*/ + 0x24) == 8) {
        k_msgq_get(((uintptr_t)&g_dmic_msgq) /*=0x20007b7c*/, buf, 0, 0);
        if (0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): enqueue_dmic num is full, drop it %d\r\n\n" /*=0xa3f17*/, "enqueue_dmic" /*=0xa41e2*/, 8);
            } else {
                debug_print();
            }
        }
    }
    memcpy(buf, param_1, 200);
    iVar1 = k_msgq_put(((uintptr_t)&g_dmic_msgq) /*=0x20007b7c*/, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/)) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): enqueue_dmic failed\r\n\n" /*=0xa3f45*/, "enqueue_dmic" /*=0xa41e2*/);
        } else {
            debug_print();
        }
    }
    return iVar1;
}

