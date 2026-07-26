#include "g1_app_symbols.h"
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
/* Reconstructed enqueue_dmic @ 0x2ec5c  (parity: 300/300 trials, PROVEN) */

extern void memcpy(void*, unsigned int, int);
extern void k_msgq_get(unsigned int, void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void log_message(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, ...);

int enqueue_dmic(unsigned int param_1)
{
    int iVar1;
    unsigned char buf[204];

    memcpy(buf, ((unsigned long)&rodata_885cc) /*=0x885cc*/, 200);
    if (*(volatile int*)(((unsigned long)&g_dmic_msgq) /*=0x20007b7c*/ + 0x24) == 8) {
        k_msgq_get(((unsigned long)&g_dmic_msgq) /*=0x20007b7c*/, buf, 0, 0);
        if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): enqueue_dmic num is full, drop it %d\r\n\n") /*=0xa3f17*/, ((unsigned long)"enqueue_dmic") /*=0xa41e2*/, 8);
            } else {
                debug_print(((unsigned long)"%s(): enqueue_dmic num is full, drop it %d\r\n\n") /*=0xa3f17*/, ((unsigned long)"enqueue_dmic") /*=0xa41e2*/, 8);
            }
        }
    }
    memcpy(buf, param_1, 200);
    iVar1 = k_msgq_put(((unsigned long)&g_dmic_msgq) /*=0x20007b7c*/, buf, 0, 0);
    if ((iVar1 != 0) && (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/)) {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): enqueue_dmic failed\r\n\n") /*=0xa3f45*/, ((unsigned long)"enqueue_dmic") /*=0xa41e2*/);
        } else {
            debug_print(((unsigned long)"%s(): enqueue_dmic failed\r\n\n") /*=0xa3f45*/, ((unsigned long)"enqueue_dmic") /*=0xa41e2*/);
        }
    }
    return iVar1;
}
