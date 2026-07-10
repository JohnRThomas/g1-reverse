/* rodata_0x45490: const pointer table, 10 x uint32 (4 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x45490, 40 bytes. Reader(s): FUN_000451e0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x45490[10] = {
    0x2000a034,
    0x2000230c,
    0x20007554,
    0x000aad35,
    0x000aaa58,
    0x200034f6,
    0x00088434,
    0x0008843e,
    0x000aabe8,
    0x000aac1e,
};
