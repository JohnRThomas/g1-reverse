/* Reconstructed FUN_00060564 @ 0x60564  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_000604e4(unsigned int,int,unsigned int);
typedef void (*fnptr)(int,unsigned int);
void FUN_00060564(int param_1, fnptr UNRECOVERED_JUMPTABLE)
{
  unsigned int uVar1;
  uVar1 = FUN_000604e4(0x00087b30UL,(param_1 - 0x2000b098) >> 5,0x40);
  (*UNRECOVERED_JUMPTABLE)(param_1,uVar1);
  return;
}

