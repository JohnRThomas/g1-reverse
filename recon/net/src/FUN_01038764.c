/* net-core FUN_01038764 @ 0x1038764 */
#include <stdint.h>

extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_01036128(void *lock);
extern uint32_t FUN_010384a8(void *work, int priority, void *state,
                             int immediate);
extern void FUN_01038654(void *work, uint32_t token, uint32_t irq_key);
extern int FUN_010375b8(void *lock, uint32_t irq_key, void *wait_queue,
                        uint32_t has_timeout,
                        uint32_t ticks_low, uint32_t ticks_high);
extern void FUN_01039bbe(const void *module, const void *file, unsigned line);
extern void FUN_01039bb0(const void *file, unsigned line);

static __attribute__((always_inline)) inline void scheduler_fatal(unsigned line)
{
    FUN_01039bbe((const void *)0x0103d2a7u,
                 (const void *)0x0103eb7fu, line);
    FUN_01039bb0((const void *)0x0103eb7fu, line);
}

static __attribute__((always_inline)) inline void scheduler_lock_fatal(unsigned line)
{
    FUN_01039bbe((const void *)0x0103d2a7u,
                 (const void *)0x0103d3b6u, line);
    FUN_01039bb0((const void *)0x0103d3b6u, line);
}

int FUN_01038764(void *work, int priority,
                 uint32_t ticks_low, uint32_t ticks_high)
{
    /* The two scheduler-lock regions are BASEPRI-protected in the image; the
     * integrated Zephyr source must wrap them with arch_irq_lock/unlock. */
    void *const lock = (void *)0x21004b78u;
    void *const wait_queue = (void *)0x21000758u;
    volatile uintptr_t *runtime = (volatile uintptr_t *)0x21004b28u;
    volatile uint8_t *state = (volatile uint8_t *)(runtime[2] + 0x60u);
    uint32_t token;
    int result;

    state[0] = 1;
    state[1] = 1;
    /* This API is thread-only.  The original checks IPSR and panics with
     * line 0x12d when invoked from an exception context. */
    if (work == 0) {
        scheduler_fatal(0x12e);
        return -1;
    }
    if (priority < 0) {
        scheduler_fatal(0x12f);
        return -1;
    }

    token = FUN_010384a8(work, priority, (void *)state,
                         (ticks_low | ticks_high) == 0);
    if (FUN_0103610c(lock) == 0) {
        scheduler_lock_fatal(0x72);
        return -1;
    }
    FUN_01036144(lock);

    if (state[0] == 0) {
        FUN_01038654(work, token, 0);
        if (FUN_01036128(lock) == 0)
            scheduler_lock_fatal(0xf0);
        return 0;
    }

    state[0] = 0;
    if ((ticks_low | ticks_high) == 0) {
        if (FUN_01036128(lock) == 0)
            scheduler_lock_fatal(0xf0);
        return -11;
    }

    result = FUN_010375b8(lock, 0, wait_queue, ticks_low | ticks_high,
                          ticks_low, ticks_high);
    if (FUN_0103610c(lock) == 0) {
        scheduler_lock_fatal(0x72);
        return result;
    }
    FUN_01036144(lock);
    FUN_01038654(work, token, 0);
    if (FUN_01036128(lock) == 0)
        scheduler_lock_fatal(0xf0);
    return result;
}
