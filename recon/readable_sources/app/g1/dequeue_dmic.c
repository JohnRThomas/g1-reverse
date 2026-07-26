#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0002ed00 @ 0x0002ed00
 * public-name: dequeue_dmic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_885cc                             @ 0x000885cc
 *   rodata_a3f62                             @ 0x000a3f62   [INLINED -- G6 literal batch]
 *   rodata_a41d5                             @ 0x000a41d5   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dmic_msgq                              @ 0x20007b7c
 */
/* Reconstructed dequeue_dmic @ 0x2ed00  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(unsigned int queue, void *record,
                       unsigned int wait, unsigned int flags);
extern void memcpy(void *destination, const void *source,
                        unsigned int length);

int dequeue_dmic(void *param_1)
{
    unsigned char record[204];

    memcpy(record, (const void *)((unsigned long)&rodata_885cc) /*=0x885cc*/, 200);
    int iVar1 = k_msgq_get(((unsigned long)&g_dmic_msgq) /*=0x20007b7c*/, record, 0, 0);
    if (iVar1 == 0) {
        memcpy(param_1, record, 200);
    } else if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): dequeue_dmic failed\r\n\n") /*=0xa3f62*/, ((unsigned long)"dequeue_dmic") /*=0xa41d5*/);
        } else {
            debug_print(((unsigned long)"%s(): dequeue_dmic failed\r\n\n") /*=0xa3f62*/, ((unsigned long)"dequeue_dmic") /*=0xa41d5*/);
        }
    }
    return iVar1;
}
