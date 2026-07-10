/* rodata_0x44af8: const pointer table, 8 x uint32 (4 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x44af8, 32 bytes. Reader(s): FUN_00044818
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x44af8[8] = {
    0x2000a034,
    0x2000230c,
    0x20007554,
    0x000aad78,
    0x000aaa58,
    0x000aab9e,
    0x000aabd2,
    0x200034f6,
};
