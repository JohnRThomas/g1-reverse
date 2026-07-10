/* rodata_0x4c8e0: const pointer list, 0xFFFF0000-terminated, 6 x uint32 (5 flash, 1 const)
 * app-core VA 0x4c8e0, 24 bytes. Reader(s): FUN_0004c548
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4c8e0[6] = {
    0x000f0b86, /* flash */
    0x000881b8, /* flash */
    0x000f0b9d, /* flash */
    0x000f0baf, /* flash */
    0x000f0be7, /* flash */
    0xffff0000, /* const */
};
