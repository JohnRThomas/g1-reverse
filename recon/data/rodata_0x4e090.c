/* rodata_0x4e090: const pointer table, 2 x uint32 (1 flash, 1 SRAM)
 * app-core VA 0x4e090, 8 bytes. Reader(s): FUN_0004e048
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4e090[2] = {
    0x20002848, /* sram */
    0x0008adac, /* flash */
};
