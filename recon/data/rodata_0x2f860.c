/* rodata_0x2f860: literal/pointer table, 6 x uint32 (4 SRAM ptr, 2 flash ptr)
 * app-core VA 0x2f860, 24 bytes emitted. Reader(s): FUN_0002f80c
 * full table (naddr==span/4)
 */
#include <stdint.h>
const uint32_t rodata_0x2f860[6] = {
    0x20003890, /* SRAM */
    0x2000230c, /* SRAM */
    0x20007554, /* SRAM */
    0x000a4959, /* flash */
    0x000a3f45, /* flash */
    0x200079e4, /* SRAM */
};
