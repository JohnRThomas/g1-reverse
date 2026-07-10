/* rodata_0x4b3b8: const pointer table, 4 x uint32 (0 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x4b3b8, 16 bytes. Reader(s): FUN_0004b2b0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4b3b8[4] = {
    0x000f075e,
    0x000f0692,
    0x00099cbd,
    0x000f0779,
};
