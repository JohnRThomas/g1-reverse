/* Full reconstruction FUN_00060788 @ 0x60788, exact 280-byte extent. */
#include <stdint.h>
#include <cmsis_gcc.h>

extern int FUN_0004b908(uintptr_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));
extern int FUN_00086406(void);
extern void FUN_0004ff38(uint32_t);
extern void FUN_00074844(uint32_t, uint32_t);

void FUN_00060788(uint32_t mode)
{
    volatile uint32_t *once = (volatile uint32_t *)0x2000b094u;
    uint32_t old = __atomic_exchange_n(once, 1u, __ATOMIC_ACQ_REL);

    if (old == 0) {
        volatile uint32_t *state = (volatile uint32_t *)0x2000b084u;
        state[1] = 0;
        state[3] = 0;
        state[2] = 1;
        if (FUN_0004b908(0x2000b0b8u) < 0) {
            FUN_0007e2fa(0x00099cbdu, 0x000f0f1bu, 0x000f5ad9u, 0x230u);
            FUN_0007e2ec(0x000f5ad9u, 0x230u);
        }
    }

    if (mode == 0)
        return;
    if (mode > 2) {
        FUN_0007e2fa(0x00099cbdu, 0x000f7a30u, 0x000f5ad9u, 0x242u);
        FUN_0007e2ec(0x000f5ad9u, 0x242u);
    }

    volatile uint32_t *hw = (volatile uint32_t *)0x50005000u;
    if (mode == 1 && (hw[0x41c / 4] & 3u) == 2u)
        return;

    int privileged = FUN_00086406();
    uint32_t saved = 0;
    if (privileged == 0 && *(volatile uint8_t *)0x2001d564u != 0) {
        hw[0x308 / 4] = 2;
    } else {
        saved = __get_BASEPRI();
        __set_BASEPRI_MAX(0x20u);
        __ISB();
        privileged = 1;
    }

    while ((hw[0x418 / 4] & 0x10000u) == 0 ||
           ((hw[0x418 / 4] & 3u) != 2u && mode != 1)) {
        if (privileged)
            FUN_0004ff38(saved);
        else
            FUN_00074844(0x21u, 0);

        if ((uint8_t)hw[0x518 / 4] == 1u && hw[0x104 / 4] != 0) {
            hw[0x104 / 4] = 0;
            (void)hw[0x104 / 4];
            hw[0x518 / 4] = 2;
            *(volatile uint32_t *)0xe000e280u = 0x20u;
            hw[8 / 4] = 1;
        }
    }

    if (privileged) {
        __set_BASEPRI(saved);
        __ISB();
    } else {
        hw[0x304 / 4] = 2;
    }
}
