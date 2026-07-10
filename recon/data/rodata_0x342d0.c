/* rodata_0x342d0: const pointer table, 4 x uint32 (3 SRAM ptrs, 1 flash ptrs)
 * app-core VA 0x342d0, 16 bytes. Reader(s): FUN_00034274
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x342d0[4] = {
    0x20007dac,
    0x2001a22a,
    0x20007554,
    0x000a8017,
};
