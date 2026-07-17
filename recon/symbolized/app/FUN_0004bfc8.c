#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004bfc8 @ 0x0004bfc8
 * public-name: FUN_0004bfc8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   idx_inc                                  <= FUN_0007e35c @ 0x0007e35c
 *   rd_idx_inc                               <= FUN_0007e378 @ 0x0007e378
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 */
/* Reconstructed FUN_0004bfc8 @ 0x4bfc8 (NCS mpsc_pbuf_free)
 * Code ends at 0x4c08f; six literals occupy 0x4c090..0x4c0a7.
 * Structured callback/index parity: PASS 40/40. */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

struct mpsc_buffer {
    uint32_t tmp_wr_idx;
    uint32_t wr_idx;
    uint32_t tmp_rd_idx;
    uint32_t rd_idx;
    uint32_t flags;
    uint32_t lock;
    void (*notify_drop)(void *, void *);
    uint32_t (*get_wlen)(void *);
    volatile uint32_t *buf;
    uint32_t size;
    uint32_t max_usage;
    uint8_t sem[0x10];
};

extern int z_spin_lock_valid(void *lock);
extern int z_spin_unlock_valid(void *lock);
extern void z_spin_lock_set_owner(void *lock);
extern void printk(uint32_t, ...);
extern void assert_post_action(uint32_t, uint32_t);
extern uint32_t idx_inc(struct mpsc_buffer *, uint32_t, uint32_t);
extern void rd_idx_inc(struct mpsc_buffer *, uint32_t);
extern void FUN_00072880(void *sem);

void FUN_0004bfc8(struct mpsc_buffer *buffer, volatile uint32_t *item)
{
    uint32_t words = buffer->get_wlen((void *)item);
    void *lock = &buffer->lock;
    uint32_t key = __get_BASEPRI();

    __set_BASEPRI_MAX(0x20);
    __ISB();
    if (!z_spin_lock_valid(lock)) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0920) /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
        printk(((unsigned long)&rodata_f0935) /*=0xf0935*/, lock);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
        return;
    }
    z_spin_lock_set_owner(lock);

    *(volatile uint8_t *)item &= (uint8_t)~1u;
    if ((buffer->flags & 2u) != 0 &&
        item != buffer->buf + buffer->rd_idx) {
        *item = (*item & 3u) | (words << 2);
    } else {
        *(volatile uint8_t *)item &= (uint8_t)~2u;
        if (buffer->rd_idx == buffer->tmp_rd_idx)
            buffer->tmp_rd_idx =
                idx_inc(buffer, buffer->tmp_rd_idx, words);
    }
    rd_idx_inc(buffer, words);

    if (!z_spin_unlock_valid(lock)) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f08f4) /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
        printk(((unsigned long)&rodata_f090b) /*=0xf090b*/, lock);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
        return;
    }
    __set_BASEPRI(key);
    __ISB();
    return FUN_00072880(buffer->sem);
}
