/* Reconstructed FUN_000188b0 @ 0x188b0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void atomic_and(void *, unsigned int);
extern void FUN_000187e8(unsigned int, unsigned int);

void FUN_000188b0(unsigned int param_1)
{
  DEBUG_PRINT(0x0009a6c1UL);
  atomic_and((void*)0x20006ab4UL,0xfffffffeUL);
  FUN_000187e8(param_1,1);
  return;
}

