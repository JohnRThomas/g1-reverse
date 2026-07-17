#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086668 @ 0x00086668
 * public-name: z_unpend_all
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_ready_thread_locked                    <= FUN_000738d4 @ 0x000738d4
 *   z_unpend_all                             <= FUN_00086668 @ 0x00086668
 */
/* Reconstructed FUN_00086668 @ 0x86668  (parity: 300/300 trials, PROVEN) */

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
