/* rodata_0x3fbb0: const pointer table, 14 x uint32 (6 SRAM ptrs, 8 flash ptrs)
 * app-core VA 0x3fbb0, 56 bytes. Reader(s): FUN_00048b5c
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3fbb0[14] = {
    0x20007554,
    0x000aa412,
    0x000aa2e9,
    0x2001c336,
    0x000aa311,
    0x000aa341,
    0x2000230c,
    0x000aa370,
    0x000aa3a8,
    0x20004bb8,
    0x2001ba2e,
    0x2001ba2d,
    0x000a9b76,
    0x000aa3ed,
};
