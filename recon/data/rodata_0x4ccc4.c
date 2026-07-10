/* rodata_0x4ccc4: const pointer table, 4 x uint32 (4 flash)
 * app-core VA 0x4ccc4, 16 bytes. Reader(s): FUN_0004cc50
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4ccc4[4] = {
    0x000f0c5e, /* flash */
    0x000881d8, /* flash */
    0x000f0c6f, /* flash */
    0x000f0c14, /* flash */
};
