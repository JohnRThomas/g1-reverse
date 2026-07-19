#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000530b4 @ 0x000530b4
 * public-name: submit_ancs_notify_work
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   submit_ancs_notify_work                  <= FUN_000530b4 @ 0x000530b4
 *   k_work_submit                            <= FUN_00072fdc @ 0x00072fdc
 * address symbols (name @ address):
 *   g_ancs_notify_work                       @ 0x20002934
 */
/* Reconstructed FUN_000530b4 @ 0x530b4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void k_work_submit(void*);
unsigned int submit_ancs_notify_work(void)
{
  k_work_submit((void*)((unsigned long)&g_ancs_notify_work) /*=0x20002934*/);
  return 0;
}
