/* rodata_0x51094: const pointer table, 2 x uint32 (2 SRAM)
 * app-core VA 0x51094, 8 bytes. Reader(s): FUN_00051074
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x51094[2] = {
    0x2000a808, /* sram */
    0x2005314c, /* sram */
};
