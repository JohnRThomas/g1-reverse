#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002692c @ 0x0002692c
 * public-name: master_display_thread
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_99969                             @ 0x00099969
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed master_display_thread @ 0x0002692c; raw identity FUN_0002692c.
 * Exact executable extent: 0x0002692c..0x000269dd (0xb2 bytes); 0x269de is
 * alignment and the literal pool starts at 0x269e0. CFG_VERIFY_PREFIX_FIRST
 */
#include <stdint.h>
#include "../../headers/g1_log.h"

/* FUN_00019c70 @ 0x00019c70 */
extern void *memset_bytes(void *, int, uint32_t); /* FUN_00086c78 */
extern int32_t k_msleep(int32_t);                   /* FUN_0007cb8e */
extern void wait_for_event(uint32_t, uint32_t);   /* FUN_0007cb8a */
extern void process_for_new_task(void *, void *); /* FUN_0002c99c */
extern uint8_t *get_device_info(void);            /* FUN_000167a8 */

void master_display_thread(uint8_t *context)
{
    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)&rodata_99969) /*=0x99969*/, 0x000a1a2bu);
        else
            debug_print(((unsigned long)&rodata_99969) /*=0x99969*/, 0x000a1a2bu);
    }

    uint8_t *buffers = context + 0x1000;
    volatile uint8_t *event = *(uint8_t **)(buffers + 0x54);
    *(volatile uint32_t *)event = 0;
    event[4] = 0;
    memset_bytes(*(void **)(context + 0x0ffc), 0, 0x217);
    memset_bytes(*(void **)(buffers + 0x00), 0, 0x0f5);
    memset_bytes(*(void **)(buffers + 0x04), 0, 0x198);
    memset_bytes(*(void **)(buffers + 0x08), 0, 0x198);
    memset_bytes(*(void **)(buffers + 0x0c), 0, 0x199);
    memset_bytes(*(void **)(context + 0x0ff8), 0, 0x0af);

    while ((*(volatile uint16_t *)(buffers + 0x5c) & 0x80u) == 0)
        k_msleep(1000);

    for (;;) {
        process_for_new_task(context, context + 0x0ee4);
        while (context[1] != 1 && get_device_info()[1] != 8)
            k_msleep(25);
        do {
            wait_for_event(((unsigned long)&rodata_28000) /*=0x28000*/, 0);
        } while (context[1] == 1 || get_device_info()[1] == 8);
    }
}
