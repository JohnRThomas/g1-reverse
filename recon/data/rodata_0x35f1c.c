/* rodata_0x35f1c: const pointer table, 3 x uint32 (0 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x35f1c, 12 bytes. Reader(s): FUN_00035afc
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x35f1c[3] = {
    0x000a8c34,
    0x000a8c37,
    0x000a8c3a,
};
