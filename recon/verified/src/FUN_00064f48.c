/* Reconstructed FUN_00064f48 @ 0x64f48 */
#include <stdint.h>

extern void FUN_0007e2fa(uint32_t subsystem, uint32_t message,
                         uint32_t source, uint32_t line);
/* The real routine is noreturn.  The return type models unreachable r0 only. */
extern uint32_t FUN_0007e2ec(uint32_t source, uint32_t line);

void FUN_00064f48(uint32_t value, volatile uint8_t *object)
{
    if (object == 0) {
        FUN_0007e2fa(0x00099cbd, 0x000f6a46, 0x000f6a09, 0x44);
        value = FUN_0007e2ec(0x000f6a09, 0x44);
        /* The original loaded r1 with the diagnostic line before the noreturn
         * call, so this is its continuation address if that call returns. */
        object = (volatile uint8_t *)(uintptr_t)0x44u;
    }

    *(volatile uint32_t *)(object + 0x80) = value | UINT32_C(0x80000000);
}
