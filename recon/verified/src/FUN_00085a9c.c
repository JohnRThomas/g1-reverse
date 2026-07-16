/* Reconstructed FUN_00085a9c @ 0x85a9c (exact 82-byte extent). */
#include <stdint.h>

extern void FUN_000859b6(void *lock, void *record);
extern uint32_t FUN_000857a8(uint32_t object, uint32_t tag);
extern void FUN_0008567c(uint32_t object, uint32_t item[2], uint32_t zero,
                         uint32_t one);
extern uint64_t FUN_000857e0(uint32_t object);
extern int FUN_000859b2(void *lock, uint32_t inherited_r1, uint32_t zero,
                        uint32_t one);

int FUN_00085a9c(uint8_t *context, uint8_t *record)
{
    uint32_t tag = *(uint32_t *)(record - 8) & 0xffffu;
    void *lock = context + 0x58;
    FUN_000859b6(lock, record);

    uint32_t object = *(uint32_t *)(context + 0xa4);
    uint32_t result = FUN_000857a8(object, tag);
    uint32_t item[2] = {(uint32_t)(uintptr_t)(record - 0x10), result};
    if (*(uint32_t *)(*(uint32_t *)(context + 0xa0) + 0x18) == 0)
        FUN_0008567c(object, item, 0, 1);

    uint64_t inherited = FUN_000857e0(object);
    return FUN_000859b2(lock, (uint32_t)(inherited >> 32), 0, 1);
}
