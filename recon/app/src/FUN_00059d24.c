/* Reconstructed FUN_00059d24 @ 0x59d24  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00059b94(uint32_t,uint32_t);
extern void FUN_0007350c(uint32_t,uint32_t,int,int);
extern void FUN_0007e2ec(uint32_t,int);
extern void FUN_0007e2fa(uint32_t,...);
extern int FUN_00080f92(void);
extern void FUN_000826e0(int,uint32_t);
extern int FUN_0008270c(uint32_t);
extern void FUN_000828da(int,uint32_t,int);

void FUN_00059d24(uint32_t param_1, uint32_t param_2, uint32_t param_3){
  int iVar2 = FUN_00080f92();
  int iVar3 = FUN_00059b94(param_1, param_2);
  if (iVar2 == 0) return;
  if (iVar3 == 0){
    int iVar4;
    int t = FUN_0008270c(0x20006330);
    if (t == 0){ iVar2 = 0; iVar4 = 0; }
    else {
      t = FUN_0008270c(0x2000633c);
      if (t == 0){ iVar4 = 1; iVar2 = 0xc; }
      else {
        t = FUN_0008270c(0x20006348);
        if (t != 0){
          FUN_0007e2fa(0x99cbd,0xf1722,0xf46b8,0x577);
          FUN_0007e2fa(0xf46e8);
          FUN_0007e2ec(0xf46b8,0x577);
        }
        iVar4 = 2; iVar2 = 0x18;
      }
    }
    int iVar1 = 0x20006328;
    iVar3 = iVar2 + 0x20006328;
    FUN_000828da(0x20006328 + iVar2 + 1, param_2, iVar3);
    *(volatile char*)(iVar1 + iVar4*0xc) = (char)param_1;
  }
  FUN_000826e0(iVar3 + 8, 1 << (param_3 & 0xff));
  FUN_0007350c(0x20006350, 0, 0x8000, 0);
}

