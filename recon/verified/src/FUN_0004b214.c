/* Full reconstruction of FUN_0004b214 @ 0x4b214 (130-byte extent). */
#include <stdint.h>

extern uint32_t FUN_0007de5c(uint32_t object, uint32_t length, uint32_t mode);
extern uint32_t FUN_0007ddec(uint32_t object, uint32_t offset, uint32_t mode);
extern uint32_t FUN_0007de18(uint32_t object, uint32_t offset);
extern uint32_t FUN_0007de24(uint32_t object, uint32_t offset);
extern void FUN_0007e0a6(uint32_t value, uint32_t offset);
extern void FUN_0007e2fa(unsigned long, ...);
extern _Noreturn void FUN_0007e2ec(uintptr_t file, uint32_t line);

void FUN_0004b214(const uint32_t *owner, uint32_t length,
                  uint32_t unused, uint32_t context)
{
    (void)unused;
    if (length == 0)
        return;

    uint32_t object = *owner;
    uint32_t start = FUN_0007de5c(object, length, 1);
    if ((FUN_0007ddec(object, start, 1) & 1u) == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f06b3u, 0x000f0692u, 0xafu,
                     context);
        FUN_0007e2fa(0x000f06c4u, length);
        FUN_0007e2ec(0x000f0692u, 0xafu);
    }

    uint32_t end = start + FUN_0007de18(object, start);
    if (start != end - FUN_0007ddec(object, end, 0)) {
        FUN_0007e2fa(0x00099cbdu, 0x000f06fcu, 0x000f0692u, 0xb7u,
                     context);
        FUN_0007e2fa(0x000f0722u, length);
        FUN_0007e2ec(0x000f0692u, 0xb7u);
    }

    FUN_0007e0a6(FUN_0007de24(object, start), start);
}
