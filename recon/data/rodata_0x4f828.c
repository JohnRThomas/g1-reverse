/* rodata_0x4f828: const pointer table, 14 x uint32 (11 flash, 3 SRAM)
 * app-core VA 0x4f828, 56 bytes. Reader(s): FUN_0004f770
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4f828[14] = {
    0x000f1754, /* flash */
    0x000f1681, /* flash */
    0x00099cbd, /* flash */
    0x000fa9b4, /* flash */
    0x000faa14, /* flash */
    0x000f16be, /* flash */
    0x2000a2c4, /* sram */
    0x000f08c7, /* flash */
    0x000f0920, /* flash */
    0x000f0935, /* flash */
    0x2000a2c8, /* sram */
    0x000f08f4, /* flash */
    0x000f090b, /* flash */
    0x20002838, /* sram */
};
