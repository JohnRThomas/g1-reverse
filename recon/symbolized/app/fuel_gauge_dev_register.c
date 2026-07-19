#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033088 @ 0x00033088
 * public-name: fuel_gauge_dev_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fuel_gauge_dev_register                  <= FUN_00033088 @ 0x00033088
 * address symbols (name @ address):
 *   g_fuel_gauge_dev                         @ 0x20002424
 */
/* Reconstructed FUN_00033088 @ 0x33088  (parity: 300/300 trials, PROVEN) */

int fuel_gauge_dev_register(int param_1)
{
  int iVar1 = ((unsigned long)&g_fuel_gauge_dev) /*=0x20002424*/;
  if (param_1 != 0) {
    if (*(volatile int *)(((unsigned long)&g_fuel_gauge_dev) /*=0x20002424*/ + 4) != param_1) {
      *(volatile int *)(((unsigned long)&g_fuel_gauge_dev) /*=0x20002424*/ + 4) = param_1;
    }
    *(volatile unsigned char *)(iVar1 + 8) = 1;
    return 0;
  }
  return -1;
}
