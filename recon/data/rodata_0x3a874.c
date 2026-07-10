/* rodata_0x3a874: const pointer table, 3 x uint32 (0 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x3a874, 12 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3a874[3] = {
    0x000a9121,
    0x000f7b6f,
    0x000a91f2,
};
