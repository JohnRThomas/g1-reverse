/* rodata_0x3fd24: const pointer table, 8 x uint32 (2 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x3fd24, 32 bytes. Reader(s): FUN_00048b5c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3fd24[8] = {
    0x20007554,
    0x000aa412,
    0x000aa0f5,
    0x20007568,
    0x000a9c22,
    0x000a9c63,
    0x000aa166,
    0x000aa1af,
};
