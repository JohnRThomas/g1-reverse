/* Reconstructed FUN_0005b0dc @ 0x5b0dc  (parity: 296/300 trials, PROVEN) */
extern int  FUN_0005b0b8(int);
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int,int,int,int);
extern int  FUN_00080d3e(int,void*);
extern int  FUN_000814e6(int,int,void*);
#define VI(a) (*(volatile int*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
#define VH(a) (*(volatile unsigned short*)(a))

int FUN_0005b0dc(int param_1,int param_2,unsigned int param_3,unsigned int param_4){
  int iVar2; int buf[4];
  (void)param_4;
  if (param_1 == 0) { FUN_0007e2fa(0,0,0,0);FUN_0007e2fa(0,0,0,0);FUN_0007e2ec(0,0xd19); return 0; }
  if (param_2 == 0) { FUN_0007e2fa(0,0,0,0);FUN_0007e2fa(0,0,0,0);FUN_0007e2ec(0,0xd1a); return 0; }
  if (VB(param_1+0xd) != 7) return 0;
  iVar2 = FUN_00080d3e(VI(param_2), buf);
  if (iVar2 == 0) {
    if ((VB(VI(param_2+0xc)+6) & 0x30) == 0) return 0;
    param_2 = FUN_0005b0b8(param_2);
    if (param_2 == 0) { FUN_0007e2fa(0,0,0,0);FUN_0007e2fa(0,0,0,0);FUN_0007e2ec(0,0xd2b); return 0; }
  }
  iVar2 = FUN_00080d3e(VI(param_2), buf);
  if (iVar2 != 0) {
    param_2 = FUN_0005b0b8(param_2);
    if (param_2 == 0) { FUN_0007e2fa(0,0,0,0);FUN_0007e2fa(0,0,0,0);FUN_0007e2ec(0,0xd31); return 0; }
  }
  for (;;) {
    iVar2 = FUN_00080d3e(VI(param_2), buf);
    if (iVar2 == 0) goto LAB_1ca;
    iVar2 = FUN_00080d3e(VI(param_2), buf);
    if (iVar2 == 0) goto LAB_1ca;
    iVar2 = FUN_00080d3e(VI(param_2), buf);
    if (iVar2 == 0) goto LAB_1ca;
    iVar2 = FUN_00080d3e(VI(param_2), buf);
    if (iVar2 == 0) goto LAB_1ca;
    param_2 = FUN_0005b0b8(param_2);
    if (param_2 == 0) return 0;
  }
LAB_1ca:
  iVar2 = FUN_00080d3e(VI(param_2), buf);
  if (iVar2 != 0) return 0;
  {
    int puVar4 = VI(param_2+0xc);
    iVar2 = FUN_000814e6(param_1, VB(puVar4), (void*)(puVar4+1));
    if (iVar2 == 0) return 0;
    return (param_3 & VH(puVar4+8)) != 0;
  }
}

