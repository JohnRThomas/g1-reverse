/* readable reconstruction; identity: FUN_0004bfc8 @ 0x0004bfc8
 * public-name: mpsc_pbuf_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   idx_inc                                  <= FUN_0007e35c @ 0x0007e35c
 *   rd_idx_inc                               <= FUN_0007e378 @ 0x0007e378
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 */
/* Reconstructed mpsc_pbuf_free @ 0x0004bfc8.
 *
 * Exact NCS 2.5.1 Zephyr lib/os/mpsc_pbuf.c implementation.  Readable names
 * retain reversible raw provenance:
 *   mpsc_pbuf_free        <= FUN_0004bfc8 @ 0x0004bfc8
 *   z_spin_lock_valid     <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid   <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner <= FUN_00072078 @ 0x00072078
 *   k_sem_give            <= FUN_00072880 @ 0x00072880
 *   printk                <= FUN_0007e2fa @ 0x0007e2fa
 *   assert_post_action    <= FUN_0007e2ec @ 0x0007e2ec
 *   idx_inc               <= FUN_0007e35c @ 0x0007e35c
 *   rd_idx_inc            <= FUN_0007e378 @ 0x0007e378
 *
 * Executable ownership is [0x0004bfc8, 0x0004c090), size 0xc8.  The final
 * instruction tail-branches to k_sem_give at 0x4c08c; six assertion literals
 * occupy 0x4c090..0x4c0a7 and the next independent body starts at 0x4c0a8.
 */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../headers/g1_log.h"

#define z_spin_lock_valid     z_spin_lock_valid
#define z_spin_unlock_valid   z_spin_unlock_valid
#define z_spin_lock_set_owner z_spin_lock_set_owner
#define k_sem_give            k_sem_give
#define printk                printk
#define assert_post_action    assert_post_action
#define idx_inc               idx_inc
#define rd_idx_inc            rd_idx_inc

struct mpsc_pbuf_buffer {
    uint32_t tmp_wr_idx;                         /* +0x00 */
    uint32_t wr_idx;                             /* +0x04 */
    uint32_t tmp_rd_idx;                         /* +0x08 */
    uint32_t rd_idx;                             /* +0x0c */
    uint32_t flags;                              /* +0x10 */
    uint32_t lock;                               /* +0x14 */
    void (*notify_drop)(void *, const void *);   /* +0x18 */
    uint32_t (*get_wlen)(const void *);          /* +0x1c */
    volatile uint32_t *buf;                      /* +0x20 */
    uint32_t size;                               /* +0x24 */
    uint32_t max_usage;                          /* +0x28 */
    uint8_t sem[0x10];                           /* +0x2c */
};

extern int z_spin_lock_valid(void *lock);
extern int z_spin_unlock_valid(void *lock);
extern void z_spin_lock_set_owner(void *lock);
extern void k_sem_give(void *sem);
extern void assert_post_action(uint32_t file, uint32_t line);
extern uint32_t idx_inc(struct mpsc_pbuf_buffer *buffer,
                        uint32_t index, uint32_t words);
extern void rd_idx_inc(struct mpsc_pbuf_buffer *buffer, uint32_t words);

void mpsc_pbuf_free(struct mpsc_pbuf_buffer *buffer,
                    volatile uint32_t *item)
{
    uint32_t words = buffer->get_wlen((const void *)item);
    void *lock = &buffer->lock;
    uint32_t irq_key = __get_BASEPRI();

    __set_BASEPRI_MAX(0x20);
    __ISB();
    if (z_spin_lock_valid(lock) == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_lock_valid(l)"), 0x000f08c7, 0x72);
        printk(((unsigned long)"\tInvalid spinlock %p\n"), lock);
        assert_post_action(0x000f08c7, 0x72);
    }

locked:
    z_spin_lock_set_owner(lock);
    *(volatile uint8_t *)item &= (uint8_t)~1u;   /* hdr.valid = 0 */

    if ((buffer->flags & 2u) == 0 ||
        item == buffer->buf + buffer->rd_idx) {
        *(volatile uint8_t *)item &= (uint8_t)~2u; /* hdr.busy = 0 */
        if (buffer->rd_idx == buffer->tmp_rd_idx) {
            buffer->tmp_rd_idx = idx_inc(buffer, buffer->tmp_rd_idx, words);
        }
        rd_idx_inc(buffer, words);
    } else {
        /* Overwrite-mode allocation advanced rd_idx during this claim.
         * Publish a skip record while preserving the two header flag bits. */
        *item = (*item & 3u) | (words << 2);
    }

    if (z_spin_unlock_valid(lock) == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"z_spin_unlock_valid(l)"), 0x000f08c7, 0xf0);
        printk(((unsigned long)"\tNot my spinlock %p\n"), lock);
        assert_post_action(0x000f08c7, 0xf0);
        goto locked; /* shipped continuation if the fatal oracle returns */
    }

    __set_BASEPRI(irq_key);
    __ISB();
    k_sem_give(buffer->sem);
}
