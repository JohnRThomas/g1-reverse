/* rodata_0x5015c: const pointer table, 5 x uint32 (4 flash, 1 periph-reg)
 * app-core VA 0x5015c, 20 bytes. Reader(s): FUN_0005010c
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x5015c[5] = {
    0x000f1ba8, /* flash */
    0x000f1bde, /* flash */
    0x00099cbd, /* flash */
    0x000f1bf9, /* flash */
    0xe000ed14, /* ppb */
};
