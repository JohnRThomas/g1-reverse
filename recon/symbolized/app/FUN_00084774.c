#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084774 @ 0x00084774
 * public-name: FUN_00084774
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00084774 @ 0x84774  (parity: 300/300 trials, PROVEN) */

extern int FUN_00084602(int *);

int FUN_00084774(int *param_1, int param_2)
{
  int diff1 = *(unsigned short *)((char *)param_1 + 10) - *(unsigned short *)((char *)param_1 + 8);
  int formula1 = param_1[1] * diff1 + param_1[0];
  if (formula1 < param_2) {
    int diff2 = *(unsigned short *)((char *)param_1 + 0x16) - *(unsigned short *)((char *)param_1 + 0x14);
    int formula2 = param_1[4] * diff2 + param_1[3];
    if (formula2 < param_2) {
      return 0xffffffea;
    }
    param_1 = param_1 + 3;
  }
  return FUN_00084602(param_1);
}
