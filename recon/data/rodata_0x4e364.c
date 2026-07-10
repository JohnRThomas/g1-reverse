/* rodata_0x4e364: const pointer table, 4 x uint32 (4 flash)
 * app-core VA 0x4e364, 16 bytes. Reader(s): FUN_0004e2b4
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4e364[4] = {
    0x000f10ce, /* flash */
    0x000880d8, /* flash */
    0x0007f071, /* flash */
    0x000f1105, /* flash */
};
