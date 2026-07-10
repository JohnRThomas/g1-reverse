/* named: FUN_000809b0 */
/* Reconstructed FUN_000809b0 @ 0x809b0  (parity: 300/300 trials, PROVEN) */
extern unsigned FUN_00080a46(void);
extern int thunk_FUN_00064134(int);
extern void FUN_00051c38(void);

unsigned FUN_000809b0(int param_1, unsigned char *param_2)
{
  unsigned uVar1;
  int uVar2;
  unsigned uVar3;
  unsigned char uVar4;

  uVar1 = FUN_00080a46();
  uVar2 = thunk_FUN_00064134(param_1);
  if (3 < uVar1) {
    FUN_00051c38();
  }
  uVar3 = uVar1 ^ 1;
  switch (uVar2) {
    case 1:
      uVar3 = uVar1;
      /* fallthrough */
    case 3:
      uVar4 = 0;
      break;
    case 2:
      uVar4 = 1;
      break;
    case 4:
      uVar4 = 2;
      break;
    default:
      return 0xffffffffU;
  }
  if (param_2 != 0) {
    *param_2 = uVar4;
  }
  return uVar3;
}

