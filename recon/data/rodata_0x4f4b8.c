/* rodata_0x4f4b8: const pointer table, 24 x uint32 (3 flash, 5 SRAM, 7 periph-reg, 9 const)
 * app-core VA 0x4f4b8, 96 bytes. Reader(s): FUN_000181f0, FUN_0004f418, FUN_0004f518
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x4f4b8[24] = {
    0x0007f895, /* flash */
    0x000f1625, /* flash */
    0x000881c0, /* flash */
    0x689b4b03, /* const */
    0x1e48b11b, /* const */
    0x2001bf18, /* sram */
    0x47704718, /* periph */
    0x2000a2b8, /* sram */
    0x461cb510, /* periph */
    0x46114b03, /* periph */
    0xb10b681b, /* const */
    0x47984622, /* periph */
    0xbd104620, /* const */
    0x2000a2b8, /* sram */
    0x685b4b02, /* const */
    0x4718b103, /* periph */
    0xbf004770, /* const */
    0x2000a2b8, /* sram */
    0x4b04b130, /* periph */
    0x601a6802, /* const */
    0x605a6842, /* const */
    0x609a6882, /* const */
    0x47702000, /* periph */
    0x2000a2b8, /* sram */
};
