#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103689c @ 0x0103689c
 * public-name: FUN_0103689c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eacd                           @ 0x0103eacd
 */
/* CPUNET semaphore take implementation @ 0x0103689c.
 * Raw/address back-map: FUN_0103689c / 0x0103689c.
 */
#include <stdint.h>

extern int FUN_0103610c(void *lock);
extern int FUN_01036128(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_010375b8(void *lock, uint32_t key, void *object,
                        uint32_t ticks, uint32_t timeout_lo,
                        uint32_t timeout_hi);
extern void assert_post_action(uint32_t message, uint32_t line); /* FUN_01039bb0 */
extern void assert_print(uint32_t source, uint32_t message,       /* FUN_01039bbe */
                         uint32_t line);

static inline uint32_t exception_number(void)
{
    uint32_t value;
    __asm__ volatile ("mrs %0, ipsr" : "=r" (value));
    return value;
}

static inline uint32_t irq_lock(void)
{
    uint32_t key;
    uint32_t ceiling = 0x40u;
    __asm__ volatile ("mrs %0, basepri\n"
                      "msr basepri_max, %1\n"
                      "isb"
                      : "=r" (key) : "r" (ceiling) : "memory");
    return key;
}

static inline void irq_unlock(uint32_t key)
{
    __asm__ volatile ("msr basepri, %0\n"
                      "isb" :: "r" (key) : "memory");
}

int FUN_0103689c(uint32_t semaphore, uint32_t unused,
                 uint32_t timeout_lo, uint32_t timeout_hi)
{
    const uint32_t timeout_ticks = timeout_lo | timeout_hi;
    void *const kernel_lock = (void *)0x21004b4cu;

    (void)unused;
    if (exception_number() != 0 && timeout_ticks != 0) {
        assert_print((uint32_t)(uintptr_t)&rodata_103d2a7,
                     (uint32_t)(uintptr_t)&rodata_103eacd, 0x80u);
        assert_post_action((uint32_t)(uintptr_t)&rodata_103eacd, 0x80u);
        __builtin_unreachable();
    }

    uint32_t key = irq_lock();
    if (FUN_0103610c(kernel_lock) == 0) {
        assert_print((uint32_t)(uintptr_t)&rodata_103d2a7,
                     (uint32_t)(uintptr_t)&rodata_103d3b6, 0x72u);
        assert_post_action((uint32_t)(uintptr_t)&rodata_103d3b6, 0x72u);
        __builtin_unreachable();
    }

    FUN_01036144(kernel_lock);
    volatile uint32_t *const count = (volatile uint32_t *)(uintptr_t)(semaphore + 8u);
    if (*count != 0) {
        --*count;
        if (FUN_01036128(kernel_lock) != 0) {
            irq_unlock(key);
            return 0;
        }
    } else if (timeout_ticks != 0) {
        return FUN_010375b8(kernel_lock, key, (void *)(uintptr_t)semaphore,
                            timeout_ticks, timeout_lo, timeout_hi);
    } else if (FUN_01036128(kernel_lock) != 0) {
        irq_unlock(key);
        return -16;
    }

    assert_print((uint32_t)(uintptr_t)&rodata_103d2a7,
                 (uint32_t)(uintptr_t)&rodata_103d3b6, 0xf0u);
    assert_post_action((uint32_t)(uintptr_t)&rodata_103d3b6, 0xf0u);
    __builtin_unreachable();
}
