/* rodata_0x4feb0: const pointer table, 6 x uint32 (2 flash, 2 SRAM, 2 const)
 * app-core VA 0x4feb0, 24 bytes. Reader(s): FUN_0004fe34
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4feb0[6] = {
    0x20002ef0, /* sram */
    0x000f1a68, /* flash */
    0xa95c5f2c, /* const */
    0x2000a7d4, /* sram */
    0x000f1a8e, /* flash */
    0x3a00003a, /* const */
};
