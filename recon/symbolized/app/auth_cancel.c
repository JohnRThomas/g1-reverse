#include "g1_app_symbols.h"
/* named: auth_cancel */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed auth_cancel @ 0x1849c  (parity: 300/300 trials, PROVEN) */

extern void format_bt_addr_str(void);
extern unsigned int FUN_00081526(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern void FUN_00056a68(void);

void auth_cancel(unsigned int param_1)
{
    unsigned int uVar1 = FUN_00081526();
    (void)uVar1;
    format_bt_addr_str();
    DEBUG_PRINT();
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    FUN_00056a68();
}

