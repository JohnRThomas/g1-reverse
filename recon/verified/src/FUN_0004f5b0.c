/* Reconstructed FUN_0004f5b0 @ 0x4f5b0  (parity: 300/300 trials, PROVEN) */
extern int  FUN_00072040(int);
extern void FUN_00072078(int);
extern int  FUN_0007205c(int);
extern void FUN_0007e2fa(int,int,int,int);
extern void FUN_0007e2ec(int,int);
extern void FUN_0004d944(int,int,int);
extern void THUNK868b4(int);

void FUN_0004f5b0(void){
  volatile int *g2c8=(volatile int*)0x2000a2c8UL;
  volatile int *g2d0=(volatile int*)0x2000a2d0UL;
  int r4, iVar5, puVar12, iVar6;
  int *piVar13;
  unsigned int uVar8;
  int t;

  if (FUN_00072040(0x2000a2c4) == 0) {
    FUN_0007e2fa(0,0,0,0); FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0);
  }
L5ea:
  FUN_00072078(0x2000a2c4);
  r4 = g2c8[0];
  if (r4 == 0) {
    if (FUN_0007205c(0x2000a2c4) == 0) {
      FUN_0007e2fa(0,0,0,0); FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0);
      goto L5ea;
    }
    return;
  }
  /* L624 */
  if (g2c8[1] == 0) r4 = 0;
  g2c8[0] = 0;
  g2c8[1] = 0;
  if (FUN_0007205c(0x2000a2c4) == 0) {
    FUN_0007e2fa(0,0,0,0); FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0);
    goto L5ea;
  }
  for(;;){
    if (r4 == 0) return;
    iVar5 = *(volatile int*)r4;
    puVar12 = *(volatile int*)(r4+4);
    if (!((unsigned int)puVar12 >= 0xfa9b4u && (unsigned int)puVar12 < 0xfaa14u)) {
      FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0);
      goto L5ea;
    }
    uVar8 = 0xaaaaaaabu * (unsigned int)((puVar12 - 0xfa9b4) >> 3);
    t = g2d0[(uVar8 >> 5)];
    if ((int)((unsigned int)((int)t >> (uVar8 & 0x1f)) << 0x1f) < 0) {
      int p3 = *(volatile int*)(puVar12+0xc);
      if (p3 == 0) {
        FUN_0004d944(0,0,0);
      } else {
        ((void(*)(int))p3)(r4);
      }
    }
    iVar6 = 0;
    piVar13 = (int*)*(volatile int*)(puVar12+4);
    while (*(volatile int*)(puVar12+8) != (int)piVar13 && iVar6 == 0) {
      if (piVar13 == 0) { FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0); goto L5ea; }
      if (*piVar13 == 0) { FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0); goto L5ea; }
      { int pc = *(volatile int*)(*piVar13 + 4);
        if (pc == 0) { FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0); goto L5ea; }
        iVar6 = ((int(*)(int))pc)(r4);
      }
      piVar13 = piVar13 + 1;
    }
    THUNK868b4(r4);
    r4 = iVar5;
  }
}

