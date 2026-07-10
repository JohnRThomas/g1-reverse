/* rodata_0x37e9c: const pointer table, 8 x uint32 (2 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x37e9c, 32 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x37e9c[8] = {
    0x000a9121,
    0x000f7b6f,
    0x20007554,
    0x000a95e7,
    0x000a9127,
    0x000a914d,
    0x000a9155,
    0x2000d716,
};
