/* rodata_0x48a1c: const pointer table, 8 x uint32 (4 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x48a1c, 32 bytes. Reader(s): FUN_00048998
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x48a1c[8] = {
    0x2000392c,
    0x000ef6d4,
    0x000ef058,
    0x2000230c,
    0x20007554,
    0x200024f4,
    0x000ef596,
    0x000ef59e,
};
