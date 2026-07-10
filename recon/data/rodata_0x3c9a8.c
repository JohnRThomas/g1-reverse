/* rodata_0x3c9a8: const pointer table, 3 x uint32 (2 SRAM ptrs, 1 flash ptrs)
 * app-core VA 0x3c9a8, 12 bytes. Reader(s): FUN_0003bfe0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3c9a8[3] = {
    0x000aae20,
    0x2001b818,
    0x20009fd8,
};
