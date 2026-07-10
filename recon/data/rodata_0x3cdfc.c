/* rodata_0x3cdfc: const pointer table, 2 x uint32 (2 SRAM ptrs, 0 flash ptrs)
 * app-core VA 0x3cdfc, 8 bytes. Reader(s): FUN_0003cb58
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3cdfc[2] = {
    0x2001b9aa,
    0x2001b9ab,
};
