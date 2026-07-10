/* rodata_0x4381c: const pointer table, 4 x uint32 (2 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x4381c, 16 bytes. Reader(s): FUN_0007d3dc
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4381c[4] = {
    0x2000230c,
    0x20007554,
    0x000aad1a,
    0x000aa951,
};
