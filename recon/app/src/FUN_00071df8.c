/* FUN_00071df8 @ 0x00071df8 — complete 154-byte code reconstruction. */
#include <stdint.h>

extern void FUN_000502c4(uintptr_t, uintptr_t, uintptr_t, uintptr_t,
                         uintptr_t, uintptr_t, uintptr_t);
extern void FUN_0007e2fa(uintptr_t, ...);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));

uintptr_t FUN_00071df8(uint8_t *object, uintptr_t buffer, uint32_t size,
                       uintptr_t operation, uintptr_t arg4, uintptr_t arg5,
                       uintptr_t arg6, int32_t offset, uint32_t tag)
{
    if (!((offset == 15 && operation == 0x00072089u) ||
          (offset != 15 && (uint32_t)(offset + 16) <= 30u))) {
        FUN_0007e2fa(0x00099cbdu, 0x000f7f6eu, 0x000f7f4bu, 0x21au,
                     object, buffer, size, operation);
        FUN_0007e2fa(0x000f7feeu, offset, 14u, 0xfffffff0u);
        FUN_0007e2ec(0x000f7f4bu, 0x21au);
    }

    uintptr_t list = (uintptr_t)(object + 0x58);
    *(uintptr_t *)(object + 0x58) = list;
    *(uintptr_t *)(object + 0x5c) = list;
    object[0x0c] = (uint8_t)tag;
    uint32_t aligned = (size + 7u) & ~7u;
    *(uintptr_t *)(object + 0x7c) = buffer;
    *(uint32_t *)(object + 0x80) = aligned;
    object[0x0e] = (uint8_t)offset;
    uintptr_t end = buffer + aligned;
    object[0x0d] = 4;
    *(uint32_t *)(object + 0x18) = 0;
    *(uint32_t *)(object + 0x1c) = 0;
    *(uint32_t *)(object + 8) = 0;
    object[0x0f] = 0;
    *(uint32_t *)(object + 0x84) = 0;
    FUN_000502c4((uintptr_t)object, buffer, end, operation, arg4, arg5, arg6);
    *(uint32_t *)(object + 0x54) = 0;
    uintptr_t owner = *(uintptr_t *)0x2000b450u;
    *(uint32_t *)(object + 0x74) = 0;
    object[0x70] = 0;
    *(uintptr_t *)(object + 0x88) = owner ? *(uintptr_t *)(owner + 0x88) : 0;
    return end;
}
