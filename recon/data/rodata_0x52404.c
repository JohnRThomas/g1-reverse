/* rodata_0x52404: const pointer table, 14 x uint32 (13 flash, 1 SRAM)
 * app-core VA 0x52404, 56 bytes. Reader(s): FUN_000521fc
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x52404[14] = {
    0x000f349f, /* flash */
    0x00085f8d, /* flash */
    0x000f3b6f, /* flash */
    0x00085f97, /* flash */
    0x000f7c24, /* flash */
    0x000f27e3, /* flash */
    0x00085f93, /* flash */
    0x00086007, /* flash */
    0x000a24e0, /* flash */
    0x000f27df, /* flash */
    0x000f27eb, /* flash */
    0x00088208, /* flash */
    0x2000ab7c, /* sram */
    0x000f280b, /* flash */
};
