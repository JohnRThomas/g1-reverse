/* rodata_0x456e4: const pointer table, 6 x uint32 (3 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x456e4, 24 bytes. Reader(s): FUN_000455cc
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x456e4[6] = {
    0x2000a034,
    0x000aac9f,
    0x000aac62,
    0x000aac83,
    0x2000230c,
    0x20007554,
};
