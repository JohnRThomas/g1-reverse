/* rodata_0x4cbe0: const pointer table, 3 x uint32 (3 flash)
 * app-core VA 0x4cbe0, 12 bytes. Reader(s): FUN_0004cb90
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4cbe0[3] = {
    0x000f0c03, /* flash */
    0x000881d8, /* flash */
    0x000f0c14, /* flash */
};
