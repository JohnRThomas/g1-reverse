/* Reconstructed FUN_00051164 @ 0x51164  (parity: 300/300 trials, PROVEN) */

extern void FUN_0004b0dc(unsigned int,unsigned int,unsigned int);
void FUN_00051164(void)
{
  FUN_0004b0dc(2,0xf2432,0x1d);
  __asm__ volatile(
    "eors r0, r0\n\t"
    "msr basepri, r0\n\t"
    "mov.w r0, #3\n\t"
    "svc #2\n\t"
  );
}

