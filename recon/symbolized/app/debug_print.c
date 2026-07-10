#include "g1_app_symbols.h"
/* named: debug_print */
/* globals referenced:
//   0x20007550  g_ring_log_pending           
*/
/* Reconstructed debug_print @ 0x19c70  (parity: 300/300 trials, PROVEN) */

extern unsigned int ancs_get_conn_ctx(void);
extern void memset_bytes(void *dst, int val, unsigned int len);
extern void vsnprintf_impl(void *dst, unsigned int size, unsigned int fmt, unsigned int *args);
extern void enqueue_debug(void *buf);
extern void thunk_FUN_00072880(unsigned int arg);

void debug_print(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char local_e8[200];
    unsigned int stack_args[3];
    stack_args[0] = param_2;
    stack_args[1] = param_3;
    stack_args[2] = param_4;

    unsigned int iVar1 = ancs_get_conn_ctx();

    memset_bytes(local_e8, 0, 200);
    vsnprintf_impl(local_e8, 200, param_1, stack_args);
    enqueue_debug(local_e8);
    local_e8[0] = 0;

    if ((*(volatile unsigned char *)(iVar1 + 0x248) == 0) &&
        (*(volatile unsigned int *)(iVar1 + 0x220) == 0)) {
        *(volatile unsigned int *)((uintptr_t)&g_ring_log_pending) /*=0x20007550*/ = 1;
        thunk_FUN_00072880(iVar1 + 0x218);
    }
}

