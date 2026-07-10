/* rodata_0x4ed80: const pointer table, 3 x uint32 (3 flash)
 * app-core VA 0x4ed80, 12 bytes. Reader(s): FUN_0004ed3c
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4ed80[3] = {
    0x000f154a, /* flash */
    0x00099cbd, /* flash */
    0x000f11bc, /* flash */
};
