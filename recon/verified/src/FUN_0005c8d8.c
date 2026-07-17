/* Reconstructed FUN_0005c8d8 @ 0x5c8d8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005306c(unsigned,int);
extern int FUN_00059b5c(unsigned,int);
extern int FUN_0005a044(unsigned,int);
extern void FUN_0005a39c(void);
extern int FUN_000826b2(int,int);
extern void FUN_000828e8(int,int,int,void*);
extern void FUN_00082c9c(int,int,int,void*);
int FUN_0005c8d8(unsigned param_1, int param_2, int param_3){
  uint32_t context[3] = {
    (uint32_t)param_2,
    ((uint32_t)param_2 & 0xffffff00u) | (param_1 & 0xffu),
    (uint32_t)param_3
  };
  int iVar1, iVar2, iVar4;
  int *piVar3;
  FUN_00082c9c(1, 0xffff, 0x0005a2d5, context);
  iVar1 = FUN_0005306c(param_1, param_2);
  if (iVar1 >= 0 && (iVar1 = FUN_0005a044(param_1,param_2)) >= 0){
    iVar1 = FUN_00059b5c(param_1,param_2);
    if (iVar1 != 0) FUN_0005a39c();
    iVar1 = FUN_0005306c(param_1,param_2);
    if (iVar1 >= 0){
      iVar4 = 0; iVar1 = 0x2000af19;
      do {
        if ((unsigned)*(volatile unsigned char*)(iVar1-1) == param_1 &&
            (iVar2 = FUN_000826b2(param_2, iVar1)) != 0){
          iVar4 = iVar4 + 0x2000af18;
          piVar3 = *(int**)(iVar4 + 8);
          if (piVar3 != 0){
            iVar1 = *piVar3;
            if (iVar1 != 0) iVar1 -= 0x18;
            *(volatile unsigned short*)((char*)piVar3 - 8) = 0;
            FUN_000828e8(0, iVar4, 0, piVar3 - 6);
            if (iVar1 != 0){
              while ((iVar2 = *(volatile int*)(iVar1+0x18)) != 0){
                *(volatile unsigned short*)(iVar1+0x10) = 0;
                FUN_000828e8(0, iVar4, 0, (void*)iVar1);
                iVar1 = iVar2 - 0x18;
              }
              *(volatile unsigned short*)(iVar1+0x10) = 0;
              FUN_000828e8(0, iVar4, 0, (void*)iVar1);
            }
          }
          break;
        }
        iVar4 += 0x10;
        iVar1 += 0x10;
      } while (iVar4 != 0x30);
      iVar1 = 0;
    }
  }
  return iVar1;
}
