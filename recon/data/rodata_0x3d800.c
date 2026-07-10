/* rodata_0x3d800: const pointer table, 8 x uint32 (4 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x3d800, 32 bytes. Reader(s): FUN_0003cf44
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3d800[8] = {
    0x2000230c,
    0x000a9e7c,
    0x000a9b45,
    0x000a9b76,
    0x20004988,
    0x200049b8,
    0x20007554,
    0x000a9bfc,
};
