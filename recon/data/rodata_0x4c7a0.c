/* rodata_0x4c7a0: const pointer list, 0xFFFF0000-terminated, 8 x uint32 (7 flash, 1 const)
 * app-core VA 0x4c7a0, 32 bytes. Reader(s): FUN_0004c548
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4c7a0[8] = {
    0x000f0af8, /* flash */
    0x000881b8, /* flash */
    0x000f0b1a, /* flash */
    0x000f0b37, /* flash */
    0x000f0b4f, /* flash */
    0x000f0b63, /* flash */
    0x000f0bc0, /* flash */
    0xffff0000, /* const */
};
