/* Full reconstruction FUN_000545f0 @ 0x000545f0 (348-byte exact extent). */
#include <stdint.h>

extern uint32_t FUN_000565c4(uintptr_t poll_events);
extern uint32_t FUN_000755f8(uintptr_t events, uint32_t count,
                            uint32_t timeout_lo, uint32_t timeout_hi);
extern uint64_t FUN_0007e2fa(uintptr_t module, uintptr_t file,
                            uintptr_t condition, uint32_t line);
/* The image inlines the fatal SVC veneer here.  The semantic external boundary
 * is therefore the SVC instruction at 0x5463e, not the separate 0x7e2ec
 * wrapper used by ordinary callers. */
extern void FUN_0005463e(uint32_t reason) __attribute__((noreturn));
extern void FUN_00054688(uint32_t reason) __attribute__((noreturn));
/* AAPCS aligns the 64-bit timeout in r2:r3, leaving r1 as unused padding. */
extern uintptr_t FUN_000836e8(uintptr_t queue, uint64_t timeout);
extern int FUN_00072908(uintptr_t event, uint64_t timeout);
extern void FUN_00080ea2(uintptr_t source, uint32_t level, const void *record);
extern void FUN_0005f24c(void *buffer);
extern uintptr_t FUN_0005f2d4(void *buffer);
extern uint32_t FUN_000543c8(void *buffer);
extern uint32_t FUN_0005ee18(void *buffer);
extern void FUN_00072880(uintptr_t event);
extern void FUN_000538f8(uint16_t handle, uint32_t reason, void *buffer);
extern void FUN_000571e8(void *connection);
extern void FUN_000745c8(uint32_t inherited);

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
    volatile uint8_t *const event_table = (volatile uint8_t *)0x20002944u;

    for (;;) {
        uint32_t flags = *(volatile uint32_t *)(event_table + 12);
        flags &= 0xffe03fffu;
        *(volatile uint32_t *)(event_table + 12) = flags;

        uint32_t count = FUN_000565c4(0x20002958u) + 1u;
        uint32_t wait_result = FUN_000755f8(0x20002944u, count,
                                           UINT32_MAX, UINT32_MAX);
        if (wait_result != 0) {
            (void)FUN_0007e2fa(0x00099cbdu, 0x000a7a10u,
                               0x000f2e84u, 0xadeu);
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
                    uintptr_t dequeued = FUN_000836e8(0x2000214cu, 0);
                    void *buffer = (void *)dequeued;
                    if (buffer == 0) {
                        (void)FUN_0007e2fa(0x00099cbdu, 0x000f45beu,
                                          0x000f2e84u, 0xa70u);
                        FUN_00054688(3);
                    }

                    FUN_00072908(0x20002128u, UINT64_MAX);

                    void **const pending = (void **)0x20002140u;
                    if (*pending != 0) {
                        const struct log2 record = {2, 0x000f313cu};
                        FUN_00080ea2(0x00088138u, 0x1040u, &record);
                        FUN_0005f24c(*pending);
                        *pending = 0;
                    }

                    *pending = (void *)FUN_0005f2d4(buffer);
                    uint32_t error = FUN_000543c8(buffer);
                    if (error != 0) {
                        const struct log3 record = {3, 0x000f3103u, error};
                        FUN_00080ea2(0x00088138u, 0x1840u, &record);
                        FUN_00072880(0x20002128u);
                        uint32_t slot = FUN_0005ee18(buffer);
                        uint16_t handle = *(volatile uint16_t *)
                            (0x2000abf4u + slot * 12u + 2u);
                        FUN_000538f8(handle, 0x1fu, buffer);
                        FUN_0005f24c(buffer);
                    }
                } else if (state == 1) {
                    FUN_000571e8((void *)(uintptr_t)
                                 (*(volatile uintptr_t *)(event + 16) - 0x38u));
                }
            } else {
                const struct log3 record = {3, 0x000f3157u, type};
                FUN_00080ea2(0x00088138u, 0x1880u, &record);
            }
        }
        FUN_000745c8(0);
    }
}
