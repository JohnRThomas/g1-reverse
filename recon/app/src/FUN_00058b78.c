/* Full reconstruction FUN_00058b78 @ 0x58b78, exact extent 108 bytes. */
#include <stdint.h>

extern void FUN_0007e2fa(uintptr_t, ...);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));
extern void FUN_00082030(void);

void FUN_00058b78(uint8_t *context, uint32_t *object,
                  uint32_t arg2, uint32_t arg3)
{
    uint32_t line;
    uintptr_t message;
    (void)arg2;
    if (context == 0) {
        line = 0x37c; message = 0x000f457au;
    } else if (object == 0) {
        line = 0x37d; message = 0x000f4590u;
    } else if (object[1] == 0) {
        line = 0x37e; message = 0x000f457fu;
    } else if (*(uint32_t *)(context + 0x124) != 0) {
        line = 0x37f; message = 0x000f4589u;
    } else {
        FUN_00082030();
        return;
    }
    FUN_0007e2fa(0x00099cbdu, message, 0x000f4388u, line, arg3);
    FUN_0007e2ec(0x000f4388u, line);
}
