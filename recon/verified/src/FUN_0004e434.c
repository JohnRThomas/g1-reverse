/* Reconstructed FUN_0004e434 @ 0x4e434  (parity: 300/300 trials, PROVEN) */

extern int FUN_000723b8(void *, long long);
extern void FUN_00072558(void *);
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

int FUN_0004e434(const char *subtree, settings_load_direct_cb callback,
                 void *parameter)
{
  struct settings_store_recon *store;
  struct settings_load_arg_recon argument;
  fnptr fp;
  argument.subtree = subtree;
  argument.callback = callback;
  argument.parameter = parameter;
  FUN_000723b8((void *)0x20003868UL, -1LL);
  for (store = *(struct settings_store_recon * volatile *)0x2000a104UL;
       store != 0; store = store->next) {
    fp = (fnptr)store->interface[0];
    fp(store, &argument);
  }
  FUN_00072558((void *)0x20003868UL);
  return 0;
}
