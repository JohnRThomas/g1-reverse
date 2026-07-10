/* rodata_0x34508: const pointer table, 7 x uint32 (4 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x34508, 28 bytes. Reader(s): FUN_0003444c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x34508[7] = {
    0x2001a22a,
    0x20007dac,
    0x2000230c,
    0x20007554,
    0x000a820f,
    0x000a80e3,
    0x000a8146,
};
