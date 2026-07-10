/* rodata_0x41a70: const pointer table, 3 x uint32 (3 SRAM ptrs, 0 flash ptrs)
 * app-core VA 0x41a70, 12 bytes. Reader(s): FUN_000417f8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x41a70[3] = {
    0x2001cdd0,
    0x2001cdce,
    0x2001cdd1,
};
