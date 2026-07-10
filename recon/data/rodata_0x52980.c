/* rodata_0x52980: const pointer table, 2 x uint32 (1 flash, 1 SRAM)
 * app-core VA 0x52980, 8 bytes. Reader(s): FUN_00052880
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x52980[2] = {
    0x200028ec, /* sram */
    0x00080c8d, /* flash */
};
