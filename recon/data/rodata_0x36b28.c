/* rodata_0x36b28: const pointer table, 5 x uint32 (5 SRAM ptrs, 0 flash ptrs)
 * app-core VA 0x36b28, 20 bytes. Reader(s): FUN_00036a18
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x36b28[5] = {
    0x200024e4,
    0x200024e0,
    0x200033d4,
    0x2001b811,
    0x2001b810,
};
