/* Full reconstruction of FUN_0004f770 @ 0x4f770 (182 bytes). */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern int FUN_00072040(uintptr_t lock);
extern int FUN_0007205c(uintptr_t lock);
extern void FUN_00072078(uintptr_t lock);
extern void FUN_00072fdc(uintptr_t object);
extern void FUN_0007e2fa(uintptr_t domain, uintptr_t message, ...);
extern void FUN_0007e2ec(uintptr_t file, uint32_t line) __attribute__((noreturn));

void FUN_0004f770(uint32_t *item)
{
    if (item == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f1754u, 0x000f1681u, 0xd1u);
        FUN_0007e2ec(0x000f1681u, 0xd1u);
    }
    if (item[1] < 0x000fa9b4u || item[1] >= 0x000faa14u) {
        FUN_0007e2fa(0x00099cbdu, 0x000f16beu, 0x000f1681u, 0xd2u);
        FUN_0007e2ec(0x000f1681u, 0xd2u);
    }

    uint32_t saved_basepri = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20u);
    __ISB();

    if (FUN_00072040(0x2000a2c4u) == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f0920u, 0x000f08c7u, 0x72u);
        FUN_0007e2fa(0x000f0935u, 0x2000a2c4u);
        FUN_0007e2ec(0x000f08c7u, 0x72u);
    }

    FUN_00072078(0x2000a2c4u);
    *item = 0;
    volatile uint32_t **queue = (volatile uint32_t **)0x2000a2c8u;
    if (queue[1] == 0) {
        queue[0] = item;
        queue[1] = item;
    } else {
        *queue[1] = (uint32_t)(uintptr_t)item;
        queue[1] = item;
    }

    if (FUN_0007205c(0x2000a2c4u) == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f08f4u, 0x000f08c7u, 0xf0u);
        FUN_0007e2fa(0x000f090bu, 0x2000a2c4u);
        FUN_0007e2ec(0x000f08c7u, 0xf0u);
    }

    __set_BASEPRI(saved_basepri);
    __ISB();
    FUN_00072fdc(0x20002838u);
}
