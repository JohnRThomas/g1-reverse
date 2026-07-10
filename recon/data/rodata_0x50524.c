/* rodata_0x50524: const pointer table, 13 x uint32 (12 flash, 1 periph-reg)
 * app-core VA 0x50524, 52 bytes. Reader(s): FUN_000503d8
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x50524[13] = {
    0x000f1c39, /* flash */
    0x00088258, /* flash */
    0xe000ed00, /* ppb */
    0x000f1c4f, /* flash */
    0x000f1c82, /* flash */
    0x000f1c95, /* flash */
    0x000f1cad, /* flash */
    0x000f1cc3, /* flash */
    0x000f1ce2, /* flash */
    0x000f1d4b, /* flash */
    0x000f1d11, /* flash */
    0x00099cbd, /* flash */
    0x000f1d95, /* flash */
};
