#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103657c @ 0x0103657c
 * public-name: z_impl_k_mutex_unlock
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_mutex_unlock                    <= FUN_0103657c @ 0x0103657c
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eaab                           @ 0x0103eaab
 *   g_net_ipc_shm_pool_desc_ptr              @ 0x21004b30
 */
/* net-core z_impl_k_mutex_unlock @ 0x0103657c
 * Raw backmap: FUN_0103657c.  This is Zephyr kernel/mutex.c's public
 * implementation body; the generated readable tree applies that identity. */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern int FUN_0103610c(uint32_t *);
extern int FUN_01036128(uint32_t *);
extern void FUN_01036144(uint32_t *);
extern void FUN_0103705c(void *);
extern void FUN_01037130(uint32_t *, uint32_t);
extern void *FUN_010379d4(uint32_t *);
extern void FUN_01039bb0(uint32_t, uint32_t);
extern void assert_print(uint32_t, uint32_t, uint32_t);
extern void FUN_0103b1c4(void *, int32_t);

#define LOG_STRING ((unsigned long)&rodata_103eaab) /*=0x103eaab*/
#define LOG_MODULE ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define ASSERT_STRING ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/
#define CURRENT_OWNER ((volatile uint32_t *)((unsigned long)&g_net_ipc_shm_pool_desc_ptr) /*=0x21004b30*/)
#define KERNEL_LOCK ((uint32_t *)0x21004b48u)

int32_t z_impl_k_mutex_unlock(uint32_t *object)
{
    uint32_t ipsr = __get_IPSR();
    void *owner;
    uint32_t count;
    uint32_t key;
    void *next;

    if (ipsr != 0) {
        assert_print(LOG_MODULE, LOG_STRING, 0xcdu);
        FUN_01039bb0(LOG_STRING, 0xcdu);
        __builtin_unreachable();
    }
    owner = (void *)(uintptr_t)object[2];
    if (owner == 0) {
        return -22;
    }
    if (owner != (void *)(uintptr_t)*CURRENT_OWNER) {
        return -1;
    }
    count = object[3];
    if (count == 0) {
        assert_print(LOG_MODULE, LOG_STRING, 0xe5u);
        FUN_01039bb0(LOG_STRING, 0xe5u);
        __builtin_unreachable();
    }
    if (count != 1) {
        object[3] = count - 1;
        return 0;
    }

    key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();
    if (FUN_0103610c(KERNEL_LOCK) == 0) {
        assert_print(LOG_MODULE, ASSERT_STRING, 0x72u);
        FUN_01039bb0(ASSERT_STRING, 0x72u);
        __builtin_unreachable();
    }
    FUN_01036144(KERNEL_LOCK);
    FUN_0103b1c4(owner, (int32_t)object[4]);
    next = FUN_010379d4(object);
    object[2] = (uint32_t)(uintptr_t)next;
    if (next != 0) {
        object[4] = (uint32_t)(int32_t)*(int8_t *)((uint8_t *)next + 14);
        *(volatile uint32_t *)((uint8_t *)next + 0x90) = ipsr;
        FUN_0103705c(next);
        FUN_01037130(KERNEL_LOCK, key);
        return 0;
    }
    object[3] = 0;
    if (FUN_01036128(KERNEL_LOCK) == 0) {
        assert_print(LOG_MODULE, ASSERT_STRING, 0xf0u);
        FUN_01039bb0(ASSERT_STRING, 0xf0u);
        __builtin_unreachable();
    }
    __set_BASEPRI(key);
    __ISB();
    return 0;
}
