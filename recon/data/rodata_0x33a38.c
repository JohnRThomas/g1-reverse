/* rodata_0x33a38: const pointer table, 9 x uint32 (3 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x33a38, 36 bytes. Reader(s): FUN_000338ec
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x33a38[9] = {
    0x2000230c,
    0x20007554,
    0x000a82e2,
    0x000a7c2d,
    0x000a7c4a,
    0x20007da8,
    0x000a82c4,
    0x000a7c9c,
    0x000a7cb6,
};
