/* net-core FUN_0103038c @ 0x103038c */
#include <stdint.h>

extern int32_t FUN_0102ca80(uint32_t);
extern void FUN_01039bbe(uint32_t, uint32_t, uint32_t);
extern void FUN_01039bb0(uint32_t, uint32_t);
extern uint32_t FUN_0103b14a(void);
extern void FUN_0102ea00(uint32_t);
extern void FUN_01037c64(uint32_t, uint32_t);

void FUN_0103038c(uint32_t mode)
{
    volatile uint32_t *lock = (volatile uint32_t *)0x21004810u;
    uint32_t was_locked = *lock;
    *lock = 1;
    if (!was_locked) {
        volatile uint32_t *state = (volatile uint32_t *)0x21004800u;
        state[1] = 0;
        state[3] = 0;
        state[2] = 1;
        if (FUN_0102ca80(0x21004834u) < 0) {
            FUN_01039bbe(0x0103d2a7u, 0x0103dea5u, 0x230u);
            FUN_01039bb0(0x0103dea5u, 0x230u);
        }
    }
    if (mode == 0)
        return;
    if (mode > 2) {
        for (;;) {
            FUN_01039bbe(0x0103d2a7u, 0x0103dea5u, 0x242u);
            FUN_01039bb0(0x0103dea5u, 0x242u);
        }
    }

    volatile uint32_t *clock = (volatile uint32_t *)0x41005000u;
    if (mode == 1 && (clock[0x41c / 4] & 3u) == 2u)
        return;

    uint32_t critical = FUN_0103b14a();
    if (!critical && *(volatile uint8_t *)0x21006461u)
        clock[0x308 / 4] = 2;

    for (;;) {
        uint32_t status = clock[0x418 / 4];
        uint32_t source = clock[0x418 / 4] & 3u;
        if ((status & 0x00020000u) && (source == 2u || mode == 1u)) {
            if (!critical)
                clock[0x304 / 4] = 2;
            return;
        }

        if (critical)
            FUN_0102ea00(0);
        else
            FUN_01037c64(0x21u, 0);

        while ((uint8_t)clock[0x518 / 4] == 1u && clock[0x104 / 4] != 0) {
            clock[0x104 / 4] = 0;
            (void)clock[0x104 / 4];
            clock[0x518 / 4] = 2;
            *(volatile uint32_t *)0xe000e280u = 0x20u;
            clock[2] = 1;
        }
    }
}
