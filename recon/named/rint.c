/* readable reconstruction; identity: FUN_000767c8 @ 0x000767c8
 * public-name: rint
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dcmp_negate_rhs                          <= FUN_0000d588 @ 0x0000d588
 *   __aeabi_dadd                             <= FUN_0000d58c @ 0x0000d58c
 *   rint                                     <= FUN_000767c8 @ 0x000767c8
 * address symbols (name @ address):
 *   rodata_40000                             @ 0x00040000
 *   rodata_888a8                             @ 0x000888a8
 */
/* Reconstructed FUN_000767c8 @ 0x767c8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long __aeabi_dadd(unsigned, unsigned, unsigned, unsigned);
extern long long dcmp_negate_rhs(unsigned, unsigned, unsigned, unsigned);
double rint(double dd, unsigned param_1, unsigned param_2, unsigned param_3)
{
  union { double d; unsigned long long u; struct{unsigned lo,hi;} w; } in, out;
  in.d = dd;
  unsigned uVar5 = in.w.hi, uVar4 = in.w.lo;
  unsigned uVar2 = (uVar5 << 1) >> 0x15;
  int iVar1 = (int)uVar5 >> 0x1f;
  unsigned uVar6 = uVar2 - 0x3ff;
  volatile unsigned *puVar3;
  long long uVar9, uVar10;
  unsigned uVar7, uVar8;
  if ((int)uVar6 < 0x14) {
    if ((int)uVar6 < 0) {
      if ((in.u & 0x7fffffff00000000ULL)==0 && uVar4==0) return in.d;
      puVar3 = (volatile unsigned*)(0x888a8 + iVar1*-8);
      uVar7=puVar3[0]; uVar8=puVar3[1];
      unsigned mantissa = (uVar5 & 0xfffffu) | uVar4;
      unsigned normalized_high = (uVar5 & 0xfffe0000u) |
          ((((0u - mantissa) | mantissa) >> 12) & 0x80000u);
      uVar9 = __aeabi_dadd(uVar7,uVar8,uVar4,normalized_high);
      uVar9 = dcmp_negate_rhs((int)uVar9,(int)((unsigned long long)uVar9>>32),uVar7,uVar8);
      out.w.lo = (unsigned)uVar9;
      out.w.hi = (uVar5 & 0x80000000) | ((unsigned)((unsigned long long)uVar9>>32) & 0x7fffffff);
      return out.d;
    }
    uVar2 = 0xfffff >> (uVar6 & 0xff);
    if ((uVar2 & uVar5)==0 && uVar4==0) return in.d;
    uVar4 = uVar4 | (uVar5 & (uVar2 >> 1));
    if (uVar4 != 0) {
      uVar5 = (0x40000 >> (uVar6&0xff)) | (uVar5 & ~(uVar2>>1));
      uVar4 = (unsigned)(uVar6==0x13)*0x80000000U;
    }
  } else {
    if (0x33 < (int)uVar6) {
      if (uVar6 != 0x400) return in.d;
      uVar10 = __aeabi_dadd(uVar4,uVar5,uVar4,uVar5);
      out.w.lo=(unsigned)uVar10; out.w.hi=(unsigned)((unsigned long long)uVar10>>32);
      return out.d;
    }
    uVar2 = uVar2 - 0x413;
    uVar6 = 0xffffffff >> (uVar2&0xff);
    if ((uVar4 & uVar6)==0) return in.d;
    if ((uVar4 & (uVar6>>1))!=0) uVar4 = (0x40000000 >> (uVar2&0xff)) | (uVar4 & ~(uVar6>>1));
  }
  puVar3 = (volatile unsigned*)(0x888a8 + iVar1*-8);
  uVar7=puVar3[0]; uVar8=puVar3[1];
  uVar9 = __aeabi_dadd(uVar7,uVar8,uVar4,uVar5);
  uVar10 = dcmp_negate_rhs((int)uVar9,(int)((unsigned long long)uVar9>>32),uVar7,uVar8);
  out.w.lo=(unsigned)uVar10; out.w.hi=(unsigned)((unsigned long long)uVar10>>32);
  return out.d;
}
