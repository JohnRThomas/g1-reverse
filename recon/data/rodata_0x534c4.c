/* rodata_0x534c4: const pointer table, 2 x uint32 (2 flash)
 * app-core VA 0x534c4, 8 bytes. Reader(s): FUN_00080f56
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x534c4[2] = {
    0x000f2d9d, /* flash */
    0x00088138, /* flash */
};
