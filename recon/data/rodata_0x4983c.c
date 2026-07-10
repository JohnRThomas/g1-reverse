/* rodata_0x4983c: const pointer table, 7 x uint32 (3 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x4983c, 28 bytes. Reader(s): FUN_000497b0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4983c[7] = {
    0x2000230c,
    0x20007554,
    0x000f018c,
    0x000ef01c,
    0x200038c4,
    0x000ef058,
    0x000f0044,
};
