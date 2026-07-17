/* readable reconstruction; identity: FUN_0008174c @ 0x0008174c
 * public-name: atomic_counter_add_and_signal
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   atomic_counter_add_and_signal            <= FUN_0008174c @ 0x0008174c
 */
/* Reconstructed FUN_0008174c @ 0x8174c  (parity: 300/300 trials, PROVEN) */

void atomic_counter_add_and_signal(int param_1, int param_2)
{
  unsigned int uVar1;
  __atomic_fetch_add((unsigned int *)(param_1 + 0x2c),
                     (unsigned int)param_2, __ATOMIC_ACQ_REL);
  uVar1 = __atomic_fetch_or((unsigned int *)(param_1 + 0x10), 1,
                            __ATOMIC_ACQ_REL);
  if ((uVar1 & 1) == 0) {
    void (*fn)(void) = *(void (**)(void))(*(volatile int*)(param_1+4) + 0x1c);
    if (fn != 0) {
      fn();
    }
  }
}
