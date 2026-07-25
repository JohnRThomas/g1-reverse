/* net-core FUN_01038764 @ 0x1038764 */
#ifdef G1_COHESIVE_BUILD
/* P4 iteration 20 - the shipped CPUNET `_kernel` is at 0x21004b28.
 * In the relocated cohesive link that address is inside `sdc_mempool`
 * (0x21002bb8..0x21007e79), so every recovered kernel body that reaches the
 * scheduler through this base read/wrote a SHADOW copy of `_kernel` carved out
 * of the SoftDevice Controller's heap while the linked Zephyr scheduler
 * (z_arm_pendsv, arch_swap, z_ready_thread) used the real one at
 * &_kernel.  Iteration 7 converted only the four spinlock validators and
 * recorded the rest as open; this pass closes the whole window structurally.
 * Field offsets are identical in both images: +0x08 = cpus[0].current and
 * +0x10 = cpus[0].id were verified against the shipped disassembly in
 * iteration 7, which fixes struct _cpu at 0x14 bytes and therefore
 * ready_q.cache at +0x14 and ready_q.runq at +0x18; `nm -S` reports
 * sizeof(_kernel) = 0x20 in this link.
 * Parity builds keep the original literal, so no proven body changes. */
/* Reached through an asm label so no reconstruction TU has to pull in the
 * Zephyr kernel headers (several of them declare assert_print /
 * assert_post_action with the recovered prototypes). */
extern char g1_net_kernel_object[] __asm__("_kernel");
#define G1_NET_KERNEL_BASE ((unsigned long)g1_net_kernel_object)
#else
#define G1_NET_KERNEL_BASE 0x21004b28ul
#endif
#define G1_NET_K(off) (G1_NET_KERNEL_BASE + (off))

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
    void *const lock = (void *)0x21004b78u;
    void *const wait_queue = (void *)0x21000758u;
    volatile uintptr_t *runtime = (volatile uintptr_t *)G1_NET_K(0x00);
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
