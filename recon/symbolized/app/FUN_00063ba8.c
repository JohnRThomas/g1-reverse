#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00063ba8 @ 0x00063ba8
 * public-name: FUN_00063ba8
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ancs_notify_slot_table                 @ 0x2000b308
 */
/* Reconstructed FUN_00063ba8 @ 0x63ba8  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00063ba8(int param_1)
{
  int i = 0;
  while (1) {
    if (*(volatile int *)(((unsigned long)&g_ancs_notify_slot_table) /*=0x2000b308*/ + i*4) != 0) {
      return 0;
    }
    if (!(param_1 > i)) {
      return 1;
    }
    i = i + 1;
  }
}
