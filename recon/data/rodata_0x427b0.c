/* rodata_0x427b0: const pointer table, 4 x uint32 (2 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x427b0, 16 bytes. Reader(s): FUN_000417f8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x427b0[4] = {
    0x2001cdd1,
    0x2001cdd2,
    0x000f341d,
    0x000f7a30,
};
