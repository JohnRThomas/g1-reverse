/* Reconstructed cleanAppLanguageInfo @ 0x23b78  (parity: 300/300 trials, PROVEN) */

extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000720d0(void*, void*, int, int);
extern void FUN_00072880(void*);
extern void DEBUG_PRINT(unsigned long, ...);

int cleanAppLanguageInfo(unsigned int param_1, unsigned int param_2)
{
  int iVar1;
  int uVar2;
  unsigned char buf[8];

  buf[0] = 2;
  *(unsigned int*)&buf[1] = 0;
  buf[5] = 0;
  iVar1 = FUN_000720d0((void*)0x20003994UL, buf, 0, 0);
  if (iVar1 == 0) {
    if (*(int*)0x2000230cUL > 2) {
      if (*(int*)0x20007554UL == 0) {
        DEBUG_PRINT(0x9e968, 0x9ed8f);
      } else {
        FUN_00019c70(0x9e968, 0x9ed8f);
      }
    }
    FUN_00072880((void*)0x200079e4UL);
    uVar2 = 0;
  } else {
    if (*(int*)0x2000230cUL > 0) {
      if (*(int*)0x20007554UL == 0) {
        DEBUG_PRINT(0x9e903, 0x9ed8f);
      } else {
        FUN_00019c70(0x9e903, 0x9ed8f);
      }
    }
    uVar2 = -1;
  }
  return uVar2;
}
