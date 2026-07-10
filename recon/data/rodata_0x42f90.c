/* rodata_0x42f90: const pointer table, 8 x uint32 (5 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x42f90, 32 bytes. Reader(s): FUN_00042d44
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x42f90[8] = {
    0x20004bf0,
    0x2000230c,
    0x20007554,
    0x000aa78f,
    0x000aa6ce,
    0x200034f5,
    0x2001cdce,
    0x000aa725,
};
