#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000530b4 @ 0x000530b4
 * public-name: FUN_000530b4
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ancs_notify_work                       @ 0x20002934
 */
/* Reconstructed FUN_000530b4 @ 0x530b4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_00072fdc(void*);
unsigned int FUN_000530b4(void)
{
  FUN_00072fdc((void*)((unsigned long)&g_ancs_notify_work) /*=0x20002934*/);
  return 0;
}
