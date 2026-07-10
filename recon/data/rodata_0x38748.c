/* rodata_0x38748: const pointer table, 2 x uint32 (0 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x38748, 8 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x38748[2] = {
    0x000a9121,
    0x000f7b6f,
};
