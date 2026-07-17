/* net-core FUN_01039f4c @ 0x01039f4c */
#include <stdint.h>

extern uint32_t FUN_0102a244();

uint32_t FUN_01039f4c(uint32_t pool, uint32_t key, uint32_t arg2,
                     uint32_t arg3)
{
    uint32_t slot = FUN_0102a244(key, pool + 0x40u, arg2, arg3, arg3);
    if (slot != 0u) {
        slot = FUN_0102a244(key, pool + 0xb0u);
        if (slot != 0u) {
            return 0u;
        }
        slot = 1u;
    }
    return pool + slot * 0x70u;
}
