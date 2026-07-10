/* rodata_0x38adc: const pointer table, 8 x uint32 (2 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x38adc, 32 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x38adc[8] = {
    0x000a9078,
    0x20007554,
    0x000a95e7,
    0x000a90de,
    0x000a9100,
    0x2000a030,
    0x000a8ea1,
    0x000a8eb5,
};
