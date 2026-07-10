/* rodata_0x45740: const pointer table, 9 x uint32 (0 SRAM ptrs, 9 flash ptrs)
 * app-core VA 0x45740, 36 bytes. Reader(s): FUN_000456fc
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000xxxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x45740[9] = {
    0x0008aa10,
    0x0008a908,
    0x0008a800,
    0x0008a6f8,
    0x0008a5f0,
    0x0008a4e8,
    0x0008a3e0,
    0x0008ab18,
    0x000bb220,
};
