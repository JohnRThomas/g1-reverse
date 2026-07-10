/* rodata_0x50bb0: const pointer table, 2 x uint32 (1 SRAM, 1 periph-reg)
 * app-core VA 0x50bb0, 8 bytes. Reader(s): FUN_00050b8c
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x50bb0[2] = {
    0x2000b448, /* sram */
    0xe000ed00, /* ppb */
};
