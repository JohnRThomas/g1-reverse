/* rodata_0x416b8: const pointer table, 2 x uint32 (2 SRAM ptrs, 0 flash ptrs)
 * app-core VA 0x416b8, 8 bytes. Reader(s): FUN_00040794
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x416b8[2] = {
    0x2001cdd1,
    0x2001cdce,
};
