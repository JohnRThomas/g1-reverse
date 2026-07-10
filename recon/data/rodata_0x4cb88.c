/* rodata_0x4cb88: const pointer table, 2 x uint32 (2 flash)
 * app-core VA 0x4cb88, 8 bytes. Reader(s): FUN_0004cab4
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4cb88[2] = {
    0x000f0ae4, /* flash */
    0x000881b8, /* flash */
};
