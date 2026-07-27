#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085a9c @ 0x00085a9c
 * public-name: virtqueue_return_rx_buffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   virtqueue_add_buffer                     <= FUN_0008567c @ 0x0008567c
 *   virtqueue_get_buffer_length              <= FUN_000857a8 @ 0x000857a8
 *   dma_xfer_end_handler                     <= FUN_000857e0 @ 0x000857e0
 *   mutex_lock_wait_forever_dup              <= FUN_000859b6 @ 0x000859b6
 *   virtqueue_return_rx_buffer               <= FUN_00085a9c @ 0x00085a9c
 */
/* Reconstructed FUN_00085a9c @ 0x85a9c (exact 82-byte extent). */
#include <stdint.h>

extern void mutex_lock_wait_forever_dup(unsigned int, unsigned int);
extern uint32_t virtqueue_get_buffer_length(uint32_t object, uint32_t tag);
extern void virtqueue_add_buffer(uint32_t object, uint32_t item[2], uint32_t zero,
                         uint32_t one);
extern uint64_t dma_xfer_end_handler(uint32_t object);
extern int FUN_000859b2(void *lock, uint32_t inherited_r1, uint32_t zero,
                        uint32_t one);

int virtqueue_return_rx_buffer(uint8_t *context, uint8_t *record)
{
    uint32_t tag = *(uint32_t *)(record - 8) & 0xffffu;
    void *lock = context + 0x58;
    mutex_lock_wait_forever_dup(lock, record);

    uint32_t object = *(uint32_t *)(context + 0xa4);
    uint32_t result = virtqueue_get_buffer_length(object, tag);
    uint32_t item[2] = {(uint32_t)(uintptr_t)(record - 0x10), result};
    if (*(uint32_t *)(*(uint32_t *)(context + 0xa0) + 0x18) == 0)
        virtqueue_add_buffer(object, item, 0, 1);

    uint64_t inherited = dma_xfer_end_handler(object);
    return FUN_000859b2(lock, (uint32_t)(inherited >> 32), 0, 1);
}
