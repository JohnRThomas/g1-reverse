/* rodata_0x4bc80: const pointer table, 3 x uint32 (0 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x4bc80, 12 bytes. Reader(s): FUN_0004bc28
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4bc80[3] = {
    0x000a7a10,
    0x00099cbd,
    0x000f0982,
};
