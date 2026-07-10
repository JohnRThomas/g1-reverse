/* Reconstructed FUN_000755f8 @ 0x755f8  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int,int,int,int);
extern int  FUN_000751d0(int,int,int,int,int,int,int);
extern void FUN_000753ec(int,int,int);
extern int  FUN_00072040(int);
extern void FUN_00072078(int);
extern int  FUN_0007205c(int);
extern int  FUN_00073f6c(int,int,int,int,int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
#define VSC(a) (*(volatile signed char*)(a))

int FUN_000755f8(int param_1,int param_2,unsigned int param_3,unsigned int param_4){
  int iVar5, iVar2, uVar3, uVar6=0, uVar4=0;
  iVar5 = VI(0x2000b450);
  VB(iVar5+0x60) = 1;
  VB(iVar5+0x61) = 1;
  if (param_1 == 0) { FUN_0007e2fa(0,0,0,0);FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0x12e); return 0; }
  if (param_2 < 0) { FUN_0007e2fa(0,0,0,0);FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0x12f); return 0; }
  uVar3 = FUN_000751d0(param_1,param_2,iVar5+0x60,(param_3==0&&param_4==0),param_1,param_2,(int)param_3);
  iVar2 = FUN_00072040(0x2000b4a0);
  if (iVar2 == 0) { FUN_0007e2fa(0,0,0,0);FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0x72); return 0; }
  FUN_00072078(0x2000b4a0);
  if (VSC(iVar5+0x60) == 0) {
    FUN_000753ec(param_1,uVar3,uVar6);
    if (FUN_0007205c(0x2000b4a0) != 0) return 0;
  } else {
    VB(iVar5+0x60) = 0;
    if ((param_3|param_4) == 0) {
      if (FUN_0007205c(0x2000b4a0) != 0) return 0xfffffff5;
    } else {
      uVar6 = FUN_00073f6c(0x2000b4a0,uVar6,0x20002d04,(int)(param_3|param_4),(int)param_3,(int)param_4);
      iVar5 = FUN_00072040(0x2000b4a0);
      if (iVar5 == 0) { FUN_0007e2fa(0,0,0,0);FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0x72); return 0; }
      FUN_00072078(0x2000b4a0);
      FUN_000753ec(param_1,uVar3,uVar4);
      if (FUN_0007205c(0x2000b4a0) != 0) return uVar6;
    }
  }
  FUN_0007e2fa(0,0,0,0);FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0xf0);
  return 0;
}

