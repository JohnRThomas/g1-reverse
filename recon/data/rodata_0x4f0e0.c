/* rodata_0x4f0e0: const pointer table, 3 x uint32 (3 flash)
 * app-core VA 0x4f0e0, 12 bytes. Reader(s): FUN_0004f040
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4f0e0[3] = {
    0x0007f635, /* flash */
    0x000f159e, /* flash */
    0x000880e8, /* flash */
};
