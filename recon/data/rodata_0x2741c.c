/* rodata_0x2741c: literal/pointer table, 11 x uint32 (2 SRAM ptr, 9 flash ptr)
 * app-core VA 0x2741c, 44 bytes emitted. Reader(s): sync_to_slave
 * full table (naddr==span/4)
 */
#include <stdint.h>
const uint32_t rodata_0x2741c[11] = {
    0x2000230c, /* SRAM */
    0x20007554, /* SRAM */
    0x000a1ab1, /* flash */
    0x0009ff92, /* flash */
    0x0009ffc4, /* flash */
    0x000a0000, /* flash */
    0x000a0032, /* flash */
    0x000a0066, /* flash */
    0x000a009a, /* flash */
    0x000a0102, /* flash */
    0x000a00d0, /* flash */
};
