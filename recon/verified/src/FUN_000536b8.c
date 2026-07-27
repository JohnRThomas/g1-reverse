/* Reconstructed FUN_000536b8 @ 0x536b8  (parity: 300/300 trials, PROVEN) */
extern void FUN_00053658(int,int,int,int);
extern void FUN_00056394(int,int,int);
extern void FUN_000566a4(int);
extern int  FUN_00056908(int,int);
extern int  FUN_0005ee18(int);
extern unsigned int* FUN_0005f148(unsigned int*);
extern void FUN_0005f24c(int);
extern int  FUN_0005f594(int,int);
extern void FUN_0007e2fa(unsigned long, ...);
extern unsigned int FUN_00080e14(unsigned int);
extern void FUN_00080ea2(int,int,void*);
extern int  FUN_000865fc(int,int);
#define VI(a) (*(volatile int*)(a))
#define VH(a) (*(volatile unsigned short*)(a))
#define VB(a) (*(volatile unsigned char*)(a))
#define ASSERT() __builtin_trap()

void FUN_000536b8(void){
  int iVar4,iVar6,iVar8; unsigned int uVar10; int uVar9;
  unsigned char *puVar7; unsigned short *puVar5;
  unsigned short uVar1,uVar2;
  int st[8];
  iVar4 = FUN_0005f148(0x20002144);
  if (iVar4 == 0) return;
  uVar10 = VB(iVar4+0x18);
  if (uVar10 == 1) {
    if (VH(iVar4+0x10) < 2) { FUN_0007e2fa(0x99cbd,0xf2eb8,0xf2e84,0xa5d); ASSERT(); }
    puVar7 = (unsigned char*)FUN_0005f594(iVar4+0xc,2);
    iVar8 = FUN_00080e14(*puVar7);
    if ((int)(iVar8<<0x1e) >= 0) { FUN_0007e2fa(0x99cbd,0xf2f17,0xf2e84,0xa61); ASSERT(); }
    FUN_00053658(*puVar7, iVar4, 0x8b190, 6);
  } else {
    uVar9 = 0xf2f45;
    if (uVar10 == 3) {
      if (VH(iVar4+0x10) < 4) { FUN_0007e2fa(0x99cbd,0xf2eb8,0xf2e84,0x200); ASSERT(); }
      puVar5 = (unsigned short*)FUN_0005f594(iVar4+0xc,4);
      uVar1 = puVar5[1];
      uVar2 = puVar5[0];
      iVar6 = FUN_0005ee18(iVar4);
      VH(0x2000ff08 + iVar6*2) = (unsigned short)(((unsigned int)uVar2 << 0x14) >> 0x14);
      if ((unsigned int)uVar1 != (unsigned int)VH(iVar4+0x10)) {
        FUN_00080ea2(0x88138,0x2040,st);
        goto LAB_0005373c;
      }
      iVar6 = FUN_0005ee18(iVar4);
      iVar6 = FUN_00056908(VH(0x2000ff08 + iVar6*2), 0xf);
      if (iVar6 != 0) {
        FUN_00056394(iVar6, iVar4, uVar2 >> 0xc);
        FUN_000566a4(iVar6);
        goto LAB_00053792;
      }
      iVar6 = FUN_0005ee18(iVar4);
      uVar10 = VH(0x2000ff08 + iVar6*2);
      uVar9 = 0xf2ef5;
    }
    FUN_00080ea2(0x88138,0x1840,st);
  }
LAB_0005373c:
  FUN_0005f24c(iVar4);
LAB_00053792:
  if (VI(0x20002144) != 0) {
    if ((int)FUN_000865fc(0x20005f08, 0x20002980) < 0) {
      FUN_00080ea2(0x88138,0x1840,st);
    }
  }
}
