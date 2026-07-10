/* rodata_0x36550: const pointer table, 2 x uint32 (0 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x36550, 8 bytes. Reader(s): FUN_000362e8
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x36550[2] = {
    0x000a8d52,
    0x000a8d5d,
};
