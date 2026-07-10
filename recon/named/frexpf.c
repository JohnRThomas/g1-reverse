/* named: frexpf */
/* Reconstructed frexpf @ 0x759b8  (parity: 300/300 trials, PROVEN) */

float frexpf(float param_1, volatile int *param_2)
{
  union { float f; unsigned int u; } uu;
  unsigned int r3, r2, fVar1;
  int off;

  uu.f = param_1;
  r3 = uu.u;
  r2 = r3 & ~0x80000000u;
  *param_2 = 0;
  fVar1 = r2 - 1;
  if (fVar1 < 0x7f7fffffu) {
    off = 0;
    if ((r3 & 0x7f800000u) == 0) {
      param_1 = param_1 * 33554432.0f;
      off = -0x19;
      *param_2 = off;
      uu.f = param_1;
      r3 = uu.u;
      r2 = r3 & ~0x80000000u;
    }
    r2 = ((int)r2) >> 0x17;
    r3 = r3 & ~0x7f800000u;
    r3 = r3 | 0x3f000000u;
    *param_2 = off + (int)r2 - 0x7e;
    uu.u = r3;
    param_1 = uu.f;
  }
  return param_1;
}

