/* rodata_0x48e10: const pointer table, 6 x uint32 (3 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x48e10, 24 bytes. Reader(s): FUN_00048b5c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x48e10[6] = {
    0x2000a098,
    0x2000230c,
    0x20007554,
    0x000f01eb,
    0x000ef784,
    0x000ef7a0,
};
