/* rodata_0x46b6c: const pointer table, 5 x uint32 (3 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x46b6c, 20 bytes. Reader(s): FUN_000469bc
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x46b6c[5] = {
    0x2000230c,
    0x20007554,
    0x000d71f9,
    0x000d7173,
    0x2001cf8f,
};
