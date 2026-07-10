/* rodata_0x4d6d0: const pointer table, 7 x uint32 (6 flash, 1 SRAM)
 * app-core VA 0x4d6d0, 28 bytes. Reader(s): FUN_0004d678
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4d6d0[7] = {
    0x2001d44c, /* sram */
    0x000882a0, /* flash */
    0x000882b0, /* flash */
    0x000f0cff, /* flash */
    0x000f0cae, /* flash */
    0x00099cbd, /* flash */
    0x000f0d20, /* flash */
};
