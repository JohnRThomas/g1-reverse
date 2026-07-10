/* rodata_0x49a10: const pointer table, 6 x uint32 (3 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x49a10, 24 bytes. Reader(s): FUN_000499b8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x49a10[6] = {
    0x200038c4,
    0x000f0139,
    0x000ef058,
    0x2000230c,
    0x20007554,
    0x000f008c,
};
