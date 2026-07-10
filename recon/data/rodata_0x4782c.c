/* rodata_0x4782c: const pointer table, 6 x uint32 (2 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x4782c, 24 bytes. Reader(s): FUN_000477a0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x4782c[6] = {
    0x2000230c,
    0x20007554,
    0x000d752a,
    0x000d7499,
    0x000d74af,
    0x000d74bd,
};
