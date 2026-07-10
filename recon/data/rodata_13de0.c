/* rodata_13de0: numeric constant table
   app-core rodata @ 0x13de0, span 124 bytes (31 x uint32)
   referenced by: FUN_000133f8
   NOTE: doubles (exp/log range + polynomial coeffs); last 8 bytes are a
         tiny "vldr;bx lr" constant-return helper, kept for byte-exactness.
 */
#include <stdint.h>
const uint32_t rodata_13de0[31] = {
    0x00000000,  /* [ 0] imm  f32=0 */
    0xbff00000,  /* [ 1] imm  f32=-1.875 */
    0xc2f8f359,  /* [ 2] imm  f32=-124.475 */
    0x01a56e1f,  /* [ 3] imm  f32=6.07694e-38 */
    0x00000000,  /* [ 4] imm  f32=0 */
    0x3fe62e43,  /* [ 5] imm  f32=1.79829 */
    0xfefa39ef,  /* [ 6] imm  f32=-1.66304e+38 */
    0x3fe62e42,  /* [ 7] imm  f32=1.79829 */
    0x0ca86c39,  /* [ 8] imm  f32=2.59496e-31 */
    0xbe205c61,  /* [ 9] imm  f32=-0.156602 */
    0x72bea4d0,  /* [10] imm  f32=7.55218e+30 */
    0x3e663769,  /* [11] imm  f32=0.224821 */
    0xc5d26bf1,  /* [12] imm  f32=-6733.49 */
    0x3ebbbd41,  /* [13] imm  f32=0.366678 */
    0xaf25de2c,  /* [14] imm  f32=-1.50856e-10 */
    0x3f11566a,  /* [15] imm  f32=0.567725 */
    0x16bebd93,  /* [16] imm  f32=3.08158e-25 */
    0x3f66c16c,  /* [17] imm  f32=0.901389 */
    0x5555553e,  /* [18] imm  f32=1.46601e+13 */
    0x3fc55555,  /* [19] imm  f32=1.54167 */
    0x4090cbff,  /* [20] imm  f32=4.5249 */
    0x3f6f3400,  /* [21] imm  f32=0.934387 */
    0x3fe00000,  /* [22] imm  f32=1.75 */
    0xfff00000,  /* [23] imm  f32=nan */
    0x3ff00000,  /* [24] imm  f32=1.875 */
    0x652b82fe,  /* [25] imm  f32=5.06213e+22 */
    0x3c971547,  /* [26] imm  f32=0.0184428 */
    0x00000000,  /* [27] imm  f32=0 */
    0x0b01ed9f,  /* [28] imm  f32=2.50233e-32 */
    0xbf004770,  /* [29] imm  f32=-0.50109 */
    0x00000000,  /* [30] imm  f32=0 */
};
