/* rodata_0x2bddc: literal/pointer table, 5 x uint32 (2 SRAM ptr, 3 flash ptr)
 * app-core VA 0x2bddc, 20 bytes emitted. Reader(s): FUN_0002bd7c
 * full table (naddr==span/4)
 */
#include <stdint.h>
const uint32_t rodata_0x2bddc[5] = {
    0x2000230c, /* SRAM */
    0x20007554, /* SRAM */
    0x000a251a, /* flash */
    0x000a24eb, /* flash */
    0x000a24f9, /* flash */
};
