/* Reconstructed FUN_0004d334 @ 0x4d334  (parity: 300/300 trials, PROVEN) */
extern int FUN_0007ee2c(int);
extern unsigned FUN_0004d2d0(unsigned);
extern void FUN_0004d8f8(int*,unsigned,int);
extern void FUN_00074844(int,int);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(int,...);
unsigned FUN_0004d334(int param_1,int param_2){
  int *piVar1 = (int*)0x000882b0;
  int *piVar5 = (int*)0x000882a0;
  unsigned uVar3, uVar6; int iVar2; unsigned uVar4;
  if ((unsigned)((int)piVar1 - (int)piVar5) < 0xa0){
    iVar2 = FUN_0007ee2c(0x2000a0dc);
    if (iVar2 != 0) return 0;
    uVar3=0; uVar6=0;
    for (; piVar5 <= piVar1; piVar5 += 4){
      if (piVar1 <= piVar5){
        if (param_1 != 0){
          while (uVar3 != 0){
            uVar3 = FUN_0004d2d0(uVar3);
            if (param_2 != 0) FUN_00074844(0x148,0);
          }
          return 0;
        }
        return uVar3;
      }
      if ((char)piVar5[3] != 0){
        if (*(void(**)(int*))(*piVar5 + 0xc) != 0) (*(void(**)(int*))(*piVar5+0xc))(piVar5);
        if (*(int(**)(int*))(*piVar5+0x10)==0 || (iVar2=(*(int(**)(int*))(*piVar5+0x10))(piVar5))==0)
          FUN_0004d8f8(piVar5, *(unsigned*)piVar5[1], 4);
        else uVar3 = uVar3 | (1u << (uVar6 & 0xff));
        uVar6++;
      }
    }
    FUN_0007e2fa(0x00099cbd,0x000f0cff,0x000f0cae,0x126);
    FUN_0007e2fa(0x000f0d20);
    uVar4 = 0x126;
  } else {
    FUN_0007e2fa(0x00099cbd,0x000f0cdb,0x000f0cae,0x119);
    uVar4 = 0x119;
  }
  FUN_0007e2ec(0x000f0cae,uVar4);
  return 0;
}

