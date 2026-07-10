/* Reconstructed FUN_000862ee @ 0x862ee  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00086208(unsigned int, unsigned int, unsigned int, int);
extern void FUN_000861c2(unsigned int, unsigned int);

unsigned int FUN_000862ee(unsigned int param_1, unsigned int param_2, int param_3)
{
  unsigned int uVar1;

  if (param_3 != 0) {
    uVar1 = FUN_00086208(param_1,0,param_2,param_3);
    return uVar1;
  }
  FUN_000861c2(param_1,0xe);
  return 0;
}

