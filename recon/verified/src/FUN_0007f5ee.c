/* Reconstructed FUN_0007f5ee @ 0x7f5ee  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(int, unsigned int);
extern void FUN_0007f5d8(int a0, unsigned int a1);

void FUN_0007f5ee(unsigned int param_1, unsigned int param_2, int param_3)
{
  fn_t UNRECOVERED_JUMPTABLE = *(fn_t volatile *)(param_3 + 0x10);
  FUN_0007f5d8(param_3 - 0x10, 2);
  if (UNRECOVERED_JUMPTABLE != 0) {
    UNRECOVERED_JUMPTABLE(param_3 - 0x14, param_2);
  }
}

