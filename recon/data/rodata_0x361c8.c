/* rodata_0x361c8: const pointer table, 4 x uint32 (2 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x361c8, 16 bytes. Reader(s): FUN_00036164
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x361c8[4] = {
    0x2000230c,
    0x20007554,
    0x000a8d3a,
    0x000a8cf4,
};
