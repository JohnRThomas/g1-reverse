/* rodata_0x52d3c: const pointer table, 7 x uint32 (6 flash, 1 SRAM)
 * app-core VA 0x52d3c, 28 bytes. Reader(s): FUN_00052cdc
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x52d3c[7] = {
    0x0009a1c8, /* flash */
    0x0009a1ea, /* flash */
    0x2001d452, /* sram */
    0x0009a1cf, /* flash */
    0x0009a1d6, /* flash */
    0x0009a1e0, /* flash */
    0x000f5071, /* flash */
};
