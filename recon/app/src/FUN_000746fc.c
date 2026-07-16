/* Reconstructed FUN_000746fc @ 0x746fc.
 * CFG_VERIFY_CALL_ARITIES=3,1,1,0,4,1,1,4,1,2
 */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern void FUN_000745c8(void);
extern int32_t FUN_00086690(uint32_t, int32_t, ...);
extern int FUN_00072040(uintptr_t);
extern void FUN_00072078(uintptr_t);
extern int FUN_0007205c(uintptr_t);
extern void FUN_00073e88(void);
extern void FUN_00074bf4(void *, uintptr_t, uint32_t, int32_t);
extern void FUN_000501d4(uint32_t);
extern void FUN_0007e2fa(uintptr_t, ...);
extern void FUN_0007e2ec(uintptr_t, uintptr_t);

int32_t FUN_000746fc(uint32_t lo, int32_t hi)
{
    uint32_t exception = __get_IPSR() & 0x1fU;
    if (exception != 0) {
        FUN_0007e2fa(0x99cbd, 0xf801f, 0xf82f4, 0x596);
        FUN_0007e2fa(0xf53ff);
        FUN_0007e2ec(0xf82f4, 0x596);
    }
    if ((lo | (uint32_t)hi) == 0) {
        FUN_000745c8();
        return 0;
    }

    uint32_t target;
    int64_t requested = ((int64_t)hi << 32) | lo;
    if (requested >= -1)
        target = lo + (uint32_t)FUN_00086690(lo, hi, lo + 2U);
    else
        target = 0U - lo - 2U;

    uint32_t key = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20);
    __ISB();
    if (FUN_00072040(0x2000b490) == 0) {
        FUN_0007e2fa(0x99cbd, 0xf0920, 0xf08c7, 0x72);
        FUN_0007e2fa(0xf0935, 0x2000b490);
        FUN_0007e2ec(0xf08c7, 0x72);
    }
    FUN_00072078(0x2000b490);
    volatile uint8_t *thread = *(volatile uint8_t **)(uintptr_t)(0x2000b448 + 8);
    *(uint32_t *)(uintptr_t)0x2000b484 = (uint32_t)(uintptr_t)thread;
    FUN_00073e88();
    thread = *(volatile uint8_t * volatile *)(uintptr_t)(0x2000b448 + 8);
    FUN_00074bf4((void *)(thread + 0x18), 0x86661, lo, hi);
    thread[0xd] |= 0x10;
    if (FUN_0007205c(0x2000b490) == 0) {
        FUN_0007e2fa(0x99cbd, 0xf08f4, 0xf08c7, 0x111);
        FUN_0007e2fa(0xf090b, 0x2000b490);
        FUN_0007e2ec(0xf08c7, 0x111);
    }
    FUN_000501d4(key);
    thread = *(volatile uint8_t * volatile *)(uintptr_t)(0x2000b448 + 8);
    if ((thread[0xd] & 0x10) != 0) {
        FUN_0007e2fa(0x99cbd, 0xf8658, 0xf82f4, 0x5b2);
        FUN_0007e2fa(0xf53ff);
        FUN_0007e2ec(0xf82f4, 0x5b2);
    }
    uint32_t now = (uint32_t)FUN_00086690(0, 0);
    return target > now ? (int32_t)(target - now) : 0;
}
