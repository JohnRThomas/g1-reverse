/* rodata_0x33d50: const pointer table, 2 x uint32 (2 SRAM ptrs, 0 flash ptrs)
 * app-core VA 0x33d50, 8 bytes. Reader(s): FUN_00033cf8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x33d50[2] = {
    0x20007dac,
    0x2001a22a,
};
