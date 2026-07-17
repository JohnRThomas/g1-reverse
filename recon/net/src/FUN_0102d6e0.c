/* net-core FUN_0102d6e0 @ 0x0102d6e0 */
#include <stdint.h>

extern int FUN_01039f4c(uint32_t, ...);

uint32_t FUN_0102d6e0(uint32_t state, uint32_t *record, uint32_t key,
                      uint32_t argument)
{
    int found = FUN_01039f4c(state, key, key, argument);
    uint32_t reused = found != 0;
    if (!reused) {
        found = FUN_01039f4c(state, 0x0103cf0au);
    }
    *record = (uint32_t)found;
    return reused;
}
