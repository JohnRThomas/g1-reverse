/* rodata_0x45834: const pointer table, 3 x uint32 (0 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x45834, 12 bytes. Reader(s): FUN_000457f4
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x45834[3] = {
    0x0008ac2c,
    0x00098e3c,
    0x000e17da,
};
