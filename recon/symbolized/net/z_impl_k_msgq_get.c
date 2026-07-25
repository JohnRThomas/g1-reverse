#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010362d0 @ 0x010362d0
 * public-name: z_impl_k_msgq_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_msgq_get                        <= FUN_010362d0 @ 0x010362d0
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103ea89                           @ 0x0103ea89
 */
/* net-core FUN_010362d0 @ 0x10362d0 */
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
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern int FUN_0103610c(void *lock);
extern int FUN_01036128(void *lock);
extern void FUN_01036144(void *lock);
extern void FUN_0103705c(void *item);
extern void FUN_01037130(void *lock, uint32_t key);
extern int FUN_010375b8(void *lock, uint32_t key, void *queue, void *item,
                        uint32_t low, uint32_t high);
extern void *FUN_010379d4(void *queue);
extern __attribute__((noreturn)) void assert_post_action(uint32_t source,
                                                   uint32_t line);
extern void assert_print(uint32_t module, uint32_t source, uint32_t line, ...);
extern void FUN_0103b614(void *destination, const void *source, uint32_t size);

typedef struct {
    uint8_t reserved_00[0x0c];
    uint32_t element_size;
    uint32_t reserved_10;
    uint8_t *buffer_begin;
    uint8_t *buffer_end;
    uint8_t *write_cursor;
    uint8_t *read_cursor;
    uint32_t queued;
} queue_t;

typedef struct {
    uint8_t reserved_00[0x14];
    const void *payload;
    uint8_t reserved_18[0x78];
    uint32_t ownership;
} queue_item_t;

static __attribute__((noreturn)) void queue_fatal(uint32_t source,
                                                  uint32_t line)
{
    assert_post_action(source, line);
}

int z_impl_k_msgq_get(queue_t *queue, void *destination,
                 uint32_t timeout_low, uint32_t timeout_high)
{
    /* Zephyr callers enter this API from thread context.  Timed queue writes
     * from an ISR are forbidden by the kernel contract. */
    if ((__get_IPSR() & 0x1fu) != 0 && (timeout_low | timeout_high) != 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103ea89) /*=0x103ea89*/, 0xd2,
                     timeout_low | timeout_high, queue, destination, timeout_low);
        queue_fatal(((unsigned long)&rodata_103ea89) /*=0x103ea89*/, 0xd2);
    }

    void *lock = (uint8_t *)queue + 8;
    uint32_t key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40);
    __ISB();

    if (FUN_0103610c(lock) == 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        queue_fatal(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
    }

    FUN_01036144(lock);
    int result;
    if (queue->queued == 0) {
        if ((timeout_low | timeout_high) != 0) {
            queue_item_t *item = *(queue_item_t **)(UINT32_C(G1_NET_K(0x00)) + 8);
            item->payload = destination;
            return FUN_010375b8(lock, key, queue, item,
                                timeout_low, timeout_high);
        }
        result = -0x23;
    } else {
        FUN_0103b614(destination, queue->write_cursor, queue->element_size);
        queue->write_cursor += queue->element_size;
        if (queue->write_cursor == queue->buffer_end)
            queue->write_cursor = queue->buffer_begin;
        queue->queued--;

        queue_item_t *item = FUN_010379d4(queue);
        result = (int)(intptr_t)item;
        if (item != 0) {
            if (queue->read_cursor < queue->buffer_begin ||
                queue->read_cursor >= queue->buffer_end) {
                assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103ea89) /*=0x103ea89*/, 0xeb,
                             queue->buffer_begin, queue->read_cursor, destination,
                             timeout_low);
                queue_fatal(((unsigned long)&rodata_103ea89) /*=0x103ea89*/, 0xeb);
            }

            FUN_0103b614(queue->read_cursor, item->payload,
                         queue->element_size);
            queue->read_cursor += queue->element_size;
            if (queue->read_cursor == queue->buffer_end)
                queue->read_cursor = queue->buffer_begin;
            queue->queued++;
            item->ownership = 0;
            FUN_0103705c(item);
            FUN_01037130(lock, key);
            return 0;
        }
    }

    result = FUN_01036128(lock) ? result : 0;
    if (result == 0) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
        queue_fatal(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    }
    __set_BASEPRI(key);
    __ISB();
    return result;
}
