/* rodata_0x3cfb8: const pointer table, 5 x uint32 (3 SRAM ptrs, 2 flash ptrs)
 * app-core VA 0x3cfb8, 20 bytes. Reader(s): FUN_0003cf44
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3cfb8[5] = {
    0x20004988,
    0x2000230c,
    0x000a9e7c,
    0x000a994b,
    0x20007554,
};
