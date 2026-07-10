/* rodata_0x4e8b8: const pointer table, 12 x uint32 (2 flash, 3 SRAM, 2 periph-reg, 5 const)
 * app-core VA 0x4e8b8, 48 bytes. Reader(s): FUN_0004e83c, FUN_0004e98c
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4e8b8[12] = {
    0x2000a114, /* sram */
    0x200027fc, /* sram */
    0x4b07b57f, /* periph */
    0x5182f44f, /* periph */
    0x23029305, /* const */
    0xaa044805, /* const */
    0xf0309304, /* const */
    0x2000fd98, /* sram */
    0xf85db007, /* const */
    0xbf00fb04, /* const */
    0x000f11a5, /* flash */
    0x00088130, /* flash */
};
