/* Reconstructed FUN_00032fe8 @ 0x32fe8  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_00071eac(void*, void*, unsigned int, void*, int, int, int, unsigned int, int);

void FUN_00032fe8(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)0x20019ef1UL;
  int iVar2;

  if (*pcVar1 != 0) {
    DEBUG_PRINT((unsigned long)0xa757fUL, (void*)0xa75c2UL, 0xab8);
    return;
  }
  iVar2 = FUN_00071eac((void*)0x20004870UL, (void*)0x20027a68UL, 0xc00, (void*)0x32421UL, 0,0,0,0xfffffff4,0);
  if (iVar2 == 0) {
    *pcVar1 = 1;
  }
  return;
}

