/* Reconstructed FUN_0003b800 @ 0x3b800  (parity: 300/300 trials, PROVEN) */

extern void FUN_0002f80c(unsigned int, unsigned int);
extern void FUN_0002efc0(void);

void FUN_0003b800(void)
{
  unsigned int uVar1;

  uVar1 = __atomic_exchange_n((unsigned int*)0x20007b78UL, 0,
                              __ATOMIC_SEQ_CST);
  FUN_0002f80c(0,uVar1);
  FUN_0002efc0();
  return;
}
