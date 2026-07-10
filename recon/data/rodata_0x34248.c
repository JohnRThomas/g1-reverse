/* rodata_0x34248: const pointer table, 11 x uint32 (2 SRAM ptrs, 9 flash ptrs)
 * app-core VA 0x34248, 44 bytes. Reader(s): FUN_000340c4
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x34248[11] = {
    0x2000230c,
    0x20007554,
    0x000a831f,
    0x000a7ef6,
    0x000a7f12,
    0x000a7f41,
    0x000a7fae,
    0x000a1f49,
    0x000a8300,
    0x000a7f79,
    0x000a7fe3,
};
