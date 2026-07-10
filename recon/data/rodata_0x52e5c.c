/* rodata_0x52e5c: const pointer table, 8 x uint32 (7 flash, 1 SRAM)
 * app-core VA 0x52e5c, 32 bytes. Reader(s): FUN_00052d58
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x52e5c[8] = {
    0x200020d4, /* sram */
    0x000f2b65, /* flash */
    0x00088178, /* flash */
    0x0009a1dd, /* flash */
    0x000f2b86, /* flash */
    0x000f2baa, /* flash */
    0x000f33e4, /* flash */
    0x000f2bcf, /* flash */
};
