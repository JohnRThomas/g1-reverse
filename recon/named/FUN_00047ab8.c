/* named: FUN_00047ab8 */
/* Reconstructed FUN_00047ab8 @ 0x47ab8  (parity: 300/300 trials, PROVEN) */

extern void heap_free(void);
void FUN_00047ab8(void)
{
  volatile int *piVar1 = (volatile int *)0x20009fccUL;
  if (*piVar1 != 0) {
    heap_free();
    *piVar1 = 0;
  }
}

