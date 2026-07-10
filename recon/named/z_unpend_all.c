/* named: z_unpend_all */
/* Reconstructed z_unpend_all @ 0x86668  (parity: 300/300 trials, PROVEN) */

extern void FUN_000742b4(int *p);
extern void z_ready_thread_locked(int *p);

unsigned int z_unpend_all(int *param_1)
{
  unsigned int uVar1;
  int *piVar2;

  uVar1 = 0;
  while ((piVar2 = (int *)*param_1, param_1 != piVar2 && (piVar2 != (int *)0)))
  {
    FUN_000742b4(piVar2);
    z_ready_thread_locked(piVar2);
    uVar1 = 1;
  }
  return uVar1;
}

