/* rodata_0x4ea18: const pointer table, 4 x uint32 (3 flash, 1 SRAM)
 * app-core VA 0x4ea18, 16 bytes. Reader(s): FUN_0004e9a0
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4ea18[4] = {
    0x2000a154, /* sram */
    0x000f1237, /* flash */
    0x00088130, /* flash */
    0x000f1253, /* flash */
};
