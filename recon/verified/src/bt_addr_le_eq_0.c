/* Reconstructed bt_addr_le_eq_0 @ 0x826b2  (CFG-directed candidate) */
#include <stdbool.h>
#include <stdint.h>
extern int FUN_00086be4(const void *a, const void *b, uint32_t len);
int bt_addr_le_eq_0(int a, int b) {
    return FUN_00086be4(a, b, 7u) == 0;
}
