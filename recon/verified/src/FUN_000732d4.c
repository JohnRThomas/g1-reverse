/* Reconstructed FUN_000732d4 @ 0x732d4  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2ec(void*, int);
extern void FUN_0007e2fa(void*, void*, void*, int);
extern void FUN_00086c78(int, int, int, unsigned int, unsigned int);

void FUN_000732d4(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;

  if (param_1 == 0) {
    FUN_0007e2fa((void*)0x99cbdUL,(void*)0xf82dfUL,(void*)0xf820fUL,0x340);
    uVar1 = 0x340;
  } else {
    if (param_2 != 0) {
      FUN_00086c78(param_1,0,0x30,param_4,param_4);
      *(volatile int*)(param_1 + 4) = param_2;
      *(volatile unsigned int*)(param_1 + 0xc) = 0x100;
      return;
    }
    FUN_0007e2fa((void*)0x99cbdUL,(void*)0xf8230UL,(void*)0xf820fUL,0x341);
    uVar1 = 0x341;
  }
  FUN_0007e2ec((void*)0xf820fUL,uVar1);
}

