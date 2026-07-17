/* Reconstructed mpsc_pbuf_claim @ 0x0102ce14.
 * Raw/address back-map: FUN_0102ce14 / 0x0102ce14.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

struct mpsc_pbuf_buffer {
    uint32_t tmp_wr_idx, wr_idx, tmp_rd_idx, rd_idx, flags, lock;
    void (*notify_drop)(void *, const void *);
    uint32_t (*get_wlen)(const void *);
    volatile uint32_t *buf;
    uint32_t size, max_usage;
    uint8_t sem[0x10];
};

extern int FUN_0103610c(void *lock);
extern int FUN_01036128(void *lock);
extern void FUN_01036144(void *lock);
extern void FUN_01039bbe(const void *, const void *, uint32_t);
extern void FUN_01039bb0(const void *, uint32_t) __attribute__((noreturn));
extern uint32_t FUN_01039c20(struct mpsc_pbuf_buffer *, uint32_t, uint32_t);
extern void FUN_01039c3c(struct mpsc_pbuf_buffer *, uint32_t);

static inline uint32_t claim_lock(struct mpsc_pbuf_buffer *buffer)
{
    uint32_t key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();
    if (FUN_0103610c(&buffer->lock) == 0) {
        FUN_01039bbe((const void *)0x0103d2a7u,
                     (const void *)0x0103d3b6u, 0x72u);
        FUN_01039bb0((const void *)0x0103d3b6u, 0x72u);
    }
    FUN_01036144(&buffer->lock);
    return key;
}

static inline void claim_unlock(struct mpsc_pbuf_buffer *buffer, uint32_t key)
{
    if (FUN_01036128(&buffer->lock) == 0) {
        FUN_01039bbe((const void *)0x0103d2a7u,
                     (const void *)0x0103d3b6u, 0xf0u);
        FUN_01039bb0((const void *)0x0103d3b6u, 0xf0u);
    }
    __set_BASEPRI(key);
    __ISB();
}

const void *FUN_0102ce14(struct mpsc_pbuf_buffer *buffer)
{
    const void *item;
    uint32_t again;
    do {
        uint32_t available;
        uint32_t key = claim_lock(buffer);
        if (((buffer->flags & 8u) != 0u) ||
            (buffer->tmp_rd_idx > buffer->wr_idx)) {
            available = buffer->size - buffer->tmp_rd_idx;
        } else {
            available = buffer->wr_idx - buffer->tmp_rd_idx;
        }
        volatile uint32_t *raw = &buffer->buf[buffer->tmp_rd_idx];
        uint8_t header = *(volatile uint8_t *)raw;
        item = (const void *)raw;
        again = 0;
        if ((available == 0u) || ((header & 3u) == 0u)) {
            item = 0;
        } else {
            uint32_t skip = ((header & 3u) == 2u) ? (*raw >> 2) : 0u;
            if ((skip != 0u) || ((header & 1u) == 0u)) {
                uint32_t words = skip != 0u ? skip : buffer->get_wlen((const void *)raw);
                buffer->tmp_rd_idx = FUN_01039c20(buffer, buffer->tmp_rd_idx,
                                                   words);
                FUN_01039c3c(buffer, words);
                again = 1;
            } else {
                *(volatile uint8_t *)raw = header | 2u;
                uint32_t words = buffer->get_wlen((const void *)raw);
                buffer->tmp_rd_idx = FUN_01039c20(buffer, buffer->tmp_rd_idx,
                                                   words);
            }
        }
        claim_unlock(buffer, key);
    } while (again != 0u);
    return item;
}
