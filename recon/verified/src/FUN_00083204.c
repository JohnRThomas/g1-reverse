/* Reconstructed FUN_00083204 @ 0x83204  (parity: 300/300 trials, PROVEN) */

extern void FUN_00073518(unsigned int *, unsigned int, unsigned int);
extern void FUN_00083090(unsigned int *, unsigned int, unsigned int, unsigned int);

void FUN_00083204(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1 = __atomic_exchange_n(param_1 + 1, 0,
                                            __ATOMIC_ACQ_REL);
  FUN_00073518(param_1 + 0x82, 0, uVar1);
  *(volatile unsigned char *)(param_1 + 2) = 0;
  (void)__atomic_exchange_n(param_1, 0, __ATOMIC_ACQ_REL);
  FUN_00083090(param_1, 1, 0, param_4);
}
