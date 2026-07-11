/* net-core FUN_01039fe6 @ 0x1039fe6 — true CFG extent 112 bytes (ends 0x103a056) */

extern void FUN_01036410(int, char*, unsigned int, unsigned int, int);
extern int FUN_0102d6e0(int, char**, char*);
extern void FUN_01039fb2(int);
extern int FUN_0102d69c(int, char *, char *, unsigned int);
extern void FUN_0103b5a4(void*, char*, unsigned int);

void FUN_01039fe6(int param_1, char *param_2, unsigned int param_3)
{
  if (param_2 == 0 || *param_2 == 0) {
    return;
  }

  volatile int * const pb0 = (volatile int *)(param_1 + 0xb0);
  int iVar3 = *pb0;
  int iVar4 = iVar3 + 0x14;

  FUN_01036410(iVar4, param_2, 0xffffffff, 0xffffffff, param_1);

  char *local_1c = param_2;
  int iVar2 = FUN_0102d6e0(iVar3 - 0x19c, &local_1c, param_2);
  char *pcVar1 = local_1c;

  if (pcVar1 != 0) {
    if (iVar2 != 0) {
      FUN_01039fb2(iVar4);
      int r = FUN_0102d69c(iVar3 - 0x19c, pcVar1, param_2, param_3);
      (void)r;
      return;
    }
    FUN_0103b5a4((void *)(pcVar1 + 0x40), param_2, 0x20);
    *(volatile unsigned int *)(pcVar1 + 0x60) = param_3;
  }
  FUN_01039fb2(iVar4);
}
