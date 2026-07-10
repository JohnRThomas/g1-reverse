/* Reconstructed FUN_0005af8c @ 0x5af8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00059edc(int,...);
extern int FUN_00077c1c(int,...);
extern int FUN_0007f1a0(int,...);
extern int FUN_0007f1e8(int,...);
extern int FUN_00080cf2(int,...);
extern int FUN_00082a42(int,...);
extern int FUN_00082c9c(int,...);
typedef int (*codeptr)(int,...);
unsigned int FUN_0005af8c(int param_1,int param_2,codeptr param_3,int param_4,int param_5)
{
  int iVar1;
  unsigned int uVar2;
  int local_100, local_fc;
  unsigned int uStack_108;
  unsigned char af8[8];
  unsigned char ae0[16];
  int dummy[16];
  iVar1 = FUN_0007f1a0(param_5, 0xf4a9e, &local_100);
  if (iVar1 == 0) {
    uVar2 = FUN_00059edc(0);
  } else {
    FUN_0007f1e8(local_100, &local_fc);
    if (local_100 == 0) {
      FUN_00082a42(0x88128, 0x1040, dummy);
    } else {
      if ((local_fc == 0) || (uStack_108 = FUN_00077c1c(local_fc,0,10), uStack_108 == 0)) {
        iVar1 = FUN_00080cf2(local_100, af8);
        if (iVar1 == 0) {
          if (param_2 == 0) {
          } else {
            unsigned int uStack_e4 = (unsigned int)param_3(param_4, (int)ae0, 0xc0);
            if ((int)uStack_e4 < 0) {
              FUN_00082a42(0x88128, 0x1840, dummy);
              return uStack_e4;
            }
          }
          FUN_00082c9c(1, 0xffff, 0x59ded, dummy);
          return 0;
        }
        FUN_00082a42(0x88128, 0x1c40, dummy);
      } else {
        FUN_00082a42(0x88128, 0x1840, dummy);
      }
    }
    uVar2 = 0xffffffea;
  }
  return uVar2;
}

