/* rodata_0x27ee4: literal/pointer table, 11 x uint32 (4 SRAM ptr, 7 flash ptr)
 * app-core VA 0x27ee4, 44 bytes emitted. Reader(s): slave_display_thread
 * full table (naddr==span/4)
 */
#include <stdint.h>
const uint32_t rodata_0x27ee4[11] = {
    0x2000230c, /* SRAM */
    0x20007554, /* SRAM */
    0x000a1a43, /* flash */
    0x00099969, /* flash */
    0x20018d96, /* SRAM */
    0x000a0354, /* flash */
    0x000a036a, /* flash */
    0x000a0396, /* flash */
    0x20018d97, /* SRAM */
    0x000a03b3, /* flash */
    0x000a03be, /* flash */
};
