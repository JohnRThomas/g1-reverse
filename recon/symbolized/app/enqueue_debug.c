#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00019bfc @ 0x00019bfc
 * public-name: enqueue_debug
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   enqueue_debug                            <= FUN_00019bfc @ 0x00019bfc
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_9b35a                             @ 0x0009b35a   [INLINED -- G6 literal batch]
 *   g_debug_msg_pipe                         @ 0x2000751c
 *   g_debug_msg_scratch_buf                  @ 0x20010257
 */
/* Reconstructed FUN_00019bfc @ 0x19bfc  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_put(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void k_msgq_get(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void memcpy(unsigned int a, unsigned int b, unsigned int c);

int enqueue_debug(unsigned int param_1)
{
    int iVar1;
    if (*(volatile int*)(((unsigned long)&g_debug_msg_pipe) /*=0x2000751c*/ + 0x24) == 0x14) {
        k_msgq_get(((unsigned long)&g_debug_msg_pipe) /*=0x2000751c*/, ((unsigned long)g_debug_msg_scratch_buf) /*=0x20010257*/, 0, 0);
    }
    memcpy(((unsigned long)g_debug_msg_scratch_buf) /*=0x20010257*/, param_1, 200);
    iVar1 = k_msgq_put(((unsigned long)&g_debug_msg_pipe) /*=0x2000751c*/, ((unsigned long)g_debug_msg_scratch_buf) /*=0x20010257*/, 0, 0);
    if (iVar1 != 0) {
        log_message(((unsigned long)"enqueue_debug failed\r\n") /*=0x9b35a*/);
    }
    return iVar1;
}
