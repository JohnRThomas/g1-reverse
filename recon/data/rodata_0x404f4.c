/* rodata_0x404f4: const pointer table, 12 x uint32 (5 SRAM ptrs, 7 flash ptrs)
 * app-core VA 0x404f4, 48 bytes. Reader(s): FUN_00048b5c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x404f4[12] = {
    0x2001cc3e,
    0x20007b3c,
    0x2000230c,
    0x20007554,
    0x000aa599,
    0x000aa56c,
    0x000aa487,
    0x200024f4,
    0x000aa4ea,
    0x000aa517,
    0x000aae20,
    0x000a8c57,
};
