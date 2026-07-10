/* rodata_0x34088: const pointer table, 15 x uint32 (7 SRAM ptrs, 8 flash ptrs)
 * app-core VA 0x34088, 60 bytes. Reader(s): FUN_00033f54
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x34088[15] = {
    0x20007554,
    0x000a8248,
    0x000a7dc5,
    0x2000230c,
    0x000a823b,
    0x000a7ddf,
    0x000a7e0f,
    0x2001a22b,
    0x20007dac,
    0x000a7e3d,
    0x000a7ec3,
    0x000a7e85,
    0x20008eb4,
    0x20009e08,
    0x20009dac,
};
