#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102ff94 @ 0x0102ff94
 * public-name: FUN_0102ff94
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103de3f                           @ 0x0103de3f
 */
/* net-core chained pool-buffer release @ 0x0102ff94.
 * Raw/address back-map: FUN_0102ff94 / 0x0102ff94.
 */
#include <stdint.h>

extern void assert_print(const void *, const void *, uint32_t);
extern void assert_post_action(const void *, uint32_t);
extern void FUN_0103b210(void *, void *);

typedef void (*release_fn_t)(void *);

void FUN_0102ff94(uint8_t *buffer)
{
    if (buffer == 0) {
        assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                     (const void *)((unsigned long)&rodata_103de3f) /*=0x103de3f*/, 0x1d3);
        assert_post_action((const void *)((unsigned long)&rodata_103de3f) /*=0x103de3f*/, 0x1d3);
    }
    do {
        uint8_t *next = *(uint8_t **)(buffer + 4);
        uint8_t refs = (uint8_t)(buffer[8] - 1u);
        buffer[8] = refs;
        if (refs != 0)
            return;

        if (*(uint32_t *)(buffer + 0x14) != 0) {
            if ((buffer[9] & 1u) == 0) {
                uint8_t *pool = (uint8_t *)0x21000994u +
                                (uint32_t)buffer[10] * 0x34u;
                void **owner = *(void ***)(pool + 0x2c);
                ((release_fn_t)owner[2])(buffer);
            }
            *(uint32_t *)(buffer + 0x14) = 0;
        }
        *(uint32_t *)(buffer + 0x0c) = 0;
        uint8_t *pool = (uint8_t *)0x21000994u +
                        (uint32_t)buffer[10] * 0x34u;
        *(uint32_t *)(buffer + 4) = 0;
        release_fn_t release = *(release_fn_t *)(pool + 0x28);
        if (release != 0)
            release(buffer);
        else
            FUN_0103b210(pool, buffer);
        buffer = next;
    } while (buffer != 0);
}
