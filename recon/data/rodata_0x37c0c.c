/* rodata_0x37c0c: const pointer table, 11 x uint32 (4 SRAM ptrs, 7 flash ptrs)
 * app-core VA 0x37c0c, 44 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x37c0c[11] = {
    0x20007554,
    0x000a95e7,
    0x000a90b7,
    0x000f26c1,
    0x000a915b,
    0x000a917d,
    0x000a9219,
    0x000a922b,
    0x2001197a,
    0x200119ba,
    0x200119da,
};
