/* Reconstructed FUN_00059f04 @ 0x59f04  (parity: 300/300 trials, PROVEN) */

typedef int (*codeptr)(int,...);
extern int FUN_00059bcc(int,void*);
extern int FUN_00077c1c(int,int,int);
extern int FUN_0007f1e8(int,int*);
extern int FUN_00080cf2(int,void*);
extern int FUN_000828da(void*,void*);
extern int FUN_00082a42(int,int,void*);

int FUN_00059f04(int param_1, int param_2, codeptr param_3, int param_4)
{
  int iVar1;
  unsigned int *puVar2;
  struct __attribute__((packed)) {
    unsigned int type;
    unsigned int label;
    int value;
    unsigned short flags;
  } diagnostic;
  struct { unsigned int type, label; } short_diagnostic;
  int iStack_50;
  int local_44;
  unsigned char auStack_40[24];

  if (param_1 == 0) {
    short_diagnostic.type = 2;
    short_diagnostic.label = 0xf2b65;
    FUN_00082a42(0x88128, 0x1040, &short_diagnostic);
  } else {
    iVar1 = FUN_00080cf2(param_1, auStack_40);
    if (iVar1 == 0) {
      FUN_0007f1e8(param_1, &local_44);
      if (local_44 == 0 || (iStack_50 = FUN_00077c1c(local_44, 0, 10), iStack_50 == 0)) {
        puVar2 = (unsigned int*)FUN_00059bcc(0, auStack_40);
        if (puVar2 == 0) {
          if (param_2 == 0) return 0;
          puVar2 = (unsigned int*)FUN_00059bcc(0, (void*)0xf2b3a);
          if (puVar2 == 0) {
            short_diagnostic.type = 2;
            short_diagnostic.label = 0xf4761;
            FUN_00082a42(0x88128, 0x1040, &short_diagnostic);
            return -0xc;
          }
          *(unsigned char*)puVar2 = 0;
          FUN_000828da((unsigned char*)puVar2 + 1, auStack_40);
        } else if (param_2 == 0) {
          puVar2[0] = 0; puVar2[1] = 0; puVar2[2] = 0;
          return 0;
        }
        iVar1 = (*param_3)(param_4, puVar2 + 2, 4);
        if (-1 < iVar1) return 0;
        diagnostic.type = 3;
        diagnostic.label = 0xf4783;
        diagnostic.value = iVar1;
        FUN_00082a42(0x88128, 0x1840, &diagnostic);
        return iVar1;
      }
      diagnostic.type = 3;
      diagnostic.label = 0xf4746;
      diagnostic.value = iStack_50;
      FUN_00082a42(0x88128, 0x1840, &diagnostic);
    } else {
      diagnostic.type = 0x1000003;
      diagnostic.label = 0xf472a;
      diagnostic.value = param_1;
      diagnostic.flags = 0x200;
      FUN_00082a42(0x88128, 0x1c40, &diagnostic);
    }
  }
  return -0x16;
}
