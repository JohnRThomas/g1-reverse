/* rodata_0x48ab4: const pointer table, 8 x uint32 (3 SRAM ptrs, 5 flash ptrs)
 * app-core VA 0x48ab4, 32 bytes. Reader(s): FUN_00048a3c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x48ab4[8] = {
    0x2000392c,
    0x000ef6b0,
    0x000ef058,
    0x2000230c,
    0x20007554,
    0x000ef5f3,
    0x000ef5df,
    0x000ef603,
};
