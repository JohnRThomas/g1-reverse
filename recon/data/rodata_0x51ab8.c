/* rodata_0x51ab8: const pointer table, 2 x uint32 (2 flash)
 * app-core VA 0x51ab8, 8 bytes. Reader(s): FUN_00051a5c
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x51ab8[2] = {
    0x000f25fb, /* flash */
    0x00088208, /* flash */
};
