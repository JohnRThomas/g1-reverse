#include "g1_app_symbols.h"
/* named: global_system_suspend */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed global_system_suspend @ 0x2bd7c  (parity: 296/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int fmt, unsigned int a1, unsigned int a2, unsigned int a3);
extern void debug_print(void);
typedef void (*fn2_t)(unsigned int);

unsigned int global_system_suspend(void *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned char *base = (volatile unsigned char *)param_1;
    if ((*(base + 0xfe6) & 0xfb) == 0) {
        *(base + 0xfe6) = 2;
        if (*(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 1) {
            if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): begin.\n" /*=0xa24eb*/, "global_system_suspend" /*=0xa251a*/, param_3, 0U);
            } else {
                debug_print();
            }
        }
        fn2_t fn = *(fn2_t *)(base + 0xb70);
        fn((unsigned int)((unsigned char *)param_1 + 0xb6c));
        if (*(volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 1) {
            if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): end.\n" /*=0xa24f9*/, "global_system_suspend" /*=0xa251a*/, param_3, 0U);
            } else {
                debug_print();
            }
        }
        *(base + 0xfe6) = 1;
    }
    return 0;
}

