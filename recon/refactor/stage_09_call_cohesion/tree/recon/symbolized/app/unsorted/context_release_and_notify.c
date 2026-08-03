#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000817b6 @ 0x000817b6
 * public-name: context_release_and_notify
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   context_release_and_notify               <= FUN_000817b6 @ 0x000817b6
 */
/* Reconstructed FUN_000817b6 @ 0x817b6  (parity: 300/300 trials, PROVEN) */

typedef void (*fn0)(void);
typedef void (*fn1)(int *);

void context_release_and_notify(int *param_1)
{
  int iVar1;
  fn0 fp0;
  fn1 fp1;
  iVar1 = param_1[1];
  if (*param_1 != 0) {
    fp0 = *(fn0 *)(iVar1 + 4);
    if (fp0 != 0) fp0();
    *param_1 = 0;
  }
  *(unsigned char *)((char *)param_1 + 0xb4) = 0;
  *(unsigned short *)((char *)param_1 + 0xb6) = 0;
  fp1 = *(fn1 *)(param_1 + 3);
  if (fp1 != 0) fp1(param_1);
  fp1 = *(fn1 *)(iVar1 + 0x20);
  if (fp1 != 0) {
    fp1(param_1);
    return;
  }
  return;
}
