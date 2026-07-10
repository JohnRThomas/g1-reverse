/* Reconstructed FUN_000596c0 @ 0x596c0  (parity: 300/300 trials, PROVEN) */

extern int FUN_000748ac(void);
extern int FUN_00071c20(int a, int *b, int c, int d, int e);
extern int memset_bytes(int a, int b, int c);

int FUN_000596c0(int param_1, int param_2, int param_3)
{
  int iVar1;
  int uVar2;
  int local_14 = 0;

  uVar2 = param_1;
  iVar1 = FUN_000748ac();
  if (*(volatile int*)0x2000ae9cUL == iVar1) {
    param_2 = 0;
    param_1 = param_2;
  }
  iVar1 = FUN_00071c20(0x20003798, &local_14, param_1, param_2, uVar2);
  if (iVar1 == 0) {
    uVar2 = memset_bytes(local_14, 0, 0x1c);
  } else {
    uVar2 = 0;
  }
  return uVar2;
}

