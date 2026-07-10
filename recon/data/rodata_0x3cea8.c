/* rodata_0x3cea8: const pointer table, 5 x uint32 (2 SRAM ptrs, 3 flash ptrs)
 * app-core VA 0x3cea8, 20 bytes. Reader(s): FUN_0003ce04
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3cea8[5] = {
    0x2000230c,
    0x20007554,
    0x000a9935,
    0x000a98de,
    0x000a9909,
};
