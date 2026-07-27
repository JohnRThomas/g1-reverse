/* FUN_00075574 @ 0x00075574 — complete 98-byte reconstruction. */
#include <stdint.h>

extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));

void FUN_00075574(uint8_t *object, uint32_t priority,
                  uint32_t reserved, uintptr_t handler)
{
    uint32_t line;

    if (reserved != 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f8835u, 0x000f871du, 0x2du, handler);
        FUN_0007e2fa(0x000f8855u);
        line = 0x2d;
    } else if (priority >= 0x40) {
        FUN_0007e2fa(0x00099cbdu, 0x000f887bu, 0x000f871du, 0x2fu, handler);
        FUN_0007e2fa(0x000f889fu);
        line = 0x2f;
    } else if (handler == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f88afu, 0x000f871du, 0x30u, handler);
        FUN_0007e2fa(0x000f88c2u);
        line = 0x30;
    } else {
        *(uint32_t *)(object + 8) = reserved;
        *(uint32_t *)(object + 12) = ((priority & 0x3fu) << 8) | object[12];
        *(uintptr_t *)(object + 16) = handler;
        return;
    }

    FUN_0007e2ec(0x000f871du, line);
}
