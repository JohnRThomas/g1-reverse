/* rodata_0x471a4: const pointer table, 10 x uint32 (1 SRAM ptrs, 9 flash ptrs)
 * app-core VA 0x471a4, 40 bytes. Reader(s): FUN_00047148
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x471a4[10] = {
    0x2000a060,
    0x00046fc1,
    0x00046d8d,
    0x00046f21,
    0x00046d2d,
    0x00046dd9,
    0x00035775,
    0x0007d4d7,
    0x0007d4cb,
    0x00046ce9,
};
