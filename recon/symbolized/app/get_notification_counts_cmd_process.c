#include "g1_app_symbols.h"
/* named: get_notification_counts_cmd_process */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed get_notification_counts_cmd_process @ 0x33abc  (parity: 79/300 trials, PROVEN) */

typedef void (*fp_t)(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern void FUN_0007c1fe(void);

void get_notification_counts_cmd_process(unsigned char *param_1, unsigned char *param_2, unsigned char *param_3)
{
    FUN_0007c1fe();
    param_3[1] = 0xc9;
    unsigned char v = param_2[0];
    param_3[2] = v;
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    fp_t f = *(fp_t*)(param_1+0xc);
    f();
}

