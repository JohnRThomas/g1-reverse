#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102cc34 @ 0x0102cc34
 * public-name: mpsc_pbuf_alloc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   mpsc_pbuf_alloc                          <= FUN_0102cc34 @ 0x0102cc34
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* Reconstructed mpsc_pbuf_alloc @ 0x0102cc34.
 * Raw/address back-map: FUN_0102cc34 / 0x0102cc34.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

struct mpsc_pbuf_buffer {
    volatile uint32_t tmp_wr_idx;
    uint32_t wr_idx;
    uint32_t tmp_rd_idx;
    volatile uint32_t rd_idx;
    uint32_t flags;
    uint32_t lock;
    void (*notify_drop)(void *, const void *);
    uint32_t (*get_wlen)(const void *);
    volatile uint32_t *buf;
    uint32_t size;
    uint32_t max_usage;
    uint8_t sem[0x10];
};

extern int FUN_0103610c(void *lock);
extern int FUN_01036128(void *lock);
extern void FUN_01036144(void *lock);
extern void assert_print(const void *, const void *, uint32_t);
extern void assert_post_action(const void *, uint32_t) __attribute__((noreturn));
extern void FUN_01039d80(struct mpsc_pbuf_buffer *, uint32_t, uint32_t);
extern int FUN_01039bd8(struct mpsc_pbuf_buffer *, uint32_t *);
extern uint32_t FUN_01039c20(struct mpsc_pbuf_buffer *, uint32_t, uint32_t);
extern void FUN_01039c54(struct mpsc_pbuf_buffer *, uint32_t);
extern int FUN_0103b14a(void);
extern int FUN_0103689c(void *, uint64_t);
extern int FUN_01039c92(struct mpsc_pbuf_buffer *, uint32_t,
                        const void **, uint32_t *);

__attribute__((always_inline)) static inline uint32_t
buffer_lock(struct mpsc_pbuf_buffer *buffer)
{
    uint32_t key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();
    if (FUN_0103610c(&buffer->lock) == 0) {
        assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                     (const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72u);
        assert_post_action((const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72u);
    }
    FUN_01036144(&buffer->lock);
    return key;
}

__attribute__((always_inline)) static inline void
buffer_unlock(struct mpsc_pbuf_buffer *buffer, uint32_t key)
{
    if (FUN_01036128(&buffer->lock) == 0) {
        assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                     (const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0u);
        assert_post_action((const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0u);
    }
    __set_BASEPRI(key);
    __ISB();
}

void *mpsc_pbuf_alloc(struct mpsc_pbuf_buffer *buffer, uint32_t words,
                   uint32_t timeout_low, uint32_t timeout_high)
{
    const void *dropped = 0;
    uint32_t shifted_words = 0;
    uint32_t previous_index = 0;
    void *item = 0;
    volatile uint32_t again = 1;

    if (words > buffer->size) {
        return 0;
    }
    do {
        uint32_t free_words;
        uint32_t key = buffer_lock(buffer);
        if (shifted_words != 0u) {
            FUN_01039d80(buffer, previous_index, shifted_words);
            shifted_words = 0;
        }
        uint32_t wrap = (uint32_t)FUN_01039bd8(buffer, &free_words);
        if (free_words >= words) {
            uint32_t index = buffer->tmp_wr_idx;
            volatile uint8_t *header = (volatile uint8_t *)&buffer->buf[index];
            item = (void *)header;
            *header &= (uint8_t)~3u;
            index = FUN_01039c20(buffer, index, words);
            buffer->tmp_wr_idx = index;
            if (index == buffer->rd_idx) {
                buffer->flags |= 8u;
            }
            again = 0;
        } else if (wrap != 0u) {
            FUN_01039c54(buffer, free_words);
            again = 1;
        } else if (((timeout_low | timeout_high) != 0u) &&
                   (FUN_0103b14a() == 0)) {
            buffer_unlock(buffer, key);
            again = FUN_0103689c(buffer->sem,
                                 ((uint64_t)timeout_high << 32) | timeout_low) == 0;
            key = buffer_lock(buffer);
        } else if (again != 0u) {
            previous_index = buffer->tmp_wr_idx;
            again = (uint32_t)FUN_01039c92(buffer, free_words, &dropped,
                                           &shifted_words);
        }
        buffer_unlock(buffer, key);
        if (dropped != 0) {
            if (buffer->notify_drop != 0) {
                buffer->notify_drop(buffer, dropped);
            }
            dropped = 0;
        }
    } while (again != 0u);
    return item;
}
