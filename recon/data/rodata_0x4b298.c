/* rodata_0x4b298: const pointer table, 6 x uint32 (0 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x4b298, 24 bytes. Reader(s): FUN_0004b214
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4b298[6] = {
    0x000f0692,
    0x000f06b3,
    0x00099cbd,
    0x000f06c4,
    0x000f06fc,
    0x000f0722,
};
