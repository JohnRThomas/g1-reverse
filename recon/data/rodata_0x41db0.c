/* rodata_0x41db0: const pointer table, 7 x uint32 (2 SRAM ptrs, 5 flash ptrs)
 * app-core VA 0x41db0, 28 bytes. Reader(s): FUN_000417f8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x41db0[7] = {
    0x2001cdd1,
    0x2001cdd2,
    0x000aa608,
    0x000aa60e,
    0x000f212c,
    0x000f341d,
    0x000aa604,
};
