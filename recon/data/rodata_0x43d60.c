/* rodata_0x43d60: const pointer table, 6 x uint32 (3 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x43d60, 24 bytes. Reader(s): FUN_00043bd8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x43d60[6] = {
    0x2000230c,
    0x20007554,
    0x000aacc8,
    0x000aa96d,
    0x000aa9a3,
    0x2000a034,
};
