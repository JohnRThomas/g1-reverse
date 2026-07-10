/* rodata_0x39a14: const pointer table, 8 x uint32 (2 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x39a14, 32 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x39a14[8] = {
    0x000a8ec6,
    0x000a8edd,
    0x000a9121,
    0x20007554,
    0x000a95e7,
    0x000a9127,
    0x000a915b,
    0x2000d716,
};
