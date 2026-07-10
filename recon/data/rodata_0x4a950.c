/* rodata_0x4a950: const pointer table, 4 x uint32 (2 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x4a950, 16 bytes. Reader(s): FUN_0004a890
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4a950[4] = {
    0x2000230c,
    0x20007554,
    0x000f04a9,
    0x000f0337,
};
