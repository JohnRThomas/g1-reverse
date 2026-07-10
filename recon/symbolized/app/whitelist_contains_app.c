#include "g1_app_symbols.h"
/* named: whitelist_contains_app */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
//   0x2001a22c  g_app_whitelist_buffer       
*/
/* Reconstructed whitelist_contains_app @ 0x34ff0  (parity: 300/300 trials, PROVEN) */

extern void debug_print(void);
extern void log_message(int a);
extern int strncmp(int a, int b, int c);

unsigned int whitelist_contains_app(int param_1, int param_2)
{
    int iVar1, iVar2, iVar3;

    if (param_1 == 0 || param_2 == 0) {
        if (*(volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message("invalid param ! \n" /*=0xa8750*/);
        } else {
            debug_print();
        }
    } else {
        iVar3 = (g_app_whitelist_buffer) /*=0x2001a22c*/ + (unsigned int)(*(volatile unsigned char *)((uintptr_t)&g_on_whitelist_by_identifier) /*=0x2001a22d*/) * 0x38;
        for (iVar2 = (g_app_whitelist_buffer) /*=0x2001a22c*/; iVar2 != iVar3; iVar2 += 0x38) {
            iVar1 = strncmp(iVar2 + 2, param_1, 0x28);
            if (iVar1 == 0 && (iVar1 = strncmp(iVar2 + 0x2a, param_2, 0x10), iVar1 == 0)) {
                return 1;
            }
        }
    }
    return 0;
}

