#include "g1_app_symbols.h"
/* named: check_bonded_addr */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006ab8  g_ancs_active_conn           
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed check_bonded_addr @ 0x183e4  (parity: 300/300 trials, PROVEN) */

extern void format_bt_addr_str(void);
extern void DEBUG_PRINT(void);
extern void debug_print(void);

void check_bonded_addr(unsigned int param_1)
{
    format_bt_addr_str();
    unsigned int *cnt = (unsigned int*)((uintptr_t)&g_bonded_count) /*=0x20007514*/;
    *cnt = *cnt + 1;
    unsigned int ptr = *(volatile unsigned int*)((uintptr_t)&g_ancs_active_conn) /*=0x20006ab8*/;
    *(volatile unsigned char*)(ptr + 0x367) = 0;
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
}

