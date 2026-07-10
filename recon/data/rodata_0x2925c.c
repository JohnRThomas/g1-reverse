/* rodata_0x2925c: literal/pointer table, 7 x uint32 (4 SRAM ptr, 3 flash ptr)
 * app-core VA 0x2925c, 28 bytes emitted. Reader(s): display_dispatch_thread
 * full table (naddr==span/4)
 */
#include <stdint.h>
const uint32_t rodata_0x2925c[7] = {
    0x20007b3c, /* SRAM */
    0x20018c6e, /* SRAM */
    0x20007554, /* SRAM */
    0x000a1a13, /* flash */
    0x000a0d92, /* flash */
    0x2000a098, /* SRAM */
    0x000a0d77, /* flash */
};
