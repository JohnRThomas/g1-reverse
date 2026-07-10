/* rodata_0x33aa8: const pointer table, 5 x uint32 (2 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x33aa8, 20 bytes. Reader(s): FUN_0002af4c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x33aa8[5] = {
    0x2000230c,
    0x20007554,
    0x000a829f,
    0x000a7cd6,
    0x000a7cf4,
};
