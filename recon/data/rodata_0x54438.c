/* rodata_0x54438: const pointer table, 3 x uint32 (2 flash, 1 SRAM)
 * app-core VA 0x54438, 12 bytes. Reader(s): FUN_000543d8
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x54438[3] = {
    0x000f3103, /* flash */
    0x00088138, /* flash */
    0x2000214c, /* sram */
};
