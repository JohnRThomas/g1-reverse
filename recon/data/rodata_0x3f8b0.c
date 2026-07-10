/* rodata_0x3f8b0: const pointer table, 12 x uint32 (4 SRAM ptrs, 8 flash ptrs)
 * app-core VA 0x3f8b0, 48 bytes. Reader(s): FUN_00048b5c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3f8b0[12] = {
    0x20007b3c,
    0x2000230c,
    0x20007554,
    0x000aa412,
    0x000aa204,
    0x000aa23d,
    0x20007568,
    0x000a9c22,
    0x000a9c63,
    0x000aa166,
    0x000aa265,
    0x000aa297,
};
