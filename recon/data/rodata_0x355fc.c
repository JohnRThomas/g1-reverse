/* rodata_0x355fc: const pointer table, 3 x uint32 (1 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x355fc, 12 bytes. Reader(s): FUN_000355b4
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x355fc[3] = {
    0x20007554,
    0x000a8a24,
    0x000a7c9c,
};
