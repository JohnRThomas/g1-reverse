#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0000ea4c @ 0x0000ea4c
 * public-name: strtod_has_more_digits
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strtod_has_more_digits                   <= FUN_0000ea4c @ 0x0000ea4c
 */
/* Reconstructed FUN_0000ea4c @ 0xea4c  (parity: 300/300 trials, PROVEN) */

unsigned int strtod_has_more_digits(int param_1, int param_2)
{
  char *pcVar1;

  if (*(int *)(param_2 + 4) == 0) {
    return 0;
  }
  pcVar1 = (char *)(param_1 - 1);
  do {
    if (*(int *)(param_2 + 4) <= (int)(pcVar1 + (1 - param_1))) {
      return 1;
    }
    pcVar1 = pcVar1 + 1;
  } while (*pcVar1 != 0);
  return 0;
}
