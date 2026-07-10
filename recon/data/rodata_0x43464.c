/* rodata_0x43464: const pointer table, 8 x uint32 (6 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x43464, 32 bytes. Reader(s): FUN_0004334c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x43464[8] = {
    0x2000230c,
    0x20007554,
    0x000aade4,
    0x000aa8eb,
    0x2000f700,
    0x2000f6fe,
    0x2000f702,
    0x2000a034,
};
