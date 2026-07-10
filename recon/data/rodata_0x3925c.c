/* rodata_0x3925c: const pointer table, 11 x uint32 (3 SRAM ptrs, 8 flash ptrs)
 * app-core VA 0x3925c, 44 bytes. Reader(s): FUN_0003727c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3925c[11] = {
    0x20007554,
    0x000a900c,
    0x000a9009,
    0x000a95e7,
    0x000a902d,
    0x20004950,
    0x000a904c,
    0x000a9078,
    0x000a90de,
    0x000a9100,
    0x2000a030,
};
