/* rodata_0x3dce8: const pointer table, 10 x uint32 (3 SRAM ptrs, 7 flash ptrs)
 * app-core VA 0x3dce8, 40 bytes. Reader(s): FUN_0003cf44
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3dce8[10] = {
    0x20007554,
    0x000a9e7c,
    0x000a9dba,
    0x000a9d5b,
    0x000a9d87,
    0x000a9da3,
    0x2000230c,
    0x000a9dfb,
    0x000a9e35,
    0x20004988,
};
