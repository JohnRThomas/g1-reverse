/* rodata_0x4e69c: const pointer table, 3 x uint32 (2 flash, 1 const)
 * app-core VA 0x4e69c, 12 bytes. Reader(s): FUN_0004e604
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4e69c[3] = {
    0x000f1180, /* flash */
    0x01000004, /* const */
    0x00088278, /* flash */
};
