/* rodata_0x51a38: const pointer table, 9 x uint32 (7 flash, 1 SRAM, 1 const)
 * app-core VA 0x51a38, 36 bytes. Reader(s): FUN_000518a8
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x51a38[9] = {
    0x96f3b83d, /* const */
    0x2000ab7c, /* sram */
    0x000f25c5, /* flash */
    0x000f2561, /* flash */
    0x00099cbd, /* flash */
    0x000f25e2, /* flash */
    0x000f25fb, /* flash */
    0x00088208, /* flash */
    0x000f26e7, /* flash */
};
