/* rodata_0x365d8: const pointer table, 5 x uint32 (3 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x365d8, 20 bytes. Reader(s): FUN_00036558
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x365d8[5] = {
    0x20009fcc,
    0x000a8e48,
    0x000a8d69,
    0x20009fc4,
    0x20009fc8,
};
