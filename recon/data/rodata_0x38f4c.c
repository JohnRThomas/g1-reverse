/* rodata_0x38f4c: const pointer table, 6 x uint32 (0 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x38f4c, 24 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x38f4c[6] = {
    0x000a8ec6,
    0x000a9121,
    0x000f7b6f,
    0x000a91db,
    0x000a91f2,
    0x000a9206,
};
