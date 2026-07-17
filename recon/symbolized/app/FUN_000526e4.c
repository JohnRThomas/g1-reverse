#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000526e4 @ 0x000526e4
 * public-name: FUN_000526e4
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ancs_notify_3be8                       @ 0x20003be8
 */
/* Reconstructed FUN_000526e4 @ 0x526e4  (parity: 300/300 trials, PROVEN) */

extern void FUN_000836de(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
void FUN_000526e4(unsigned int param_1, unsigned int param_2)
{
  FUN_000836de(((unsigned long)&g_ancs_notify_3be8) /*=0x20003be8*/, param_2, 0, 0);
}
