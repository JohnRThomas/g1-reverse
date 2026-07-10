/* Reconstructed FUN_00058c34 @ 0x58c34  (parity: 300/300 trials, PROVEN) */
extern int FUN_0005833c(int);
extern int FUN_000585f0(void*,int,int);
extern void FUN_0005f24c(int);
extern void FUN_00081cee(int,int,int,void*);
extern void FUN_000821a4(void*);
extern void FUN_000821f4(void*,int,int,int);
extern int FUN_00082236(void*,int);
extern int FUN_00082ec8(int,int);
extern void FUN_00086c78(void*,int,int);
char FUN_00058c34(int *param_1,int param_2,int param_3,int param_4,short param_5,int param_6,short param_7){
  int iVar1 = param_2 ? 1 : 0;
  iVar1 = FUN_00082ec8(*(int*)*param_1, iVar1);
  if (iVar1 == 0){
    if (FUN_00082236((char*)param_1 + 0x120, 5) == 0) return 0x12;
    return 0;
  }
  if (param_4 == 0) return 1;
  {
    struct { int a; int b; unsigned char c; int d; short e; short f; char g; } S;
    int local_2c = 0;
    FUN_00086c78(&S, 0, 0x18);
    if (param_3 != 0){
      local_2c = FUN_000585f0(param_1, param_3, 0);
      if (local_2c == 0) return 0x11;
    }
    S.a = *(int*)*param_1;
    S.f = param_5;
    S.c = (unsigned char)param_2;
    S.d = param_6;
    S.e = param_7;
    S.g = 1;
    FUN_00081cee(param_4, param_4, 0x00081c8d, &S);
    if (S.g == 0){
      if (local_2c != 0) FUN_000821a4(param_1);
      return 0;
    } else {
      if (param_3 != 0){
        FUN_0005833c(*(int*)(local_2c + 0x18));
        FUN_0005f24c(local_2c);
        FUN_000821f4(param_1, param_2, param_4, S.g);
      }
      if (param_2 == 0x18) return S.g;
    }
  }
  return 0;
}

