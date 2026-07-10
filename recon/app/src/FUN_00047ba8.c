/* Reconstructed FUN_00047ba8 @ 0x47ba8  (parity: 300/300 trials, PROVEN) */

extern char* FUN_000167a8(void);
extern void FUN_00086c78(void*, int, int);
extern int FUN_000720d0(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int);

unsigned int FUN_00047ba8(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int local_20 = param_1;
  unsigned int uStack_1c = param_2;
  unsigned int uStack_18 = param_3;
  unsigned int uStack_14 = param_4;
  (void)uStack_1c; (void)uStack_18; (void)uStack_14;
  char *pcVar1 = FUN_000167a8();
  if (*pcVar1 != 2) {
    FUN_00086c78((char*)&local_20 + 1, 0, 0x17);
    local_20 = (local_20 & 0xffffff00) | 1;
    int iVar2 = FUN_000720d0(0x2000392c, &local_20, 0, 0);
    if (iVar2 != 0) {
      DEBUG_PRINT(0xef058, 0xef736);
      return 0xffffffff;
    }
  }
  return 0;
}

