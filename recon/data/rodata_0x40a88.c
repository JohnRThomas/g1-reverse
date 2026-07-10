/* rodata_0x40a88: const pointer table, 7 x uint32 (5 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x40a88, 28 bytes. Reader(s): FUN_00040794
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x40a88[7] = {
    0x2001cdd3,
    0x2001cdce,
    0x20009ff4,
    0x20004bf0,
    0x200034f3,
    0x000aae20,
    0x000a8c57,
};
