/* rodata_0x2a8c0: literal/pointer table, 7 x uint32 (3 SRAM ptr, 3 flash ptr, 1 const)
 * app-core VA 0x2a8c0, 29 bytes emitted. Reader(s): FUN_0002a868
 * full table (naddr==span/4)
 */
#include <stdint.h>
const struct { uint32_t w[7]; uint8_t tail[1]; } rodata_0x2a8c0 = {
    { 0x20007af0, 0x2000230c, 0x20007554, 0x000a19af, 0x000a18cd, 0x000a18ea, 0x4ff0e92d },
    { 0x04 },
};
