/* Reconstructed FUN_0005a724 @ 0x5a724  (parity: 300/300 trials, PROVEN) */
extern int  FUN_00059b5c(int,void*);
extern int  FUN_00059c04(void);
extern int  FUN_0005a39c(int);
extern int  FUN_00077c1c(int,int,int);
extern void FUN_0007f1e8(int,int*);
extern int  FUN_00080cf2(int,void*);
extern void FUN_000828da(int,void*);
extern void FUN_00082a42(int,int,void*);
extern void FUN_00082b98(int,int);
extern void FUN_00082bb8(int,int);
#define VB(a) (*(volatile unsigned char*)(a))

int FUN_0005a724(int param_1,int param_2,int param_3,int param_4){
  int iVar1, puVar2, local_44;
  unsigned char st40[24];
  struct { unsigned char local_48; unsigned char local_47; } S;
  int stkargs[8];
  if (param_1 == 0) {
    FUN_00082a42(0x00088128, 0x1040, stkargs);
    return -0x16;
  }
  iVar1 = FUN_00080cf2(param_1, st40);
  if (iVar1 != 0) {
    FUN_00082a42(0x00088128, 0x1c40, stkargs);
    return -0x16;
  }
  FUN_0007f1e8(param_1, &local_44);
  if (local_44 != 0 && (iVar1 = FUN_00077c1c(local_44, 0, 10)) != 0) {
    FUN_00082a42(0x00088128, 0x1840, stkargs);
    return -0x16;
  }
  puVar2 = FUN_00059b5c(0, st40);
  if (puVar2 == 0) {
    puVar2 = FUN_00059c04();
    if (puVar2 == 0) {
      FUN_00082a42(0x00088128, 0x1040, stkargs);
      return -0xc;
    }
    VB(puVar2) = 0;
    FUN_000828da(puVar2+1, st40);
  }
  if (param_2 != 0) {
    iVar1 = ((int(*)(int,void*,int))param_3)(param_4, &S.local_48, 2);
    if (iVar1 < 0) {
      FUN_00082a42(0x00088128, 0x1840, stkargs);
      return iVar1;
    }
    VB(puVar2+8) = S.local_48;
    if (iVar1 == 2) {
      unsigned int u = S.local_47;
      if (u < 2) { FUN_00082b98(puVar2, u & 1); return 0; }
      FUN_00082a42(0x00088128, 0x1880, stkargs);
    } else {
      FUN_00082a42(0x00088128, 0x1080, stkargs);
    }
    FUN_00082bb8(puVar2, 0);
    return 0;
  }
  FUN_0005a39c(puVar2);
  return 0;
}

