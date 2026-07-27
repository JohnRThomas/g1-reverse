#include "g1_app_symbols.h"
#include <zephyr/sys_clock.h>
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00018d94 @ 0x00018d94
 * public-name: dequeue_ancs
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9aa1f                             @ 0x0009aa1f   [INLINED -- G6 literal batch]
 *   rodata_9b190                             @ 0x0009b190   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_msgq                              @ 0x20006a6c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed dequeue_ancs @ 0x18d94  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(struct k_msgq *, void *, k_timeout_t);
extern void memcpy(int, int, int);
extern void memset_bytes(void*, int, int);

int dequeue_ancs(void *param_1)
{
    unsigned char buf[0x1b4];
    memset_bytes(buf, 0, 0x1b4);

    volatile unsigned char *base = (volatile unsigned char *)((unsigned long)&g_ancs_msgq) /*=0x20006a6c*/;
    if (*(volatile unsigned int *)(base + 0x10) == 0) {
        return 1;
    }

    int iVar1 = k_msgq_get((void *)base, buf, (k_timeout_t){ .ticks = 0LL });
    if (iVar1 == 0) {
        memcpy(param_1, buf, 0x1b4);
    } else if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): D ancs F\n") /*=0x9aa1f*/, ((unsigned long)"dequeue_ancs") /*=0x9b190*/);
        } else {
            debug_print(((unsigned long)"%s(): D ancs F\n") /*=0x9aa1f*/, ((unsigned long)"dequeue_ancs") /*=0x9b190*/);
        }
    }
    return iVar1;
}
