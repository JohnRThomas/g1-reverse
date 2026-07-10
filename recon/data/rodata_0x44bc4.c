/* rodata_0x44bc4: const pointer table, 5 x uint32 (3 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x44bc4, 20 bytes. Reader(s): FUN_00044818
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x44bc4[5] = {
    0x2000a034,
    0x2000230c,
    0x20007554,
    0x000aad78,
    0x000aaa7f,
};
