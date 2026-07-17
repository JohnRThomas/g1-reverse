#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084b14 @ 0x00084b14
 * public-name: FUN_00084b14
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   pinctrl_lookup_state                     <= FUN_00083eb8 @ 0x00083eb8
 */
/* Reconstructed FUN_00084b14 @ 0x84b14  (parity: 300/300 trials, PROVEN) */

extern int pinctrl_lookup_state(unsigned int *, unsigned int *, unsigned int **, unsigned int, unsigned int *);
extern void FUN_00083ede(unsigned int, unsigned char, unsigned int);

void FUN_00084b14(unsigned int *param_1, unsigned int *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int *local_c;

  local_c = param_2;
  iVar1 = pinctrl_lookup_state(param_1,param_2,&local_c,param_4,param_1);
  if (-1 < iVar1) {
    FUN_00083ede(*local_c,*(unsigned char *)(local_c + 1),*param_1);
  }
  return;
}
