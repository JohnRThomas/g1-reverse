/* rodata_0x286c4: literal/pointer table, 14 x uint32 (5 SRAM ptr, 8 flash ptr, 1 const)
 * app-core VA 0x286c4, 57 bytes emitted. Reader(s): slave_display_thread
 * full table (naddr==span/4)
 */
#include <stdint.h>
const struct { uint32_t w[14]; uint8_t tail[1]; } rodata_0x286c4 = {
    { 0x20007554, 0x000a1a43, 0x000a09ac, 0x000a09ee, 0x000a0a04, 0x000a0a2e, 0x000a0a47, 0x20018d9f, 0x000a0a61, 0x20018d8d, 0x000a0a7b, 0x2001cdce, 0x2001b9ab, 0x4604b5f8 },
    { 0x8c },
};
