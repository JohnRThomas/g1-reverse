/* rodata_0x5451c: const pointer table, 3 x uint32 (3 flash)
 * app-core VA 0x5451c, 12 bytes. Reader(s): FUN_00054444
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x5451c[3] = {
    0x000f2db7, /* flash */
    0x00088138, /* flash */
    0x000f3125, /* flash */
};
