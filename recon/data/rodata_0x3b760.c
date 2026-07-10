/* rodata_0x3b760: const pointer table, 11 x uint32 (4 SRAM ptrs, 7 flash ptrs)
 * app-core VA 0x3b760, 44 bytes. Reader(s): FUN_0003af78
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3b760[11] = {
    0x20007554,
    0x000a957d,
    0x000a947f,
    0x2001b816,
    0x000a94c5,
    0x2001b815,
    0x000a94e9,
    0x2001b814,
    0x000a950a,
    0x000a9529,
    0x000a9551,
};
