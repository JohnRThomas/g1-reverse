/* rodata_0x4d7b0: const pointer table, 10 x uint32 (7 flash, 3 SRAM)
 * app-core VA 0x4d7b0, 40 bytes. Reader(s): FUN_0004d6ec
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4d7b0[10] = {
    0x000882a0, /* flash */
    0x000882b0, /* flash */
    0x000f0d3f, /* flash */
    0x000f0cae, /* flash */
    0x00099cbd, /* flash */
    0x2000a0d0, /* sram */
    0x2000a0d8, /* sram */
    0x200039f8, /* sram */
    0x000f0cff, /* flash */
    0x000f0d20, /* flash */
};
