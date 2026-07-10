/* rodata_0x50200: const pointer table, 3 x uint32 (1 flash, 1 SRAM, 1 periph-reg)
 * app-core VA 0x50200, 12 bytes. Reader(s): FUN_000501d4
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x50200[3] = {
    0x2000b448, /* sram */
    0x00098654, /* flash */
    0xe000ed00, /* ppb */
};
