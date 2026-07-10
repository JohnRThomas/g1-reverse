/* rodata_0x355a4: const pointer table, 4 x uint32 (1 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x355a4, 16 bytes. Reader(s): FUN_00035498
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x355a4[4] = {
    0x20007554,
    0x000a8a33,
    0x000a893c,
    0x000a8952,
};
