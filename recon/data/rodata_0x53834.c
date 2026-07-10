/* rodata_0x53834: const pointer table, 15 x uint32 (10 flash, 5 SRAM)
 * app-core VA 0x53834, 60 bytes. Reader(s): FUN_000536b8
 * Thumb literal pool: 32-bit words (flash 0x000xxxxx rodata/code ptrs, SRAM 0x2000xxxx, periph 0x4/0x5/0xE000xxxx regs). */
#include <stdint.h>
const uint32_t rodata_0x53834[15] = {
    0x20002144, /* sram */
    0x000f2e84, /* flash */
    0x000f2eb8, /* flash */
    0x00099cbd, /* flash */
    0x2000ff08, /* sram */
    0x000f2ed1, /* flash */
    0x00088138, /* flash */
    0x000f2ef5, /* flash */
    0x20002000, /* sram */
    0x20002980, /* sram */
    0x20005f08, /* sram */
    0x000f2ddb, /* flash */
    0x000f2f17, /* flash */
    0x0008b190, /* flash */
    0x000f2f45, /* flash */
};
