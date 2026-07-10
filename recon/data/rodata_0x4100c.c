/* rodata_0x4100c: const pointer table, 9 x uint32 (2 SRAM ptrs, 7 flash ptrs)
 * app-core VA 0x4100c, 36 bytes. Reader(s): FUN_00040794
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4100c[9] = {
    0x20004bf0,
    0x20009ff4,
    0x000aa608,
    0x000aa60e,
    0x000f212c,
    0x000f7a30,
    0x000f3449,
    0x000aa604,
    0x000aa600,
};
