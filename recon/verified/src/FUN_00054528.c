/* Reconstructed FUN_00054528 @ 0x54528  (parity: 300/300 trials, PROVEN) */
extern int FUN_00053cd4(int,int);
extern void FUN_000543d8(int,int);
extern void FUN_000566a4(int);
extern int FUN_00056908(unsigned,int);
extern int FUN_00056c78(int,void*);
extern unsigned short* FUN_0005f5d0(int,int);
extern void FUN_00080ea2(int,int,void*);
extern void FUN_00080f56(unsigned,int);
void FUN_00054528(int param_1){
  unsigned short *src = *(unsigned short**)(param_1+0xc);
  unsigned uVar1 = *(volatile unsigned short*)src;
  unsigned uVar5 = uVar1 & 0xffff;
  unsigned short local_20 = *(volatile unsigned short*)((char*)src+2);
  unsigned short local_1e = *(volatile unsigned short*)((char*)src+4);
  unsigned short local_1c = *(volatile unsigned short*)((char*)src+6);
  unsigned short local_1a = *(volatile unsigned short*)((char*)src+8);
  int iVar2 = FUN_00056908(uVar5,1);
  if (iVar2 == 0){
    unsigned local_30=3, local_2c=0x000f2db7, uStack_28=uVar5;
    (void)local_2c;(void)uStack_28;
    FUN_00080ea2(0x00088138, 0x1840, &local_30);
    FUN_00080f56(uVar5, 2);
  } else {
    int iVar3 = FUN_00056c78(iVar2, &local_20);
    if (iVar3 == 0){
      FUN_00080f56(uVar5, 0x1e);
    } else {
      iVar3 = FUN_00053cd4(0x2020, 0xe);
      if (iVar3 != 0){
        volatile unsigned short *p = (volatile unsigned short*)FUN_0005f5d0(iVar3+0xc, 0xe);
        *p = (unsigned short)uVar1;
        *(volatile unsigned*)((char*)p+0xa) = 0;
        p[1] = local_20;
        p[2] = local_1e;
        p[3] = local_1c;
        p[4] = local_1a;
        FUN_000543d8(0x2020, iVar3);
      }
    }
    FUN_000566a4(iVar2);
  }
}

