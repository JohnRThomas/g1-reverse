/* rodata_0x4f720: const pointer table, 20 x uint32 (15 flash, 3 SRAM, 2 const)
 * app-core VA 0x4f720, 80 bytes. Reader(s): FUN_0004f5b0
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4f720[20] = {
    0x2000a2c4, /* sram */
    0x000f08c7, /* flash */
    0x000f0920, /* flash */
    0x00099cbd, /* flash */
    0x000f0935, /* flash */
    0x2000a2c8, /* sram */
    0x000f08f4, /* flash */
    0x000f090b, /* flash */
    0x000fa9b4, /* flash */
    0x000f16be, /* flash */
    0x000f1681, /* flash */
    0x2000a2d0, /* sram */
    0x000f5eeb, /* flash */
    0x01000003, /* const */
    0x000880f0, /* flash */
    0x000f1710, /* flash */
    0x000f1722, /* flash */
    0x000f1734, /* flash */
    0x000faa14, /* flash */
    0xaaaaaaab, /* const */
};
