/* rodata_0x4751c: const pointer table, 7 x uint32 (3 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x4751c, 28 bytes. Reader(s): FUN_000473c8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4751c[7] = {
    0x2000230c,
    0x20007554,
    0x000d7426,
    0x000aa891,
    0x0007fc00,
    0x2000a060,
    0x000d7383,
};
