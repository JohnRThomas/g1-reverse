#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01038764 @ 0x01038764
 * public-name: FUN_01038764
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eb7f                           @ 0x0103eb7f
 */
/* net-core FUN_01038764 @ 0x1038764 */
#include <stdint.h>
#include <cmsis_gcc.h>

extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_01036128(void *lock);
extern uint32_t FUN_010384a8(void *work, int priority, void *state,
                             int immediate);
extern void FUN_01038654(void *work, uint32_t token, uint32_t irq_key);
extern int FUN_010375b8(void *lock, uint32_t irq_key, void *wait_queue,
                        uint32_t has_timeout,
                        uint32_t ticks_low, uint32_t ticks_high);
extern void assert_print(const void *module, const void *file, unsigned line);
extern void FUN_01039bb0(const void *file, unsigned line);

static __attribute__((always_inline)) inline void scheduler_fatal(unsigned line)
{
    assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                 (const void *)((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/, line);
    FUN_01039bb0((const void *)((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/, line);
}

static __attribute__((always_inline)) inline void scheduler_lock_fatal(unsigned line)
{
    assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                 (const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, line);
    FUN_01039bb0((const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, line);
}

int FUN_01038764(void *work, int priority,
                 uint32_t ticks_low, uint32_t ticks_high)
{
    void *const lock = (void *)0x21004b78u;
    void *const wait_queue = (void *)0x21000758u;
    volatile uintptr_t *runtime = (volatile uintptr_t *)0x21004b28u;
    volatile uint8_t *state = (volatile uint8_t *)(runtime[2] + 0x60u);
    uint32_t token, irq_key;
    int result;

    state[0] = 1;
    state[1] = 1;
    if ((__get_IPSR() & 0x1fu) != 0) {
        scheduler_fatal(0x12d);
        return -1;
    }
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
    irq_key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();
    if (FUN_0103610c(lock) == 0) {
        scheduler_lock_fatal(0x72);
        return -1;
    }
    FUN_01036144(lock);

    if (state[0] == 0) {
        FUN_01038654(work, token, irq_key);
        if (FUN_01036128(lock) == 0)
            scheduler_lock_fatal(0xf0);
        __set_BASEPRI(irq_key);
        __ISB();
        return 0;
    }

    state[0] = 0;
    if ((ticks_low | ticks_high) == 0) {
        if (FUN_01036128(lock) == 0)
            scheduler_lock_fatal(0xf0);
        __set_BASEPRI(irq_key);
        __ISB();
        return -11;
    }

    result = FUN_010375b8(lock, irq_key, wait_queue, ticks_low | ticks_high,
                          ticks_low, ticks_high);
    irq_key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();
    if (FUN_0103610c(lock) == 0) {
        scheduler_lock_fatal(0x72);
        return result;
    }
    FUN_01036144(lock);
    FUN_01038654(work, token, irq_key);
    if (FUN_01036128(lock) == 0)
        scheduler_lock_fatal(0xf0);
    __set_BASEPRI(irq_key);
    __ISB();
    return result;
}
