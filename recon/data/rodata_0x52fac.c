/* rodata_0x52fac: const pointer table, 4 x uint32 (3 flash, 1 SRAM)
 * app-core VA 0x52fac, 16 bytes. Reader(s): FUN_00052f68
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x52fac[4] = {
    0x20002000, /* sram */
    0x0009a1dd, /* flash */
    0x000f2c71, /* flash */
    0x00088178, /* flash */
};
