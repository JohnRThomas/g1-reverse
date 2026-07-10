/* rodata_0x3c644: const pointer table, 6 x uint32 (4 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x3c644, 24 bytes. Reader(s): FUN_0003bfe0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3c644[6] = {
    0x2001b818,
    0x20007b3c,
    0x200024ec,
    0x000aae20,
    0x20009fd8,
    0x000a8e98,
};
