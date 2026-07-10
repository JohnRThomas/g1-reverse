/* rodata_0x3680c: const pointer table, 5 x uint32 (3 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x3680c, 20 bytes. Reader(s): FUN_0003678c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3680c[5] = {
    0x20009fcc,
    0x000a8e18,
    0x000a8d69,
    0x20009fc4,
    0x20009fc8,
};
