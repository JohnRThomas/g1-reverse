/* rodata_0x2e428: literal/pointer table, 7 x uint32 (4 SRAM ptr, 2 flash ptr, 1 const)
 * app-core VA 0x2e428, 29 bytes emitted. Reader(s): FUN_0002e398
 * full table (naddr==span/4)
 */
#include <stdint.h>
const struct { uint32_t w[7]; uint8_t tail[1]; } rodata_0x2e428 = {
    { 0x20007b54, 0x2000230c, 0x20007554, 0x000a3ab6, 0x000a3a5a, 0x20007b68, 0x41f0e92d },
    { 0x00 },
};
