/* rodata_0x3c2dc: const pointer table, 16 x uint32 (8 SRAM ptrs, 8 flash ptrs)
 * app-core VA 0x3c2dc, 64 bytes. Reader(s): FUN_0003bfe0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3c2dc[16] = {
    0x200024ec,
    0x0008a3a8,
    0x2001b9a8,
    0x0008a370,
    0x2000230c,
    0x2001b818,
    0x20007554,
    0x000a98ce,
    0x000a9855,
    0x000a9879,
    0x20009fd8,
    0x2000a038,
    0x2001cdd7,
    0x000aae20,
    0x000a989f,
    0x000a8e98,
};
