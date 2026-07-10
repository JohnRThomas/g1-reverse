/* rodata_0x3ec44: const pointer table, 7 x uint32 (5 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x3ec44, 28 bytes. Reader(s): FUN_0003e7f8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3ec44[7] = {
    0x20010325,
    0x20013dea,
    0x20011d82,
    0x000aae20,
    0x20010322,
    0x2001ba2c,
    0x000a8c57,
};
