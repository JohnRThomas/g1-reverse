#include "g1_app_symbols.h"
/* named: dequeue_dmic */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed dequeue_dmic @ 0x2ed00  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern int k_msgq_get(void);
extern void memcpy(void);

int dequeue_dmic(unsigned int param_1)
{
    memcpy();
    int iVar1 = k_msgq_get();
    if (iVar1 == 0) {
        memcpy();
    } else if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    return iVar1;
}

