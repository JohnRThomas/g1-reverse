/* rodata_0x488a4: const pointer table, 6 x uint32 (3 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x488a4, 24 bytes. Reader(s): FUN_00048840
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x488a4[6] = {
    0x2000392c,
    0x000ef707,
    0x000ef058,
    0x2000230c,
    0x20007554,
    0x000ef4d9,
};
