/* readable reconstruction; identity: FUN_000710b4 @ 0x000710b4
 * public-name: rpmsg_virtio_tx_enqueue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rpmsg_virtio_tx_enqueue                  <= FUN_000710b4 @ 0x000710b4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   metal_io_block_write                     <= FUN_00085508 @ 0x00085508
 *   virtqueue_add_buffer                     <= FUN_0008567c @ 0x0008567c
 *   virtqueue_get_buffer_length              <= FUN_000857a8 @ 0x000857a8
 *   dma_xfer_end_handler                     <= FUN_000857e0 @ 0x000857e0
 *   mutex_lock_wait_forever_dup              <= FUN_000859b6 @ 0x000859b6
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f7ba6                             @ 0x000f7ba6
 *   rodata_f7be9                             @ 0x000f7be9
 *   rodata_f7c02                             @ 0x000f7c02
 */
/* Reconstructed FUN_000710b4 @ 0x710b4 */
#include <stdint.h>
#include "../headers/g1_log.h"

extern int metal_io_block_write(int*, unsigned int, int, int);
extern void mutex_lock_wait_forever_dup(void *);
extern void FUN_000859b2(void *);
extern unsigned long virtqueue_get_buffer_length(unsigned long, unsigned long);
extern int virtqueue_add_buffer(void *, const void *, int, int, void *);
extern void dma_xfer_end_handler(int*);
extern int assert_post_action(int, int);

uint32_t rpmsg_virtio_tx_enqueue(uint8_t *owner, uint32_t a, uint32_t b,
                      uint8_t *item_end, uint32_t tag)
{
    uint8_t *item = item_end - 16;
    uint16_t id = *(uint32_t *)(item_end - 8);
    uint32_t *pool = *(uint32_t **)(owner + 0xac);
    uint32_t offset = (uint32_t)(uintptr_t)item - pool[0];
    struct { uint32_t a, b, zero; uint16_t tag, pad; } key = {a, b, 0, (uint16_t)tag, 0};
    if (offset >= pool[2]) offset = UINT32_MAX;
    if (metal_io_block_write(pool, offset, &key, 16) != 16) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f7be9, 0x000f7ba6, 0x1af);
        assert_post_action(0x000f7ba6, 0x1af);
    }
    void *lock = owner + 0x58;
    mutex_lock_wait_forever_dup(lock);
    uint32_t value;
    if (*(uint32_t *)(*(uint8_t **)(owner + 0xa0) + 0x18) == 0) {
        value = *(uint32_t *)(owner + 0x94);
    } else {
        value = virtqueue_get_buffer_length(*(void **)(owner + 0xa8), id);
        if (*(uint32_t *)(*(uint8_t **)(owner + 0xa0) + 0x18) != 0) goto done;
    }
    struct { void *item; uint32_t value; } entry = {item, value};
    if (virtqueue_add_buffer(*(void **)(owner + 0xa8), &entry, 1, 0, item) != 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f7c02, 0x000f7ba6, 0x1bc);
        assert_post_action(0x000f7ba6, 0x1bc);
    }
done:
    dma_xfer_end_handler(*(void **)(owner + 0xa8));
    FUN_000859b2(lock);
    return tag;
}
