/* rodata_0x3613c: const pointer table, 10 x uint32 (6 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x3613c, 40 bytes. Reader(s): FUN_00048b5c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3613c[10] = {
    0x20007554,
    0x000a8c60,
    0x200033d3,
    0x2001b80f,
    0x200033d2,
    0x20018d9f,
    0x000a8c80,
    0x000a8c97,
    0x000a8cb6,
    0x2001b80e,
};
