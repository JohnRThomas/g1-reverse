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

extern int FUN_00072040(void *lock);
extern int FUN_0007205c(void *lock);
extern void FUN_00072078(void *lock);
extern void FUN_0007e2fa(uint32_t, ...);
extern void FUN_0007e2ec(uint32_t, uint32_t);
extern uint32_t FUN_0007e35c(struct mpsc_buffer *, uint32_t, uint32_t);
extern void FUN_0007e378(struct mpsc_buffer *, uint32_t);
extern void FUN_00072880(void *sem);

void FUN_0004bfc8(struct mpsc_buffer *buffer, volatile uint32_t *item)
{
    uint32_t words = buffer->get_wlen((void *)item);
    void *lock = &buffer->lock;
    uint32_t key = __get_BASEPRI();

    __set_BASEPRI_MAX(0x20);
    __ISB();
    if (!FUN_00072040(lock)) {
        FUN_0007e2fa(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72);
        FUN_0007e2fa(0x000f0935, lock);
        FUN_0007e2ec(0x000f08c7, 0x72);
        return;
    }
    FUN_00072078(lock);

    *(volatile uint8_t *)item &= (uint8_t)~1u;
    if ((buffer->flags & 2u) != 0 &&
        item != buffer->buf + buffer->rd_idx) {
        *item = (*item & 3u) | (words << 2);
    } else {
        *(volatile uint8_t *)item &= (uint8_t)~2u;
        if (buffer->rd_idx == buffer->tmp_rd_idx)
            buffer->tmp_rd_idx =
                FUN_0007e35c(buffer, buffer->tmp_rd_idx, words);
    }
    FUN_0007e378(buffer, words);

    if (!FUN_0007205c(lock)) {
        FUN_0007e2fa(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
        FUN_0007e2fa(0x000f090b, lock);
        FUN_0007e2ec(0x000f08c7, 0xf0);
        return;
    }
    __set_BASEPRI(key);
    __ISB();
    return FUN_00072880(buffer->sem);
}
