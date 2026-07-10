/* Reconstructed FUN_0007d6ae @ 0x7d6ae  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007d4ec(void);
extern void FUN_00086c78(unsigned int, unsigned int, unsigned int);
extern void FUN_000476b4(unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_0007d6ae(unsigned int param_1)
{
  int iVar1;
  unsigned int uVar2;

  iVar1 = FUN_0007d4ec();
  uVar2 = *(unsigned int*)(iVar1+0x24);
  FUN_00086c78(uVar2, param_1, 64000);
  FUN_000476b4(0,0,uVar2,0xf000);
  FUN_000476b4(0,0xc0,uVar2,0xf000);
  FUN_000476b4(0,0x180,uVar2,0x7800);
  return;
}

