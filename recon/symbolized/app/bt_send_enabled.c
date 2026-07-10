#include "g1_app_symbols.h"
/* named: bt_send_enabled */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20006a30  g_ble_conn_ctx_ptr           
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed bt_send_enabled @ 0x17e3c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int, unsigned int, int);
extern void debug_print(void);

void bt_send_enabled(int param_1)
{
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): status:%d\n\n" /*=0x9a143*/, "bt_send_enabled" /*=0x9a2cd*/, param_1);
        } else {
            debug_print();
        }
    }
    int *p = *(int* volatile*)((uintptr_t)&g_ble_conn_ctx_ptr) /*=0x20006a30*/;
    *(volatile unsigned char*)((char*)p + 0x366) = (param_1 == 0);
}

