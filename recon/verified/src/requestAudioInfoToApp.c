/* Reconstructed requestAudioInfoToApp @ 0x48840  (parity: 300/300 trials, PROVEN) */

extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000720d0(void*, void*, int, int);
extern void FUN_00086c78(void*, int, int);
extern void DEBUG_PRINT(unsigned long, ...);

int requestAudioInfoToApp(unsigned char param_1)
{
  int iVar1;
  int uVar2;
  unsigned char buf[24];

  FUN_00086c78(&buf[1], 0, 0x17);
  buf[0] = 3;
  *(unsigned short*)&buf[2] = 1;
  buf[4] = param_1;
  iVar1 = FUN_000720d0((void*)0x2000392cUL, buf, 0, 0);
  if (iVar1 == 0) {
    uVar2 = 0;
    if (*(int*)0x2000230cUL > 2) {
      if (*(int*)0x20007554UL == 0) {
        DEBUG_PRINT(0xef4d9, 0xef707);
      } else {
        FUN_00019c70(0xef4d9, 0xef707);
      }
    }
  } else {
    DEBUG_PRINT(0xef058, 0xef707);
    uVar2 = -1;
  }
  return uVar2;
}

