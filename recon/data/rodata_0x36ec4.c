/* rodata_0x36ec4: const pointer table, 5 x uint32 (1 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x36ec4, 20 bytes. Reader(s): FUN_00036d38
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x36ec4[5] = {
    0x20004950,
    0x000a8ea1,
    0x000a8eb5,
    0x000a8ec6,
    0x000a8edd,
};
