/* Reconstructed FUN_000723b8 @ 0x723b8  (parity: 300/300 trials, PROVEN) */
extern int  FUN_00072040(int);
extern void FUN_00072078(int);
extern int  FUN_0007205c(int);
extern int  FUN_000739f0(int,int);
extern int  FUN_00073f6c(int,int,int);
extern void FUN_0007e2fa(int,int,int,int,int,int);
extern void FUN_0007e2ec(int,int);
extern int  FUN_000864b2(int,int);
#define VI(a)  (*(volatile int*)(a))
#define VSC(a) (*(volatile signed char*)(a))

int FUN_000723b8(int *param_1,int param_2,int *param_3,int param_4){
  volatile int *p = param_1;
  int iVar3, iVar4, cVar5, cVar1;
  (void)param_2;
MAIN:
  if (FUN_00072040(0x2000b470) == 0) {
    FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2ec(0,0);
    goto MAIN;
  }
  FUN_00072078(0x2000b470);
  if (p[3] == 0) {
    iVar4 = VSC(VI(0x2000b450) + 0xe);
    goto L7244e;
  }
  if (p[2] == VI(0x2000b450)) {
    iVar4 = p[4];
    goto L7244e;
  }
  if ((((int)param_3) | param_4) == 0) {
    if (FUN_0007205c(0x2000b470) != 0) return 0xfffffff0;
    FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2ec(0,0);
    goto MAIN;
  }
  cVar5 = VSC(VI(0x2000b450) + 0xe);
  cVar1 = VSC(p[2] + 0xe);
  { int r1 = cVar5;
    if (cVar5 >= cVar1) r1 = cVar1;
    if (r1 < -0x7f) r1 = -0x7f;
    iVar3 = 0;
    if (cVar1 > r1) iVar3 = FUN_000864b2(0,0);
  }
  if (FUN_00073f6c(0x2000b470,0,(int)param_1) == 0) return 0;
  if (FUN_00072040(0x2000b470) == 0) {
    FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2ec(0,0);
    goto MAIN;
  }
  FUN_00072078(0x2000b470);
  if (p[2] != 0) {
    int *piVar7 = (int*)p[0];
    iVar4 = p[4];
    if (param_1 != piVar7 && piVar7 != 0) {
      if (iVar4 >= (int)VSC((int)piVar7 + 0xe)) iVar4 = (int)VSC((int)piVar7 + 0xe);
      if (iVar4 < -0x7f) iVar4 = -0x7f;
    }
    if (FUN_000864b2(p[2], iVar4) != 0) goto L72504;
  }
  if (iVar3 != 0) goto L72504;
  if (FUN_0007205c(0x2000b470) != 0) return 0xfffffff5;
  FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2ec(0,0);
  goto MAIN;
L72504:
  FUN_000739f0(0x2000b470, 0);
  return 0xfffffff5;
L7244e:
  p[3] = p[3] + 1;
  p[4] = iVar4;
  p[2] = VI(0x2000b450);
  if (FUN_0007205c(0x2000b470) != 0) return 0;
  FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2fa(0,0,0,0,0,0); FUN_0007e2ec(0,0);
  goto MAIN;
}

