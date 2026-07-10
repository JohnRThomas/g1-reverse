/* Reconstructed FUN_00075a0c @ 0x75a0c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef union { float f; uint32_t u; } FU;

float FUN_00075a0c(float param_1, int param_2){
  FU x; x.f = param_1;
  uint32_t r3 = x.u;
  uint32_t r2 = r3 & 0x7fffffffu;
  if (r2 == 0) return param_1;
  if (r2 >= 0x7f800000u) return param_1 + param_1;
  uint32_t uVar2;
  if ((r3 & 0x7f800000u) == 0){
    FU sc; sc.u = 0x4c000000u;
    param_1 = param_1 * sc.f;
    if (param_2 < (int)0xffff3cb0){
      FU c; c.u = 0x0da24260u;
      return c.f * param_1;
    }
    x.f = param_1; r3 = x.u;
    uVar2 = ((r3 >> 0x17) & 0xff) - 0x19;
  } else {
    uVar2 = r2 >> 0x17;
  }
  param_2 = param_2 + (int)uVar2;
  if (param_2 <= 0xfe){
    if (param_2 > 0){
      FU o; o.u = (r3 & ~0x7f800000u) | ((uint32_t)param_2 << 23);
      return o.f;
    }
    if (param_2 >= -0x16){
      param_2 = param_2 + 0x19;
      FU o; o.u = (r3 & ~0x7f800000u) | ((uint32_t)param_2 << 23);
      FU res; res.u = 0x33000000u;
      return o.f * res.f;
    }
    FU s15b; s15b.u = 0x0da24260u;
    FU sel; sel.u = ((int32_t)r3 >= 0) ? 0x0da24260u : 0x8da24260u;
    return sel.f * s15b.f;
  }
  FU s15c; s15c.u = 0x7149f2cau;
  FU sel2; sel2.u = ((int32_t)r3 >= 0) ? 0x7149f2cau : 0xf149f2cau;
  return sel2.f * s15c.f;
}

