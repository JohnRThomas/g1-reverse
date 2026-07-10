/* rodata_0x47bec: const pointer table, 3 x uint32 (1 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x47bec, 12 bytes. Reader(s): FUN_00047ba8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x47bec[3] = {
    0x2000392c,
    0x000ef058,
    0x000ef736,
};
