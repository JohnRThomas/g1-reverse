/* Reconstructed FUN_000355b4 @ 0x355b4  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(const char *msg, const char *file, unsigned int line);
extern int FUN_00019c70(void);
extern int FUN_000352e8(int);
extern int FUN_00076d6c(int);
extern int FUN_00076d7c(int);
extern int FUN_00086c78(int, int, int);

void FUN_000355b4(void)
{
  int iVar1;

  iVar1 = FUN_00076d6c(0x1800);
  if (iVar1 != 0) {
    FUN_00086c78(iVar1,0,0x15e3);
    FUN_000352e8(iVar1);
    FUN_00076d7c(iVar1);
    return;
  }
  if (*(volatile unsigned int*)0x20007554UL != 0) {
    FUN_00019c70();
    return;
  }
  DEBUG_PRINT((const char*)0xa7c9cUL,(const char*)0xa8a24UL,0x277);
  return;
}

