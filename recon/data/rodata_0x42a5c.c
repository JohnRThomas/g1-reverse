/* rodata_0x42a5c: const pointer table, 2 x uint32 (2 SRAM ptrs, 0 flash ptrs)
 * app-core VA 0x42a5c, 8 bytes. Reader(s): FUN_000429f8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x42a5c[2] = {
    0x2001cdce,
    0x2001cdd1,
};
