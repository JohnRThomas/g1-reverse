/* rodata_0x38268: const pointer table, 6 x uint32 (1 SRAM ptrs, 5 flash ptrs)
 * app-core VA 0x38268, 24 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x38268[6] = {
    0x20007554,
    0x000a95e7,
    0x000a9127,
    0x000a915b,
    0x000a916c,
    0x000a9121,
};
