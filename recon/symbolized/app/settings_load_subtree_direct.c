#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e434 @ 0x0004e434
 * public-name: settings_load_subtree_direct
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_load_subtree_direct             <= FUN_0004e434 @ 0x0004e434
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 * address symbols (name @ address):
 *   g_settings_lock                          @ 0x20003868
 *   g_settings_stores                        @ 0x2000a104
 */
/* Reconstructed FUN_0004e434 @ 0x4e434  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_lock(unsigned int, unsigned int, int, int, unsigned int);
extern void k_mutex_unlock(unsigned int);
typedef void (*fnptr)(int *, void *);

unsigned int settings_load_subtree_direct(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int *piVar1;
  unsigned int local_14;
  unsigned int uStack_10;
  unsigned int local_c;
  fnptr fp;
  local_14 = param_1;
  uStack_10 = param_2;
  local_c = param_3;
  k_mutex_lock(((unsigned long)&g_settings_lock) /*=0x20003868*/, param_2, -1, -1, param_1);
  for (piVar1 = *(int * volatile *)((unsigned long)&g_settings_stores) /*=0x2000a104*/; piVar1 != 0; piVar1 = *(int **)piVar1) {
    fp = *(fnptr *)(piVar1[1]);
    fp(piVar1, &local_14);
  }
  k_mutex_unlock(((unsigned long)&g_settings_lock) /*=0x20003868*/);
  return 0;
}
