/* rodata_0x39df4: const pointer table, 5 x uint32 (2 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x39df4, 20 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x39df4[5] = {
    0x000a9121,
    0x20007554,
    0x000a95e7,
    0x000a91a4,
    0x200107e3,
};
