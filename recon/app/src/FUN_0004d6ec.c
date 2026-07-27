/* Full reconstruction of FUN_0004d6ec @ 0x4d6ec (194 bytes).
 * CFG_VERIFY_CALL_ARITIES=2,0,1,1,0,4
 */
#include <stdint.h>

extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uint32_t, uint32_t) __attribute__((noreturn));
extern uintptr_t FUN_0004d334(uint32_t, uint32_t);
extern unsigned int FUN_0004d2d0(unsigned int);
extern uintptr_t FUN_000748ac(void);
extern void FUN_00072880(uintptr_t);
extern uint64_t FUN_0004d594(void);
extern void FUN_00072908(uintptr_t, uint32_t, uint32_t, uint32_t);

void FUN_0004d6ec(void)
{
    uintptr_t const begin = 0x000882a0u;
    uintptr_t const end = 0x000882b0u;
    if ((end - begin) / 16u == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f0d3fu, 0x000f0caeu, 0x35cu);
        FUN_0007e2ec(0x000f0caeu, 0x35cu);
    }

    uintptr_t iterator = FUN_0004d334(0, 0);
    uint32_t event = iterator ? 0x667u : UINT32_MAX;
    uint32_t status = iterator ? 0u : UINT32_MAX;
    uintptr_t timer = FUN_000748ac();
    *(volatile uintptr_t *)0x2000a0d0u = timer;
    if (timer && *(volatile int32_t *)0x2000a0d8u > 9)
        FUN_00072880(0x200039f8u);

    uint32_t previous = 0;
    for (;;) {
        if (iterator) {
            iterator = FUN_0004d2d0(iterator);
            if (!iterator)
                event = status = UINT32_MAX;
        }
        uint64_t result = FUN_0004d594();
        uint32_t current = (uint32_t)result;
        uint32_t aux = (uint32_t)(result >> 32);
        if (!current) {
            if (previous) {
                for (uintptr_t item = begin; item < end; item += 16) {
                    uintptr_t ops = *(volatile uintptr_t *)item;
                    uintptr_t callback = *(volatile uintptr_t *)(ops + 0x18);
                    if (callback)
                        ((void (*)(uintptr_t, uint32_t))callback)(item, 0);
                }
            }
            FUN_00072908(0x200039f8u, aux, event, status);
        }
        previous = current;
    }
}
