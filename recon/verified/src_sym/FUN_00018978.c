/* Reconstructed FUN_00018978 @ 0x18978  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int);
extern void atomic_and(void *, unsigned int);
extern void FUN_000187e8(unsigned int, unsigned int);

void FUN_00018978(unsigned int param_1)
{
  DEBUG_PRINT(0x0009a7f2UL);
  atomic_and((void*)0x20006ab4UL,0xfffffffeUL);
  FUN_000187e8(param_1,1);
  return;
}

