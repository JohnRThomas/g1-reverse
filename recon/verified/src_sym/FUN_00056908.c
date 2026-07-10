/* Reconstructed FUN_00056908 @ 0x56908  (parity: 300/300 trials, PROVEN) */

extern int conn_lookup_handle(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_000813ca(unsigned int a, unsigned int b, void *c);
extern void FUN_000566a4(int a);

int FUN_00056908(unsigned int param_1, unsigned char param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int local_28;
  unsigned int local_24;
  unsigned int uStack_20;
  unsigned int uStack_18;

  uStack_18 = param_4;
  iVar1 = conn_lookup_handle(0x20006138, 1, param_1);
  if (iVar1 != 0) {
    if ((param_2 & *(volatile unsigned char *)(iVar1 + 2)) != 0) {
      return iVar1;
    }
    local_24 = 0xf3c7b;
    local_28 = 3;
    uStack_20 = param_1;
    FUN_000813ca(0x88108, 0x1880, &local_28);
    FUN_000566a4(iVar1);
  }
  return 0;
}

