/* rodata_0x3d618: const pointer table, 9 x uint32 (2 SRAM ptrs, 7 flash ptrs)
 * app-core VA 0x3d618, 36 bytes. Reader(s): FUN_0003cf44
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3d618[9] = {
    0x2000230c,
    0x20007554,
    0x000a9e7c,
    0x000a9a39,
    0x000a9a6c,
    0x000a9aa2,
    0x000f26c1,
    0x000a9ad2,
    0x000a9af8,
};
