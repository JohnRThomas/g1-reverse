/* Reconstructed dmic_record_start @ 0x3b78c  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(int, int);
extern void FUN_00019c70(void);
extern void FUN_0002f688(void);
extern void FUN_0002f764(void);
extern void FUN_00072880(int);
extern int DEBUG_PRINT(int, ...);

void dmic_record_start(void)
{
  int iVar1;
  unsigned int uVar2;

  iVar1 = FUN_000167a8(0, 0);
  *(volatile unsigned char*)(iVar1 + 0x1059) = 4;
  if (*(int*)0x2000230cUL > 2) {
    if (*(int*)0x20007554UL == 0) {
      DEBUG_PRINT(0x9d30b, 0xa9843);
    } else {
      FUN_00019c70();
    }
  }
  FUN_0002f688();
  FUN_0002f764();
  uVar2 = *(volatile unsigned int*)0x20007b78UL;
  *(volatile unsigned int*)0x20007b78UL = 1;
  iVar1 = FUN_000167a8(0, uVar2);
  *(volatile unsigned int*)(iVar1 + 0x104c) = 0x1d;
  iVar1 = FUN_000167a8(0, 0);
  FUN_00072880(iVar1 + 0x68);
}

