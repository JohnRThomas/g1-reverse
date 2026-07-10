/* rodata_0x36d1c: const pointer table, 7 x uint32 (3 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x36d1c, 28 bytes. Reader(s): FUN_00048b5c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x36d1c[7] = {
    0x20007554,
    0x000a8e61,
    0x2001b813,
    0x2001b812,
    0x000a8e84,
    0x000aae20,
    0x000a8e98,
};
