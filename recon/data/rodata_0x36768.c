/* rodata_0x36768: const pointer table, 9 x uint32 (3 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x36768, 36 bytes. Reader(s): FUN_000365ec
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x36768[9] = {
    0x000a8e27,
    0x000a8d69,
    0x000a8d7f,
    0x000a8da5,
    0x000a8da8,
    0x000a8dc1,
    0x20009fc4,
    0x20009fc8,
    0x20009fcc,
};
