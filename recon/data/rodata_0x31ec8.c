/* rodata_0x31ec8: literal/pointer table, 8 x uint32 (4 SRAM ptr, 4 flash ptr)
 * app-core VA 0x31ec8, 32 bytes emitted. Reader(s): FUN_00031dd8
 * full table (naddr==span/4)
 */
#include <stdint.h>
const uint32_t rodata_0x31ec8[8] = {
    0x000a715d, /* flash */
    0x000a7173, /* flash */
    0x20019ef3, /* SRAM */
    0x000a672f, /* flash */
    0x20007aac, /* SRAM */
    0x20007aa8, /* SRAM */
    0x20007aa4, /* SRAM */
    0x0009ddbf, /* flash */
};
