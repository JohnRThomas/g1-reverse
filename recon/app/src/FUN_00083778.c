/* Reconstructed FUN_00083778 @ 0x83778  (parity: 300/300 trials, PROVEN) */

/* Full reconstruction of the 42-byte atomic reference-count helper. */
#include <stdint.h>

extern void FUN_0005f638(void);
void FUN_00083778(uint8_t *param_1)
{
    uint32_t old_count = __atomic_fetch_add((uint32_t *)(param_1 - 8), 1,
                                             __ATOMIC_RELAXED);
    if (old_count != 0) {
        *(int32_t *)(param_1 + 0x68) = -16;
        return;
    }
    FUN_0005f638();
}
