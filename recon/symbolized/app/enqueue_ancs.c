#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00018bb4 @ 0x00018bb4
 * public-name: enqueue_ancs
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9a964                             @ 0x0009a964   [INLINED -- G6 literal batch]
 *   rodata_9a981                             @ 0x0009a981   [INLINED -- G6 literal batch]
 *   rodata_9b19d                             @ 0x0009b19d   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_msgq                              @ 0x20006a6c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed enqueue_ancs @ 0x18bb4  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
extern void k_msgq_get(unsigned int, void*, int, int);
extern void memcpy(void*, unsigned int, int);
extern int k_msgq_put(unsigned int, void*, int, int);

int enqueue_ancs(unsigned int param_1)
{
    int iVar1;
    unsigned char buf[436];

    memset_bytes(buf, 0, 0x1b4);
    if (*(volatile int*)(((unsigned long)&g_ancs_msgq) /*=0x20006a6c*/ + 0x10) == 0) {
        iVar1 = 1;
    } else {
        if (*(volatile int*)(((unsigned long)&g_ancs_msgq) /*=0x20006a6c*/ + 0x24) == 10) {
            k_msgq_get(((unsigned long)&g_ancs_msgq) /*=0x20006a6c*/, buf, 0, 0);
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"enqueue ancs drop package! \n") /*=0x9a964*/);
            } else {
                debug_print(((unsigned long)"enqueue ancs drop package! \n") /*=0x9a964*/);
            }
        }
        memcpy(buf, param_1, 0x1b4);
        iVar1 = k_msgq_put(((unsigned long)&g_ancs_msgq) /*=0x20006a6c*/, buf, 0, 0);
        if ((iVar1 != 0) && (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): en ancs F\n") /*=0x9a981*/, ((unsigned long)"enqueue_ancs") /*=0x9b19d*/);
            } else {
                debug_print(((unsigned long)"%s(): en ancs F\n") /*=0x9a981*/, ((unsigned long)"enqueue_ancs") /*=0x9b19d*/);
            }
        }
    }
    return iVar1;
}
