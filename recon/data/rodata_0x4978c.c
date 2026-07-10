/* rodata_0x4978c: const pointer table, 9 x uint32 (3 SRAM ptrs, 6 flash ptrs)
 * app-core VA 0x4978c, 36 bytes. Reader(s): FUN_0004967c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4978c[9] = {
    0x2000230c,
    0x20007554,
    0x000f019a,
    0x000ef01c,
    0x000effd2,
    0x200038c4,
    0x000ef058,
    0x000efff4,
    0x000f001c,
};
