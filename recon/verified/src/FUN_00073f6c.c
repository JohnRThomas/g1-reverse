/* Reconstructed FUN_00073f6c @ 0x73f6c  (parity: 300/300 trials, PROVEN) */
extern int FUN_00072040(int,int,int,int);
extern int FUN_0007205c(int);
extern void FUN_00072078(int);
extern void FUN_00073f3c(int,int,int,int);
extern void FUN_000501d4(int);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(int,...);
void FUN_00073f6c(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6){
  int iVar3 = 0x2000b448;
  int iVar5 = 0x2000b490;
  (void)param_4;
  *(volatile int*)0x2000b484UL = *(volatile int*)(iVar3+8);
  if (param_1 == iVar5){
    FUN_0007e2fa(0x00099cbd,0x000f8584,0x000f82f4,0x35f);
    FUN_0007e2ec(0x000f82f4,0x35f);
    return;
  }
  if (FUN_00072040(iVar5, param_2, 0x20, 0) == 0){
    FUN_0007e2fa(0x00099cbd,0x000f0920,0x000f08c7,0x72);
    FUN_0007e2fa(0x000f0935,iVar5);
    FUN_0007e2ec(0x000f08c7,0x72);
    return;
  }
  FUN_00072078(iVar5);
  FUN_00073f3c(*(volatile int*)(iVar3+8), param_3, param_5, param_6);
  if (FUN_0007205c(param_1) == 0){
    FUN_0007e2fa(0x00099cbd,0x000f08f4,0x000f08c7,0x111);
    FUN_0007e2fa(0x000f090b,param_1);
    FUN_0007e2ec(0x000f08c7,0x111);
    return;
  }
  if (FUN_0007205c(iVar5) == 0){
    FUN_0007e2fa(0x00099cbd,0x000f08f4,0x000f08c7,0x111);
    FUN_0007e2fa(0x000f090b,iVar5);
    FUN_0007e2ec(0x000f08c7,0x111);
    return;
  }
  FUN_000501d4(param_2);
}

