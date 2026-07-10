/* rodata_0x4c2c4: const pointer table, 4 x uint32 (3 flash, 1 periph-reg)
 * app-core VA 0x4c2c4, 16 bytes. Reader(s): FUN_0004c278
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4c2c4[4] = {
    0x000f0a5d, /* flash */
    0x00099cbd, /* flash */
    0x000f0a2b, /* flash */
    0x5002a180, /* periph */
};
