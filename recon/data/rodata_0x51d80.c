/* rodata_0x51d80: const pointer table, 3 x uint32 (3 flash)
 * app-core VA 0x51d80, 12 bytes. Reader(s): FUN_00051c98
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x51d80[3] = {
    0x000f275f, /* flash */
    0x000f2766, /* flash */
    0x000f27cc, /* flash */
};
