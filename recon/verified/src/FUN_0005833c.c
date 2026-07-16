/* Reconstructed FUN_0005833c @ 0x5833c, exact extent 118 bytes. */
#include <stdint.h>

extern void FUN_0007e2fa(uintptr_t format, ...);
extern void FUN_0007e2ec(uintptr_t file, uint32_t line);
extern void FUN_00086502(uintptr_t queue, void *item);
extern void FUN_00086c78(void *destination, uint32_t value, uint32_t length);

void FUN_0005833c(uint32_t *item)
{
    if (item == 0) {
        FUN_0007e2fa(0x00099cbdu, 0x000f3b6fu, 0x000f4388u, 0xc4u);
        FUN_0007e2ec(0x000f4388u, 0xc4u);
        return;
    }

    uint32_t *owner_item = (uint32_t *)(uintptr_t)(*item + 0x148u);
    uintptr_t address = (uintptr_t)item;
    if (address < 0x2000add4u || address >= 0x2000ae9cu) {
        if (owner_item == item) {
            FUN_00086c78(item, 0u, 0x14u);
            return;
        }
        FUN_0007e2fa(0x00099cbdu, 0x000f43b8u, 0x000f4388u, 0xcdu);
        FUN_0007e2ec(0x000f4388u, 0xcdu);
        return;
    }

    if (owner_item == item) {
        FUN_0007e2fa(0x00099cbdu, 0x000f43b7u, 0x000f4388u, 0xcbu);
        FUN_0007e2ec(0x000f4388u, 0xcbu);
        return;
    }

    FUN_00086c78(item, 0u, 0x14u);
    FUN_00086502(0x20003a28u, item);
}
