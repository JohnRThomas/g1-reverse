/* rodata_0x3e8b0: const pointer table, 6 x uint32 (3 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x3e8b0, 24 bytes. Reader(s): FUN_0003e7f8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3e8b0[6] = {
    0x20004bb8,
    0x2000230c,
    0x20007554,
    0x000aa425,
    0x000a9f6f,
    0x000aae20,
};
