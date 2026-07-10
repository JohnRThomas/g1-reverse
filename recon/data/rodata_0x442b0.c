/* rodata_0x442b0: const pointer table, 3 x uint32 (1 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x442b0, 12 bytes. Reader(s): FUN_000440ec
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x442b0[3] = {
    0x2000a034,
    0x000883ec,
    0x00088410,
};
