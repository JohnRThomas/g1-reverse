/* Reconstructed FUN_000566a4 @ 0x566a4  true code extent: 0x50 bytes */
#include <stdint.h>

extern void FUN_0007e2fa(uint32_t module, ...);
extern void FUN_0007e2ec(uint32_t source, uint32_t line);
extern void FUN_00055aac(void *object);

void FUN_000566a4(uint8_t *object)
{
    uint32_t *references = (uint32_t *)(object + 0xd0);
    uint32_t previous = __atomic_fetch_sub(references, 1, __ATOMIC_ACQ_REL);

    if ((int32_t)previous <= 0) {
        FUN_0007e2fa(0x00099cbd, 0x000f3c07, 0x000f3a5d, 0x525);
        FUN_0007e2fa(0x000f3c0f);
        FUN_0007e2ec(0x000f3a5d, 0x525);
    }

    if (*(volatile uint16_t *)(object + 2) == 0x101 &&
        __atomic_load_n(references, __ATOMIC_ACQUIRE) == 0)
        FUN_00055aac(object);
}
