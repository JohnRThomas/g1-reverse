#include "g1_app_symbols.h"
/* named: enqueue_debug */
/* globals referenced:
//   0x2000751c  g_debug_msg_pipe             
*/
/* Reconstructed enqueue_debug @ 0x19bfc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a);
extern int k_msgq_put(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void k_msgq_get(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void memcpy(unsigned int a, unsigned int b, unsigned int c);

int enqueue_debug(unsigned int param_1)
{
    int iVar1;
    if (*(volatile int*)(((uintptr_t)&g_debug_msg_pipe) /*=0x2000751c*/ + 0x24) == 0x14) {
        k_msgq_get(((uintptr_t)&g_debug_msg_pipe) /*=0x2000751c*/, (g_debug_msg_scratch_buf) /*=0x20010257*/, 0, 0);
    }
    memcpy((g_debug_msg_scratch_buf) /*=0x20010257*/, param_1, 200);
    iVar1 = k_msgq_put(((uintptr_t)&g_debug_msg_pipe) /*=0x2000751c*/, (g_debug_msg_scratch_buf) /*=0x20010257*/, 0, 0);
    if (iVar1 != 0) {
        DEBUG_PRINT("enqueue_debug failed\r\n" /*=0x9b35a*/);
    }
    return iVar1;
}

