/* Full reconstruction FUN_00056300 @ 0x00056300 (128-byte exact extent). */
#include <stdint.h>

extern void *thunk_FUN_000727ac(void *, uint32_t, uint32_t, uint32_t);
extern void FUN_0005f24c(void *);
extern void FUN_00056080(void *, void *);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));
extern uint64_t FUN_000813d6(void *);
extern void FUN_0007350c(unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_00056300(void *context, uint32_t inherited_r1)
{
    uint8_t *base = context;
    for (;;) {
        void *item = thunk_FUN_000727ac(base + 0x38, inherited_r1, 0, 0);
        if (!item) {
            if (*(uint32_t *)(base + 0x14)) {
                FUN_0007e2fa(0x000f3abeu, 0x000f3a5du, 0x00099cbdu, 0x313u);
                FUN_0007e2fa(0x000f3ae4u);
                FUN_0007e2ec(0x000f3a5du, 0x313u);
            }
            if (*(uint32_t *)(base + 0x1c)) {
                FUN_0007e2fa(0x000f3abeu, 0x000f3af9u, 0x000f3a5du, 0x314u);
                FUN_0007e2ec(0x000f3a5du, 0x314u);
            }
            uint64_t released = FUN_000813d6(context);
            FUN_0007350c(base + 0x60, (uint32_t)(released >> 32), 0, 0);
            return;
        }
        void *fragment = *(void **)((uint8_t *)item + 0x18);
        *(void **)((uint8_t *)item + 0x18) = 0;
        FUN_0005f24c(item);
        if (fragment) FUN_00056080(context, fragment);
    }
}
