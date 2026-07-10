/* rodata_0x50f30: const pointer table, 7 x uint32 (4 flash, 2 SRAM, 1 periph-reg)
 * app-core VA 0x50f30, 28 bytes. Reader(s): FUN_00050e64
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x50f30[7] = {
    0x2000a7f4, /* sram */
    0xe000ed00, /* ppb */
    0x2001d450, /* sram */
    0x000f219e, /* flash */
    0x000f7a30, /* flash */
    0x00099cbd, /* flash */
    0x000f2201, /* flash */
};
