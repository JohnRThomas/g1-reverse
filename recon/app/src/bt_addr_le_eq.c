/* Reconstructed bt_addr_le_eq @ 0x00080fa4 (FUN_00080fa4; CFG-verified). */
/* Pinned Zephyr 3.4.99 owner: include/zephyr/bluetooth/addr.h. */
#include <stdbool.h>
#include <stdint.h>
extern int FUN_00086be4(const void *, const void *, uint32_t);
bool bt_addr_le_eq(const void *a, const void *b)
{
    return FUN_00086be4(a, b, 7u) == 0;
}
