/* rodata_0x4baec: const pointer table, 8 x uint32 (0 SRAM ptrs, 8 flash ptrs)
 * app-core VA 0x4baec, 32 bytes. Reader(s): FUN_0004ba38
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4baec[8] = {
    0x000f08c7,
    0x000f0920,
    0x00099cbd,
    0x000f0935,
    0x000f08f4,
    0x000f090b,
    0x000f094b,
    0x000f0824,
};
