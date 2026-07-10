/* rodata_0x421f0: const pointer table, 5 x uint32 (1 SRAM ptrs, 4 flash ptrs)
 * app-core VA 0x421f0, 20 bytes. Reader(s): FUN_000417f8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x421f0[5] = {
    0x000f7b6f,
    0x2001cdd1,
    0x000f7a30,
    0x000aa604,
    0x000aa600,
};
