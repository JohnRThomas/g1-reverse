/* rodata_0x50b14: const pointer table, 2 x uint32 (1 periph-reg, 1 const)
 * app-core VA 0x50b14, 8 bytes. Reader(s): FUN_00050af8
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x50b14[2] = {
    0xe000ed00, /* ppb */
    0x05fa0004, /* const */
};
