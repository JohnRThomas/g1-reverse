/* rodata_0x44524: const pointer table, 8 x uint32 (3 SRAM ptrs, 5 flash ptrs)
 * app-core VA 0x44524, 32 bytes. Reader(s): FUN_000442bc
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x44524[8] = {
    0x000f02a3,
    0x000aaaac,
    0x2000a034,
    0x000aaab7,
    0x000aad0b,
    0x000aaad4,
    0x2000230c,
    0x20007554,
};
