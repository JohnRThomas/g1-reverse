#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086976 @ 0x00086976
 * public-name: ldexpf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   scalbnf                                  <= FUN_00075a0c @ 0x00075a0c
 *   ldexpf                                   <= FUN_00086976 @ 0x00086976
 *   finitef                                  <= FUN_000869f2 @ 0x000869f2
 */
/* Reconstructed FUN_00086976 @ 0x86976  (parity: 300/300 trials, PROVEN) */

extern int finitef(void);
extern float scalbnf(float a, unsigned int b);
extern int* thunk_FUN_00071678(void);

float ldexpf(float param_1, unsigned int param_2)
{
  int iVar1;
  int *puVar2;

  iVar1 = finitef();
  if ((iVar1 != 0) && (param_1 != 0.0f)) {
    param_1 = scalbnf(param_1, param_2);
    iVar1 = finitef();
    if ((iVar1 == 0) || (param_1 == 0.0f)) {
      puVar2 = thunk_FUN_00071678();
      *puVar2 = 0x22;
    }
  }
  return param_1;
}
