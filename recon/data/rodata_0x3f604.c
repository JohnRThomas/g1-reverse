/* rodata_0x3f604: const pointer table, 14 x uint32 (8 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x3f604, 56 bytes. Reader(s): FUN_00048b5c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3f604[14] = {
    0x20004bb8,
    0x2000230c,
    0x000aa412,
    0x000aa0ae,
    0x000aa0d7,
    0x2001ba2e,
    0x2001ba2d,
    0x20007554,
    0x000aa112,
    0x20010326,
    0x20010325,
    0x2001ba2c,
    0x000aa138,
    0x000a9dba,
};
