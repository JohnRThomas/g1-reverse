/* Reconstructed FUN_00076d6c @ 0x76d6c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00076e20(unsigned int *, unsigned int,
                         unsigned int, unsigned int);

void FUN_00076d6c(unsigned int param_1, unsigned int unused_2,
                   unsigned int param_3, unsigned int unused_4)
{
  volatile unsigned int **heap_context =
      (volatile unsigned int **)0x20002d20UL;

  FUN_00076e20((unsigned int *)*heap_context, param_1, param_3,
               (unsigned int)(unsigned long)heap_context);
}
