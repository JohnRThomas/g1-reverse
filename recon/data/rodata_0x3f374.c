/* rodata_0x3f374: const pointer table, 3 x uint32 (0 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x3f374, 12 bytes. Reader(s): FUN_0003f2a8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3f374[3] = {
    0x000aa02b,
    0x000aa056,
    0x000a9da3,
};
