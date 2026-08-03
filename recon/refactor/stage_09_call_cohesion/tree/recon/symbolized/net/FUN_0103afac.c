#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103afac @ 0x0103afac
 * public-name: FUN_0103afac
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   virtqueue_add_consumed_buffer            <= FUN_010353ec @ 0x010353ec
 *   thunk_FUN_01036824                       <= FUN_0103aec2 @ 0x0103aec2
 */
/* net-core FUN_0103afac @ 0x103afac */
#include <stdint.h>
extern void FUN_0103aec6(void *);
extern uint32_t FUN_0103ac46(void *, uint32_t);
extern void virtqueue_add_consumed_buffer(void *, uint32_t, uint32_t);
extern void FUN_0103acca(void *);
extern void thunk_FUN_01036824(void *);

void FUN_0103afac(void *object, const uint8_t *record)
{
    uint8_t *base = object;
    uint32_t id = *(const uint32_t *)(record - 8) & 0xffffu;
    void *lock = base + 0x58;
    FUN_0103aec6(lock);
    void *channel = *(void **)(base + 0xa4);
    uint32_t value = FUN_0103ac46(channel, id);
    if (*(uint32_t *)(*(uint8_t **)(base + 0xa0) + 0x18) == 1)
        virtqueue_add_consumed_buffer(channel, id, value);
    FUN_0103acca(channel);
    thunk_FUN_01036824(lock);
}
