#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00076154 @ 0x00076154
 * public-name: atan2f
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atan2f                                   <= FUN_00076154 @ 0x00076154
 * address symbols (name @ address):
 *   rodata_98684                             @ 0x00098684
 *   rodata_98690                             @ 0x00098690
 */
/* Reconstructed FUN_00076154 @ 0x76154  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern float FUN_000768e0(void);
extern void FUN_000868ee(float);
union U{float f; unsigned u; int i;};
static float fb(unsigned u){union U x; x.u=u; return x.f;}
static unsigned bf(float f){union U x; x.f=f; return x.u;}

float atan2f(float param_1, float param_2){
  unsigned b1 = bf(param_1), b2 = bf(param_2);
  unsigned a2 = b2 & 0x7fffffff;
  unsigned a1 = b1 & 0x7fffffff;
  if(a2 < 0x7f800001 && a1 < 0x7f800001){
    if(b2 == 0x3f800000){
      return FUN_000768e0();
    }
    unsigned uVar4 = (((int)b2 >> 30) & 2) | (b1 >> 31);
    if(a1 == 0){
      if(uVar4 == 2) return fb(0x40490fdb);
      return fb(uVar4==3 ? 0xc0490fdb : b1);
    }
    if(a2 != 0){
      if(a2 == 0x7f800000){
        unsigned fbits = 0x00000000; int iVar1 = ((unsigned long)&rodata_98684) /*=0x98684*/;
        if(a1 == 0x7f800000){ fbits = 0x3f490fdb; iVar1 = ((unsigned long)&rodata_98690) /*=0x98690*/; }
        if((uVar4 - 1) > 2) return fb(fbits);
        return *(float*)(iVar1 + (int)((uVar4-1)*4));
      }
      if(a1 != 0x7f800000){
        int diff = (int)a1 - (int)a2;
        int iVar1 = diff >> 0x17;
        float fVar5 = fb(0x3fc90fdb);
        if(diff < 0x1e800000 && ((int)b2 >= 0 || (fVar5 = fb(0x00000000), (iVar1 + 0x3c) >= 0))){
          FUN_000868ee(param_1 / param_2);
          fVar5 = FUN_000768e0();
        }
        if(uVar4 == 1) return fb(bf(fVar5) + 0x80000000);
        if(uVar4 == 2) return fb(0x40490fdb) - (fVar5 + fb(0x33bbbd2e));
        if(uVar4 == 0) return fVar5;
        return (fVar5 + fb(0x33bbbd2e)) - fb(0x40490fdb);
      }
    }
    return fb(((int)b1 >= 0) ? 0x3fc90fdb : 0xbfc90fdb);
  }
  return param_1 + param_2;
}
