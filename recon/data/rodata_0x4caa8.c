/* rodata_0x4caa8: const pointer list, 0xFFFF0000-terminated, 3 x uint32 (2 flash, 1 const)
 * app-core VA 0x4caa8, 12 bytes. Reader(s): FUN_0004c8f8
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4caa8[3] = {
    0x000f0ae4, /* flash */
    0x000881b8, /* flash */
    0xffff0000, /* const */
};
