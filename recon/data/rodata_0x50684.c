/* rodata_0x50684: const pointer table, 10 x uint32 (9 flash, 1 periph-reg)
 * app-core VA 0x50684, 40 bytes. Reader(s): FUN_00050558
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x50684[10] = {
    0x000f1df9, /* flash */
    0x00088258, /* flash */
    0xe000ed00, /* ppb */
    0x000f1e0f, /* flash */
    0x000f1c82, /* flash */
    0x000f1e20, /* flash */
    0x000f1e39, /* flash */
    0x000f1e4e, /* flash */
    0x000f1e69, /* flash */
    0x000f1ce2, /* flash */
};
