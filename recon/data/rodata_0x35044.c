/* rodata_0x35044: const pointer table, 3 x uint32 (2 SRAM ptrs, 1 flash ptrs)
 * app-core VA 0x35044, 12 bytes. Reader(s): FUN_00034ff0
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x35044[3] = {
    0x2001a22c,
    0x20007554,
    0x000a8750,
};
