/* rodata_0x53d5c: const pointer table, 5 x uint32 (3 flash, 2 SRAM)
 * app-core VA 0x53d5c, 20 bytes. Reader(s): FUN_00053cd4
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x53d5c[5] = {
    0x20003b4c, /* sram */
    0x000f45be, /* flash */
    0x00099cbd, /* flash */
    0x000f2e84, /* flash */
    0x2000abf4, /* sram */
};
