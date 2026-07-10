/* rodata_0x4fad4: const pointer table, 2 x uint32 (2 flash)
 * app-core VA 0x4fad4, 8 bytes. Reader(s): FUN_0004fa34
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4fad4[2] = {
    0x00088454, /* flash */
    0x000f1968, /* flash */
};
