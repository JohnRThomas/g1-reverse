/* rodata_0x39614: const pointer table, 10 x uint32 (1 SRAM ptrs, 9 flash ptrs)
 * app-core VA 0x39614, 40 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x39614[10] = {
    0x000a8ea1,
    0x000a9009,
    0x000a95e7,
    0x000a902d,
    0x20007554,
    0x000a9082,
    0x000a909f,
    0x000f26c1,
    0x000a90da,
    0x000a90b7,
};
