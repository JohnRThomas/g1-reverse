/* Reconstructed FUN_0005b270 @ 0x5b270  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00058eb0(unsigned,int,int);
extern int FUN_000596c0(int,int);
extern void FUN_00059708(int);
extern int FUN_00059a90(unsigned,int);
extern int FUN_0005b0dc(unsigned,unsigned,int);
extern unsigned FUN_0005f5d0(int,int);
extern void FUN_000825ac(int,int,int,int);
extern void FUN_00082a42(unsigned,int,void*);
extern int FUN_00082cba(unsigned,unsigned,int);
extern void FUN_00086c04(void*,unsigned,unsigned);
int FUN_0005b270(unsigned param_1, unsigned short param_2, int param_3)
{
  unsigned short uVar1; unsigned uVar2; int iVar3, iVar5; unsigned short *puVar4;
  unsigned local_28, local_24;
  iVar3 = FUN_00082cba(param_1, *(unsigned*)(param_3+4), 0x94);
  if (iVar3 == 0) {
    iVar3 = FUN_0005b0dc(param_1, *(unsigned*)(param_3+4), 2);
    if (iVar3 == 0) {
      local_24 = 0x000f4aeb; local_28 = 2; iVar3 = -0x16;
      FUN_00082a42(0x00088128, 0x1080, &local_28);
    } else {
      uVar1 = *(unsigned short*)(param_3+0x14);
      iVar3 = FUN_000596c0(0xf0000, 0);
      uVar2 = 0x000825d5;
      iVar5 = uVar1 + 2;
      if (iVar3 != 0) {
        *(volatile int*)(iVar3+0x14) = iVar5;
        *(volatile unsigned char*)(iVar3+0x11) = 0x1d;
        *(volatile unsigned*)(iVar3+0xc) = 0;
        *(volatile unsigned*)(iVar3+4) = uVar2;
        *(volatile int*)(iVar3+0x18) = param_3;
        iVar5 = FUN_00058eb0(param_1, 0x1d, iVar5);
        if (iVar5 != 0) {
          FUN_000825ac(iVar5, 0, 0, 1);
          puVar4 = (unsigned short*)FUN_0005f5d0(iVar5+0xc, 2);
          *(volatile unsigned short*)puVar4 = param_2;
          FUN_0005f5d0(iVar5+0xc, *(unsigned short*)(param_3+0x14));
          FUN_00086c04(puVar4+1, *(unsigned*)(param_3+0x10), *(unsigned short*)(param_3+0x14));
          *(volatile int*)(iVar3+8) = iVar5;
          iVar5 = FUN_00059a90(param_1, iVar3);
          if (iVar5 == 0) return 0;
          FUN_00059708(iVar3);
          return iVar5;
        }
        local_24 = 0x000f4b16; local_28 = 2;
        FUN_00082a42(0x00088128, 0x1080, &local_28);
        FUN_00059708(iVar3);
      }
      iVar3 = -0xc;
    }
  } else {
    iVar3 = -1;
    local_24 = 0x000f4ad5; local_28 = 2;
    FUN_00082a42(0x00088128, 0x1080, &local_28);
  }
  return iVar3;
}

