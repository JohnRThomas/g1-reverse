#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000836de @ 0x000836de
 * public-name: FUN_000836de
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_queue_insert_with_timeout              <= FUN_0005eeb4 @ 0x0005eeb4
 */
/* Reconstructed FUN_000836de @ 0x836de  (parity: 300/300 trials, PROVEN) */

extern void k_queue_insert_with_timeout(int, unsigned int, unsigned int, unsigned int);

void FUN_000836de(int param_1, unsigned int unused_2,
                   unsigned int param_3, unsigned int param_4)
{
  unsigned int queue = *(volatile unsigned int *)(param_1 + 0x2c);
  unsigned int pending = *(volatile unsigned int *)(queue + 4);
  unsigned int item = *(volatile unsigned int *)pending;

  k_queue_insert_with_timeout(param_1, item, param_3, param_4);
}
