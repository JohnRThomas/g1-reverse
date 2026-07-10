/* rodata_0x281d0: literal/pointer table, 12 x uint32 (2 SRAM ptr, 10 flash ptr)
 * app-core VA 0x281d0, 48 bytes emitted. Reader(s): slave_display_thread
 * full table (naddr==span/4)
 */
#include <stdint.h>
const uint32_t rodata_0x281d0[12] = {
    0x20007554, /* SRAM */
    0x000a1a43, /* flash */
    0x000a03d9, /* flash */
    0x000a03f5, /* flash */
    0x000a0434, /* flash */
    0x000a044e, /* flash */
    0x000a0477, /* flash */
    0x000a04cb, /* flash */
    0x20007b38, /* SRAM */
    0x000a050a, /* flash */
    0x000a052d, /* flash */
    0x000a0568, /* flash */
};
