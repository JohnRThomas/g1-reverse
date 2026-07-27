/* Full reconstruction of FUN_0004ed3c @ 0x4ed3c (66-byte extent). */
#include <stdint.h>

extern uint32_t FUN_0007f4d6(uint32_t collection, uint32_t previous);
extern const uint32_t *FUN_0007f4a0(void);
extern int FUN_00080d3e(const void *key, uint32_t candidate);
extern void FUN_0007e2fa(unsigned long, ...);
extern _Noreturn void FUN_0007e2ec(uintptr_t file, uint32_t line);

uint32_t FUN_0004ed3c(uint32_t collection, const void *key)
{
    uint32_t current = 0;
    for (;;) {
        current = FUN_0007f4d6(collection, current);
        if (current == 0)
            return 0;

        const uint32_t *candidate = FUN_0007f4a0();
        if (candidate == 0) {
            FUN_0007e2fa(0x00099cbdu, 0x000f154au, 0x000f11bcu, 0x21cu);
            FUN_0007e2ec(0x000f11bcu, 0x21cu);
        }
        if (FUN_00080d3e(key, *candidate) == 0)
            return current;
    }
}
