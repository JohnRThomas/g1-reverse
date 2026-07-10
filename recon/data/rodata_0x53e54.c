/* rodata_0x53e54: const pointer table, 8 x uint32 (6 flash, 2 SRAM)
 * app-core VA 0x53e54, 32 bytes. Reader(s): FUN_00053d70
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x53e54[8] = {
    0x2000214c, /* sram */
    0x000f2e84, /* flash */
    0x000a7a10, /* flash */
    0x00099cbd, /* flash */
    0x000f301e, /* flash */
    0x000f304a, /* flash */
    0x00088138, /* flash */
    0x2000abf4, /* sram */
};
