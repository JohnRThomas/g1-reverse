/* rodata_0x3feb4: const pointer table, 6 x uint32 (3 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x3feb4, 24 bytes. Reader(s): FUN_0003fd44
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3feb4[6] = {
    0x2000230c,
    0x20007554,
    0x000aa5ab,
    0x000aa487,
    0x200024f4,
    0x000aa4ea,
};
