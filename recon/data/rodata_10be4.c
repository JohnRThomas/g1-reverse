/* rodata_10be4: mixed literal pool (pointers + immediates)
   app-core rodata @ 0x10be4, span 20 bytes (5 x uint32)
   referenced by: fuel_gauge_update
 */
#include <stdint.h>
const uint32_t rodata_10be4[5] = {
    0x00000000,  /* [ 0] imm  f32=0 */
    0x447a0000,  /* [ 1] imm  f32=1000 */
    0x20004790,  /* [ 2] RAM 0x20004790 */
    0x000a3d37,  /* [ 3] flash 0x000a3d37 */
    0x42c80000,  /* [ 4] imm  f32=100 */
};
