/* rodata_0x35e74: const pointer table, 8 x uint32 (1 SRAM ptrs, 7 flash ptrs)
 * app-core VA 0x35e74, 32 bytes. Reader(s): FUN_00035afc
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x35e74[8] = {
    0x20007554,
    0x000a8ce7,
    0x000a8bcd,
    0x000a8be6,
    0x000a8c37,
    0x000a8c09,
    0x000a8c11,
    0x000f4ca5,
};
