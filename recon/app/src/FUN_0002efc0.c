/* Reconstructed FUN_0002efc0 @ 0x2efc0  (parity: 300/300 trials, PROVEN) */

extern int FUN_00032ee4(void);
extern char *FUN_000167a8(void);
unsigned int FUN_0002efc0(void)
{
  int iVar1;
  char *pcVar2;
  iVar1 = FUN_00032ee4();
  if ((iVar1 == 1) || (pcVar2 = FUN_000167a8(), *pcVar2 == (char)1)) {
    *(volatile unsigned char*)0x2000302fUL = 1;
  }
  return 0;
}

