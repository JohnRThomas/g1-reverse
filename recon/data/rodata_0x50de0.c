/* rodata_0x50de0: const pointer table, 4 x uint32 (3 flash, 1 periph-reg)
 * app-core VA 0x50de0, 16 bytes. Reader(s): FUN_00050c54
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x50de0[4] = {
    0xe000ed00, /* ppb */
    0x000f217b, /* flash */
    0x000f2158, /* flash */
    0x00088228, /* flash */
};
