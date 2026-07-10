/* rodata_0x42d30: const pointer table, 5 x uint32 (2 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x42d30, 20 bytes. Reader(s): FUN_00042c8c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x42d30[5] = {
    0x2000230c,
    0x20007554,
    0x000aa763,
    0x000aa679,
    0x000aa6a3,
};
