/* rodata_0x50a04: const pointer table, 20 x uint32 (18 flash, 1 periph-reg, 1 const)
 * app-core VA 0x50a04, 80 bytes. Reader(s): FUN_000507d4
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x50a04[20] = {
    0xe000ed00, /* ppb */
    0x000f1fa6, /* flash */
    0x00088258, /* flash */
    0x000f1fd1, /* flash */
    0x000f1d11, /* flash */
    0x00099cbd, /* flash */
    0x000f1fe4, /* flash */
    0x000f2022, /* flash */
    0x000f2039, /* flash */
    0x000f205a, /* flash */
    0x000f2068, /* flash */
    0x000f2087, /* flash */
    0x000f7a30, /* flash */
    0x000f20a3, /* flash */
    0x000f20c7, /* flash */
    0x000f20f7, /* flash */
    0x000f1f8d, /* flash */
    0x000f1f78, /* flash */
    0x000f211b, /* flash */
    0x01000004, /* const */
};
