/* Full reconstruction FUN_0002a4f4 @ 0x2a4f4, exact extent 320 bytes.
 * CFG_VERIFY_PREFIX_FIRST */
#include <stdint.h>

extern int FUN_00086534(uintptr_t object, uint32_t flags, uint32_t count);
extern void DEBUG_PRINT(uintptr_t format, ...);
extern uintptr_t FUN_000167a8(void);
extern void FUN_0002a4d8(uint32_t delay);
extern void FUN_00032c0c(void);
extern void thunk_FUN_00074844(uint32_t ticks, uint32_t flags);
extern uint64_t FUN_00032ee4(void);
extern int thunk_FUN_00072908(uintptr_t object, uint32_t high,
                             uint32_t timeout, uint32_t flags);
extern uint64_t FUN_0007cb2c(void);
extern void FUN_0002563c(uint8_t *status);
extern int FUN_0002560c(void);
extern void FUN_0002eb28(uint32_t channel, uint32_t enabled);
extern int FUN_00033340(void);
extern void FUN_0003271c(void);

void FUN_0002a4f4(uint32_t inherited_stack, uint32_t packed_status,
                  uint32_t inherited_r2, uint32_t inherited_r3)
{
    volatile uint8_t *const initialized = (volatile uint8_t *)0x20018d88u;
    volatile uint64_t *const deadline = (volatile uint64_t *)0x200040c8u;
    volatile uint8_t *const channels_stopped = (volatile uint8_t *)0x20018d94u;
    unsigned attempts = 0;

    (void)inherited_stack;
    (void)inherited_r2;
    (void)inherited_r3;
    int init_result = FUN_00086534(0x20007b00u, 0, 10);
    uint32_t stale_r2 = 10;
    if (init_result == 0) {
        *initialized = 1;
        stale_r2 = 1;
    }
    DEBUG_PRINT(0x000a1895u, (uint32_t)*initialized, stale_r2, 0x20018d88u);

    for (;;) {
        if (*(volatile uint8_t *)(FUN_000167a8() + 1) == 8) {
            FUN_0002a4d8(10000);
            FUN_00032c0c();
            thunk_FUN_00074844(0x667, 0);
            continue;
        }
        if (*(volatile uint8_t *)(FUN_000167a8() + 1) == 1) {
            thunk_FUN_00074844(0x28000, 0);
            continue;
        }

        uint64_t state = FUN_00032ee4();
        if ((uint32_t)state == 1) {
            int active = FUN_0002560c();
            if (*(volatile uint8_t *)(FUN_000167a8() + 0x1088) == 1)
                active = FUN_00033340();
            thunk_FUN_00074844(0x1334, 0);
            if (active == 0)
                FUN_0003271c();
            thunk_FUN_00074844(0x1334, 0);
            continue;
        }

        int wait_result = thunk_FUN_00072908(0x20007b00u,
                                             (uint32_t)(state >> 32),
                                             0x18000, 0);
        if (wait_result != 0) {
            if (*channels_stopped == 0 &&
                *(volatile uint8_t *)(FUN_000167a8() + 1) != 8) {
                uint64_t then = *deadline;
                uint64_t first_now = FUN_0007cb2c();
                uint64_t second_now = FUN_0007cb2c();
                if (then < second_now && first_now - then >= 3001) {
                    FUN_0002eb28(0, 0);
                    FUN_0002eb28(1, 0);
                    *channels_stopped = 0;
                }
            }
            continue;
        }

        uint8_t status = (uint8_t)(packed_status >> 24);
        uint64_t now = FUN_0007cb2c();
        if (*deadline < now)
            FUN_0002a4d8(0);
        FUN_0002563c(&status);
        if (status & 0x20) {
            FUN_0002560c();
            FUN_0002eb28(0, 1);
            attempts = 0;
        } else if (++attempts >= 10) {
            FUN_0002eb28(0, 1);
            attempts = 0;
        }
    }
}
