#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000545f0 @ 0x000545f0
 * public-name: FUN_000545f0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_id                               <= FUN_0005ee18 @ 0x0005ee18
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_ref                              <= FUN_0005f2d4 @ 0x0005f2d4
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   mutex_unlock_syscall_handler             <= FUN_000745c8 @ 0x000745c8
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   net_buf_get                              <= FUN_000836e8 @ 0x000836e8
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_a7a10                             @ 0x000a7a10
 *   rodata_f2e84                             @ 0x000f2e84
 *   rodata_f3103                             @ 0x000f3103
 *   rodata_f313c                             @ 0x000f313c
 *   rodata_f3157                             @ 0x000f3157
 *   rodata_f45be                             @ 0x000f45be
 *   g_20002128                               @ 0x20002128
 *   g_20002140                               @ 0x20002140
 *   hci_cmd_pool                             @ 0x2000214c
 *   g_20002944                               @ 0x20002944
 *   g_20002958                               @ 0x20002958
 *   bt_hci_cmd_data                          @ 0x2000abf4
 */
/* Full reconstruction FUN_000545f0 @ 0x000545f0 (348-byte exact extent). */
#include <stdint.h>

extern uint32_t FUN_000565c4(uintptr_t poll_events);
extern uint32_t FUN_000755f8(uintptr_t events, uint32_t count,
                            uint32_t timeout_lo, uint32_t timeout_hi);
extern uint64_t printk(uintptr_t module, uintptr_t file,
                            uintptr_t condition, uint32_t line);
/* The image inlines the fatal SVC veneer here.  The semantic external boundary
 * is therefore the SVC instruction at 0x5463e, not the separate 0x7e2ec
 * wrapper used by ordinary callers. */
extern void FUN_0005463e(uint32_t reason) __attribute__((noreturn));
extern void FUN_00054688(uint32_t reason) __attribute__((noreturn));
/* AAPCS aligns the 64-bit timeout in r2:r3, leaving r1 as unused padding. */
extern uintptr_t net_buf_get(uintptr_t queue, uint64_t timeout);
extern int z_impl_k_sem_take(uintptr_t event, uint64_t timeout);
extern void FUN_00080ea2(uintptr_t source, uint32_t level, const void *record);
extern void net_buf_unref(void *buffer);
extern uintptr_t net_buf_ref(void *buffer);
extern uint32_t FUN_000543c8(void *buffer);
extern uint32_t net_buf_id(void *buffer);
extern void k_sem_give(uintptr_t event);
extern void FUN_000538f8(uint16_t handle, uint32_t reason, void *buffer);
extern void FUN_000571e8(void *connection);
extern void mutex_unlock_syscall_handler(uint32_t inherited);

struct log2 {
    uint32_t count;
    uintptr_t format;
};

struct log3 {
    uint32_t count;
    uintptr_t format;
    uint32_t value;
};

void FUN_000545f0(void)
{
    volatile uint8_t *const event_table = (volatile uint8_t *)((unsigned long)&g_20002944) /*=0x20002944*/;

    for (;;) {
        uint32_t flags = *(volatile uint32_t *)(event_table + 12);
        flags &= 0xffe03fffu;
        *(volatile uint32_t *)(event_table + 12) = flags;

        uint32_t count = FUN_000565c4(((unsigned long)&g_20002958) /*=0x20002958*/) + 1u;
        uint32_t wait_result = FUN_000755f8(((unsigned long)&g_20002944) /*=0x20002944*/, count,
                                           UINT32_MAX, UINT32_MAX);
        if (wait_result != 0) {
            (void)printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_a7a10) /*=0xa7a10*/,
                               ((unsigned long)&rodata_f2e84) /*=0xf2e84*/, 0xadeu);
            FUN_0005463e(3);
        }

        volatile uint8_t *event = event_table;
        for (uint32_t remaining = count; remaining != 0;
             --remaining, event += 20) {
            uint32_t type = (*(volatile uint32_t *)(event + 12) >> 14) & 0x7fu;
            if (type <= 2)
                continue;

            if (type == 4) {
                uint8_t state = *(volatile uint8_t *)(event + 12);
                if (state == 0) {
                    uintptr_t dequeued = net_buf_get(((unsigned long)&hci_cmd_pool) /*=0x2000214c*/, 0);
                    void *buffer = (void *)dequeued;
                    if (buffer == 0) {
                        (void)printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f45be) /*=0xf45be*/,
                                          ((unsigned long)&rodata_f2e84) /*=0xf2e84*/, 0xa70u);
                        FUN_00054688(3);
                    }

                    z_impl_k_sem_take(((unsigned long)&g_20002128) /*=0x20002128*/, UINT64_MAX);

                    void **const pending = (void **)((unsigned long)&g_20002140) /*=0x20002140*/;
                    if (*pending != 0) {
                        const struct log2 record = {2, ((unsigned long)&rodata_f313c) /*=0xf313c*/};
                        FUN_00080ea2(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1040u, &record);
                        net_buf_unref(*pending);
                        *pending = 0;
                    }

                    *pending = (void *)net_buf_ref(buffer);
                    uint32_t error = FUN_000543c8(buffer);
                    if (error != 0) {
                        const struct log3 record = {3, ((unsigned long)&rodata_f3103) /*=0xf3103*/, error};
                        FUN_00080ea2(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840u, &record);
                        k_sem_give(((unsigned long)&g_20002128) /*=0x20002128*/);
                        uint32_t slot = net_buf_id(buffer);
                        uint16_t handle = *(volatile uint16_t *)
                            (((unsigned long)&bt_hci_cmd_data) /*=0x2000abf4*/ + slot * 12u + 2u);
                        FUN_000538f8(handle, 0x1fu, buffer);
                        net_buf_unref(buffer);
                    }
                } else if (state == 1) {
                    FUN_000571e8((void *)(uintptr_t)
                                 (*(volatile uintptr_t *)(event + 16) - 0x38u));
                }
            } else {
                const struct log3 record = {3, ((unsigned long)&rodata_f3157) /*=0xf3157*/, type};
                FUN_00080ea2(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1880u, &record);
            }
        }
        mutex_unlock_syscall_handler(0);
    }
}
