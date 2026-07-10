/* rodata_0x3db08: const pointer table, 16 x uint32 (5 SRAM ptrs, 11 flash ptrs)
 * app-core VA 0x3db08, 64 bytes. Reader(s): FUN_0003cf44
 * Array of 32-bit addresses (SRAM 0x2000xxxx data ptrs, flash 0x000axxxx rodata/string ptrs). */
#include <stdint.h>
const uint32_t rodata_0x3db08[16] = {
    0x000a8b58,
    0x000a9c15,
    0x20009fe0,
    0x20009fdc,
    0x20007564,
    0x20007554,
    0x000a9e7c,
    0x000a9c22,
    0x000a9c63,
    0x000a9cb9,
    0x000a9d04,
    0x00057e3f,
    0x000a9d5b,
    0x000a9d87,
    0x000a9da3,
    0x20009fe4,
};
