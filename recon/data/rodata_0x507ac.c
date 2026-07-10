/* rodata_0x507ac: const pointer table, 10 x uint32 (9 flash, 1 periph-reg)
 * app-core VA 0x507ac, 40 bytes. Reader(s): FUN_000506ac
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x507ac[10] = {
    0x000f1e81, /* flash */
    0x00088258, /* flash */
    0xe000ed00, /* ppb */
    0x000f1e99, /* flash */
    0x000f1eac, /* flash */
    0x000f1ec6, /* flash */
    0x000f1ef0, /* flash */
    0x000f1f0e, /* flash */
    0x000f1f33, /* flash */
    0x000f1f4d, /* flash */
};
