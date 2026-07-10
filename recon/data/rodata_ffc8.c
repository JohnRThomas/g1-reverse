/* rodata_ffc8: mixed literal pool (pointers + immediates)
   app-core rodata @ 0xffc8, span 60 bytes (15 x uint32)
   referenced by: handle_attitude_trigger
 */
#include <stdint.h>
const uint32_t rodata_ffc8[15] = {
    0x2000230c,  /* [ 0] RAM 0x2000230c */
    0x20007554,  /* [ 1] RAM 0x20007554 */
    0x0009facf,  /* [ 2] flash 0x0009facf */
    0x0009f86d,  /* [ 3] flash 0x0009f86d */
    0x0009f87b,  /* [ 4] flash 0x0009f87b */
    0x20007a94,  /* [ 5] RAM 0x20007a94 */
    0x688369e0,  /* [ 6] imm  f32=4.96466e+24 */
    0x691b2103,  /* [ 7] imm  f32=1.17212e+25 */
    0x4798aa10,  /* [ 8] imm  f32=78164.1 */
    0x688369e0,  /* [ 9] imm  f32=4.96466e+24 */
    0x691baa16,  /* [10] imm  f32=1.17617e+25 */
    0x47982107,  /* [11] imm  f32=77890.1 */
    0xf7fd9811,  /* [12] imm  f32=-1.0287e+34 */
    0xa3a6fc13,  /* [13] imm  f32=-1.81045e-17 */
    0x2300e9d3,  /* [14] imm  f32=6.98841e-18 */
};
