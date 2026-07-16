/* Reconstructed FUN_000710b4 @ 0x710b4 */
#include <stdint.h>

extern int FUN_00085508(void *, uint32_t, const void *, uint32_t);
extern void FUN_000859b6(void *);
extern void FUN_000859b2(void *);
extern uint32_t FUN_000857a8(void *, uint16_t);
extern int FUN_0008567c(void *, const void *, int, int, void *);
extern void FUN_000857e0(void *);
extern void FUN_0007e2fa(uint32_t, ...);
extern void FUN_0007e2ec(uint32_t, uint32_t);

uint32_t FUN_000710b4(uint8_t *owner, uint32_t a, uint32_t b,
                      uint8_t *item_end, uint32_t tag)
{
    uint8_t *item = item_end - 16;
    uint16_t id = *(uint32_t *)(item_end - 8);
    uint32_t *pool = *(uint32_t **)(owner + 0xac);
    uint32_t offset = (uint32_t)(uintptr_t)item - pool[0];
    struct { uint32_t a, b, zero; uint16_t tag, pad; } key = {a, b, 0, (uint16_t)tag, 0};
    if (offset >= pool[2]) offset = UINT32_MAX;
    if (FUN_00085508(pool, offset, &key, 16) != 16) {
        FUN_0007e2fa(0x00099cbd, 0x000f7be9, 0x000f7ba6, 0x1af);
        FUN_0007e2ec(0x000f7ba6, 0x1af);
    }
    void *lock = owner + 0x58;
    FUN_000859b6(lock);
    uint32_t value;
    if (*(uint32_t *)(*(uint8_t **)(owner + 0xa0) + 0x18) == 0) {
        value = *(uint32_t *)(owner + 0x94);
    } else {
        value = FUN_000857a8(*(void **)(owner + 0xa8), id);
        if (*(uint32_t *)(*(uint8_t **)(owner + 0xa0) + 0x18) != 0) goto done;
    }
    struct { void *item; uint32_t value; } entry = {item, value};
    if (FUN_0008567c(*(void **)(owner + 0xa8), &entry, 1, 0, item) != 0) {
        FUN_0007e2fa(0x00099cbd, 0x000f7c02, 0x000f7ba6, 0x1bc);
        FUN_0007e2ec(0x000f7ba6, 0x1bc);
    }
done:
    FUN_000857e0(*(void **)(owner + 0xa8));
    FUN_000859b2(lock);
    return tag;
}
