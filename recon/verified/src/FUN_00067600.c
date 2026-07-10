/* Reconstructed FUN_00067600 @ 0x67600  (parity: 300/300 trials, PROVEN) */
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int,int,int,int);
extern int  FUN_00085316(int,int);
extern int  FUN_0008539a(int,int);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))

void FUN_00067600(int param_1,int *param_2){
  int p2 = (int)param_2;
  int iVar2,iVar3; unsigned int uVar4;
  unsigned char local_28[8]; int stk[16];
  (void)stk;
  if (VI(p2) == 0) { FUN_0007e2fa(0,0,0,0); FUN_0007e2ec(0,0x297); }
  iVar2 = FUN_0008539a(param_1, 2);
  iVar3 = FUN_0008539a(param_1, 0x200);
  if (iVar3 == 0) {
    if (iVar2 != 0) goto LAB_67670;
    FUN_0008539a(param_1, 0x40000);
    if ((signed char)VB(p2+0x20) != 0) {
      VI(param_1+0x200)=0x200; VI(p2+8)=0x202; VI(param_1+0x308)=0x19c0202;
      VI(param_1+0x304)=VI(p2+8); VI(param_1+8)=1; VI(param_1+0x20)=1; return;
    }
    uVar4 = VB(p2+0x25);
    if (uVar4 == 0) goto LAB_676b2;
  } else {
    if (iVar2 == 0) {
      VI(param_1+0x308)=VI(p2+8); VI(p2+8)=2; VI(param_1+0x304)=VI(p2+8);
      iVar2 = FUN_0008539a(param_1, 0x1000000);
      if (iVar2==0 || (int)(VI(param_1+0x200)<<0x16) >= 0) { VI(param_1+0x20)=1; VI(param_1+0x14)=1; }
      VB(p2+0x23)=1; return;
    }
LAB_67670:
    if ((int)(VI(p2+0x1c)<<0x19) >= 0 && VB(p2+0x23)==0) {
      int b = FUN_00085316(param_1, p2);
      VB(p2+0x23) = (unsigned char)(b ^ 1);
    }
    if ((VI(p2+0x1c) & 4) != 0) goto LAB_6770c;
    VI(param_1+0x160)=0; VI(param_1+0x15c)=0;
    if (VB(p2+0x25)==0 || VB(p2+0x23)!=0) {
      uVar4 = 0;
LAB_676b2:
      VI(param_1+0x200)=(int)uVar4; VI(p2+8)=(int)uVar4; VI(param_1+0x308)=0x019c0202;
      uVar4 = (unsigned int)(((int)(param_1<<0xc))>>0x18);
      if ((int)uVar4 >= 0) {
        VI(0xe000e100 + ((uVar4>>5)+0x60)*4) = 1 << (uVar4 & 0x1f);
      }
    }
  }
LAB_6770c:
  iVar2 = VI(param_1+0x4c4);
  VI(param_1+0x4c4) = iVar2;
  if ((int)(iVar2<<0x1e) < 0) local_28[0]=1;
  else if ((int)(iVar2<<0x1d) < 0) local_28[0]=2;
  else if ((int)(iVar2<<0x1f) < 0) local_28[0]=3;
  else local_28[0] = (unsigned char)((VB(p2+0x23) & 0x3f) << 2);
  if (VB(p2+0x25) == 0) VB(p2+0x24) = 0;
  if ((int)(VI(p2+0x1c)<<0x1d) >= 0 || VB(p2+0x23) != 0) {
    ((void(*)(void*,int))(VI(p2)))(local_28, VI(p2+4));
  }
}

