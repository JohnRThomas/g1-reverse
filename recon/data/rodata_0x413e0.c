/* rodata_0x413e0: const pointer table, 7 x uint32 (3 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x413e0, 28 bytes. Reader(s): FUN_00040794
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x413e0[7] = {
    0x000aae20,
    0x20004bf0,
    0x2001cdce,
    0x20009ff4,
    0x000f7a30,
    0x000f341d,
    0x000a8c57,
};
