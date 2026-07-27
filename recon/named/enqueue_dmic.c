/* readable reconstruction; identity: FUN_0002ec5c @ 0x0002ec5c
 * public-name: enqueue_dmic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_885cc                             @ 0x000885cc
 *   rodata_a3f17                             @ 0x000a3f17   [INLINED -- G6 literal batch]
 *   rodata_a3f45                             @ 0x000a3f45   [INLINED -- G6 literal batch]
 *   rodata_a41e2                             @ 0x000a41e2   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dmic_msgq                              @ 0x20007b7c
 */
#include "../headers/g1_log.h"
/* Reconstructed enqueue_dmic @ 0x2ec5c  (parity: 300/300 trials, PROVEN) */

extern void memcpy(int, int, int);
extern int k_msgq_get(int, unsigned int, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);

int enqueue_dmic(unsigned int param_1)
{
    int iVar1;
    unsigned char buf[204];

    memcpy(buf, 0x885cc, 200);
    if (*(volatile int*)(0x20007b7cUL + 0x24) == 8) {
        k_msgq_get(0x20007b7cUL, buf, 0, 0);
        if (0 < *(volatile int*)0x2000230cUL) {
            if (*(volatile unsigned int*)0x20007554UL == 0) {
                log_message(((unsigned long)"%s(): enqueue_dmic num is full, drop it %d\r\n\n"), ((unsigned long)"enqueue_dmic"), 8);
            } else {
                debug_print(((unsigned long)"%s(): enqueue_dmic num is full, drop it %d\r\n\n"), ((unsigned long)"enqueue_dmic"), 8);
            }
        }
    }
    memcpy(buf, param_1, 200);
    iVar1 = k_msgq_put(0x20007b7cUL, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)0x2000230cUL)) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            log_message(((unsigned long)"%s(): enqueue_dmic failed\r\n\n"), ((unsigned long)"enqueue_dmic"));
        } else {
            debug_print(((unsigned long)"%s(): enqueue_dmic failed\r\n\n"), ((unsigned long)"enqueue_dmic"));
        }
    }
    return iVar1;
}
