/* rodata_0x4e520: const pointer table, 8 x uint32 (6 flash, 2 SRAM)
 * app-core VA 0x4e520, 32 bytes. Reader(s): FUN_0004e494
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4e520[8] = {
    0x000882b0, /* flash */
    0x00088328, /* flash */
    0x000f1158, /* flash */
    0x000f1126, /* flash */
    0x00099cbd, /* flash */
    0x000f0d20, /* flash */
    0x2000a10c, /* sram */
    0x20003868, /* sram */
};
