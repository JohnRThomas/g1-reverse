/* rodata_0x4f030: const pointer table, 4 x uint32 (4 flash)
 * app-core VA 0x4f030, 16 bytes. Reader(s): FUN_0004ee68
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4f030[4] = {
    0x000887b7, /* flash */
    0x000887c8, /* flash */
    0x000887d9, /* flash */
    0x000887ea, /* flash */
};
