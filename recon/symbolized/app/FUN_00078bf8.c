#include "g1_app_symbols.h"
/* named: FUN_00078bf8 */
/* Reconstructed FUN_00078bf8 @ 0x78bf8  (parity: 300/300 trials, PROVEN) */

static unsigned int shr_arm(unsigned int val, unsigned int amt) {
    amt &= 0xff;
    if (amt >= 32) return 0;
    return val >> amt;
}

double FUN_00078bf8(double d0)
{
  union { double d; struct { unsigned int lo; unsigned int hi; } s; } uu, out;
  unsigned int uStack_4, uVar1, uVar3, mag, lo, hi;
  int iVar2;

  uu.d = d0;
  uStack_4 = uu.s.hi;
  iVar2 = (int)((uStack_4 & 0x7ff00000u) - 0x3400000u);

  if (iVar2 < 1) {
    mag = (unsigned int)(-iVar2);
    uVar1 = mag >> 0x14;
    if (mag > 0x13fffff) {
      uVar3 = uVar1 - 0x14;
      if ((int)uVar3 <= 0x1e) {
        lo = shr_arm(0x80000000u, uVar3);
      } else {
        lo = 1;
      }
      hi = 0;
    } else {
      hi = shr_arm(((uintptr_t)&rodata_80000) /*=0x80000*/, uVar1);
      lo = 0;
    }
  } else {
    lo = 0;
    hi = (unsigned int)iVar2;
  }
  out.s.lo = lo;
  out.s.hi = hi;
  return out.d;
}

