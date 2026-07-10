/* rodata_0x4a29c: const pointer table, 2 x uint32 (0 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x4a29c, 8 bytes. Reader(s): FUN_0004a1b8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4a29c[2] = {
    0x00015180,
    0x00099014,
};
