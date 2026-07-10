/* rodata_0x53a10: const pointer table, 6 x uint32 (3 flash, 3 SRAM)
 * app-core VA 0x53a10, 24 bytes. Reader(s): FUN_000538f8
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x53a10[6] = {
    0x20003b4c, /* sram */
    0x000f2f59, /* flash */
    0x00088138, /* flash */
    0x2000abf4, /* sram */
    0x000f2f8e, /* flash */
    0x20002000, /* sram */
};
