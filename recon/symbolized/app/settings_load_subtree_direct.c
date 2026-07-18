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

extern int k_mutex_lock(void *, long long);
extern void k_mutex_unlock(void *);
typedef int (*settings_load_direct_cb)(const char *, unsigned int,
                                      void *, void *, void *);
struct settings_load_arg_recon {
  const char *subtree;
  settings_load_direct_cb callback;
  void *parameter;
};
struct settings_store_recon {
  struct settings_store_recon *next;
  const void **interface;
};
typedef int (*fnptr)(struct settings_store_recon *,
                     const struct settings_load_arg_recon *);

int settings_load_subtree_direct(const char *subtree, settings_load_direct_cb callback,
                 void *parameter)
{
  struct settings_store_recon *store;
  struct settings_load_arg_recon argument;
  fnptr fp;
  argument.subtree = subtree;
  argument.callback = callback;
  argument.parameter = parameter;
  k_mutex_lock((void *)((unsigned long)&g_settings_lock) /*=0x20003868*/, -1LL);
  for (store = *(struct settings_store_recon * volatile *)((unsigned long)&g_settings_stores) /*=0x2000a104*/;
       store != 0; store = store->next) {
    fp = (fnptr)store->interface[0];
    fp(store, &argument);
  }
  k_mutex_unlock((void *)((unsigned long)&g_settings_lock) /*=0x20003868*/);
  return 0;
}
