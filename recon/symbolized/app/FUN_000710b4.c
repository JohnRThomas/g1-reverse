#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000710b4 @ 0x000710b4
 * public-name: FUN_000710b4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   metal_io_block_write                     <= FUN_00085508 @ 0x00085508
 *   virtqueue_add_buffer                     <= FUN_0008567c @ 0x0008567c
 *   virtqueue_get_buffer_length              <= FUN_000857a8 @ 0x000857a8
 *   mutex_lock_wait_forever_dup              <= FUN_000859b6 @ 0x000859b6
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f7ba6                             @ 0x000f7ba6
 *   rodata_f7be9                             @ 0x000f7be9
 *   rodata_f7c02                             @ 0x000f7c02
 */
/* Reconstructed FUN_000710b4 @ 0x710b4 */
#include <stdint.h>

extern int metal_io_block_write(void *, uint32_t, const void *, uint32_t);
extern void mutex_lock_wait_forever_dup(void *);
extern void FUN_000859b2(void *);
extern uint32_t virtqueue_get_buffer_length(void *, uint16_t);
extern int virtqueue_add_buffer(void *, const void *, int, int, void *);
extern void FUN_000857e0(void *);
extern void printk(uint32_t, ...);
extern void assert_post_action(uint32_t, uint32_t);

uint32_t FUN_000710b4(uint8_t *owner, uint32_t a, uint32_t b,
                      uint8_t *item_end, uint32_t tag)
{
    uint8_t *item = item_end - 16;
    uint16_t id = *(uint32_t *)(item_end - 8);
    uint32_t *pool = *(uint32_t **)(owner + 0xac);
    uint32_t offset = (uint32_t)(uintptr_t)item - pool[0];
    struct { uint32_t a, b, zero; uint16_t tag, pad; } key = {a, b, 0, (uint16_t)tag, 0};
    if (offset >= pool[2]) offset = UINT32_MAX;
    if (metal_io_block_write(pool, offset, &key, 16) != 16) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f7be9) /*=0xf7be9*/, ((unsigned long)&rodata_f7ba6) /*=0xf7ba6*/, 0x1af);
        assert_post_action(((unsigned long)&rodata_f7ba6) /*=0xf7ba6*/, 0x1af);
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
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f7c02) /*=0xf7c02*/, ((unsigned long)&rodata_f7ba6) /*=0xf7ba6*/, 0x1bc);
        assert_post_action(((unsigned long)&rodata_f7ba6) /*=0xf7ba6*/, 0x1bc);
    }
done:
    FUN_000857e0(*(void **)(owner + 0xa8));
    FUN_000859b2(lock);
    return tag;
}
