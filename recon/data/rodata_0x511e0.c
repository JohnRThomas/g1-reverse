/* rodata_0x511e0: const pointer table, 4 x uint32 (3 flash, 1 SRAM)
 * app-core VA 0x511e0, 16 bytes. Reader(s): FUN_00051180
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x511e0[4] = {
    0x2000a80c, /* sram */
    0x000a7a10, /* flash */
    0x000f2459, /* flash */
    0x00099cbd, /* flash */
};
