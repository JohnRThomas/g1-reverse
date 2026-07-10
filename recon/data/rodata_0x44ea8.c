/* rodata_0x44ea8: const pointer table, 7 x uint32 (4 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x44ea8, 28 bytes. Reader(s): FUN_00044bd8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x44ea8[7] = {
    0x2000a034,
    0x2000230c,
    0x20007554,
    0x000aad64,
    0x000aaa58,
    0x200034f6,
    0x000aaa7f,
};
