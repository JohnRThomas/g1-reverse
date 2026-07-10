/* rodata_0x4d264: const pointer table, 4 x uint32 (4 flash)
 * app-core VA 0x4d264, 16 bytes. Reader(s): FUN_0004d170
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4d264[4] = {
    0x000f0c94, /* flash */
    0x0008844c, /* flash */
    0x000f0c9e, /* flash */
    0x0008ac74, /* flash */
};
