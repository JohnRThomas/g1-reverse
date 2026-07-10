/* rodata_0x4e2a0: const pointer table, 5 x uint32 (5 flash)
 * app-core VA 0x4e2a0, 20 bytes. Reader(s): FUN_0004e1ac
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4e2a0[5] = {
    0x000f1052, /* flash */
    0x000880d8, /* flash */
    0x000f1080, /* flash */
    0x000f10a4, /* flash */
    0x000f10ba, /* flash */
};
