/* Full reconstruction FUN_0005f338 @ 0x5f338, exact extent 70 bytes. */
#include <stdint.h>
extern void *FUN_0005f304(void *node);
extern void FUN_0007e2fa(uintptr_t, uintptr_t, uintptr_t, uint32_t);
extern __attribute__((noreturn)) void FUN_0007e2ec(uintptr_t, uint32_t);

void FUN_0005f338(void *owner, void *node)
{
    if (!owner) {
        FUN_0007e2fa(0x00099cbdu, 0x000f5407u, 0x000f539au, 0x241);
        FUN_0007e2ec(0x000f539au, 0x241);
    }
    if (!node) {
        FUN_0007e2fa(0x00099cbdu, 0x000f542du, 0x000f539au, 0x242);
        FUN_0007e2ec(0x000f539au, 0x242);
    }
    void *previous = *(void **)((uint8_t *)owner + 4);
    if (previous)
        *(void **)((uint8_t *)FUN_0005f304(node) + 4) = previous;
    *(void **)((uint8_t *)owner + 4) = node;
}
