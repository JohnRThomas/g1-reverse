/* named: FUN_00083ede */
/* Reconstructed FUN_00083ede @ 0x83ede  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00061f64(void*);
#define VU(a) (*(volatile unsigned int*)(a))
#define VItt(a) (*(volatile int*)(a))
unsigned int FUN_00083ede(unsigned int *param_1, int param_2, int param_3){
  unsigned int uVar2,uVar4,uVar5,uVar7,uVar3;
  int iVar1;
  unsigned int *puVar6 = param_1 + param_2;
  unsigned int local_2c[2];
  do {
    if (puVar6 == param_1) return 0;
    uVar2 = *param_1;
    uVar4 = uVar2 & 0x7f;
    uVar5 = (uVar2 << 0x13) >> 0x1c;
    if (uVar4 == 0x7f) uVar4 = 0xffffffff;
    local_2c[0] = uVar4;
    switch(uVar2 >> 0x10) {
      case 0: VU(param_3+0x50c)=uVar4; goto L46;
      case 1: VU(param_3+0x514)=uVar4; goto L54;
      case 2: VU(param_3+0x508)=uVar4; goto L46;
      case 3: VU(param_3+0x510)=uVar4; goto L54;
      default: return FUN_00061f64(local_2c);
      case 0xb: VU(param_3+0x508)=uVar4; goto L6e;
      case 0xc: VU(param_3+0x50c)=uVar4;
      L6e: if (uVar5!=0) goto L54;
           if (uVar4!=0xffffffff){ uVar5=6; uVar7=0; uVar2=0; goto Lff4; }
           goto L4a;
      case 0x14: VU(param_3+0x540)=uVar4;
           if (uVar4!=0xffffffff) goto L8e; goto L4a;
      case 0x15: VU(param_3+0x544)=uVar4;
      L54: if (uVar4!=0xffffffff){ uVar7=0; uVar2=uVar7; goto Lff4; } goto L4a;
      case 0x16: VU(param_3+0x560)=uVar4; goto Lb0;
      case 0x17: VU(param_3+0x564)=uVar4; goto Lb0;
      case 0x18: VU(param_3+0x568)=uVar4; goto Lb0;
      case 0x19: VU(param_3+0x56c)=uVar4;
      Lb0: if (uVar4!=0xffffffff){
             if ((int)(*param_1 << 0x11) < 0){
      Lc0:     iVar1=FUN_00061f64(local_2c); VItt(iVar1+8)=1<<(local_2c[0]&0xff);
             } else {
      L8e:     iVar1=FUN_00061f64(local_2c); VItt(iVar1+0xc)=1<<(local_2c[0]&0xff);
             }
             uVar7=1; uVar2=uVar7; goto Lff4;
           }
           goto L4a;
      case 0x1d: VU(param_3+0x524)=uVar4; break;
      case 0x1e: VU(param_3+0x528)=uVar4;
      L46: if (uVar4!=0xffffffff) goto Lc0; goto L4a;
      case 0x1f: VU(param_3+0x530)=uVar4; break;
      case 0x20: VU(param_3+0x534)=uVar4; break;
      case 0x21: VU(param_3+0x538)=uVar4; break;
      case 0x22: VU(param_3+0x53c)=uVar4; break;
    }
    if (uVar4 != 0xffffffff){
      uVar7=0; uVar2=1;
    Lff4:
      uVar3 = *param_1;
      if ((uVar3 & 0x2000)!=0){ uVar2=1; uVar7=0; }
      local_2c[0]=uVar4;
      iVar1=FUN_00061f64(local_2c);
      iVar1 = iVar1 + local_2c[0]*4;
      VU(iVar1+0x200) =
         uVar5<<8 | ((uVar3<<0x17)>>0x1e)<<2 | uVar7 |
         (VU(iVar1+0x200) & 0xfffcf0f0) | uVar2<<1;
    }
    L4a:
    param_1 = param_1 + 1;
  } while(1);
}

