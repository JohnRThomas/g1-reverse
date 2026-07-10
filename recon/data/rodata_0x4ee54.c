/* rodata_0x4ee54: const pointer table, 5 x uint32 (3 flash, 2 SRAM)
 * app-core VA 0x4ee54, 20 bytes. Reader(s): FUN_0004ed8c
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4ee54[5] = {
    0x2000a28c, /* sram */
    0x0004ea79, /* flash */
    0x2000a15c, /* sram */
    0x000f1574, /* flash */
    0x00088130, /* flash */
};
