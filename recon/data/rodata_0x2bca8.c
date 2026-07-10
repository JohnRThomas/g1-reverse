/* rodata_0x2bca8: literal/pointer table, 5 x uint32 (2 SRAM ptr, 3 flash ptr)
 * app-core VA 0x2bca8, 20 bytes emitted. Reader(s): FUN_0002bc2c
 * full table (naddr==span/4)
 */
#include <stdint.h>
const uint32_t rodata_0x2bca8[5] = {
    0x2000230c, /* SRAM */
    0x20007554, /* SRAM */
    0x000a254a, /* flash */
    0x000a2470, /* flash */
    0x000a2486, /* flash */
};
