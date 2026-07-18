/* readable reconstruction; identity: FUN_0004e3e8 @ 0x0004e3e8
 * public-name: settings_load_subtree
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_load_subtree                    <= FUN_0004e3e8 @ 0x0004e3e8
 *   settings_commit_subtree                  <= FUN_0004e6a8 @ 0x0004e6a8
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 * address symbols (name @ address):
 *   g_settings_lock                          @ 0x20003868
 *   g_settings_stores                        @ 0x2000a104
 */
/* Reconstructed FUN_0004e3e8 @ 0x4e3e8
 * CFG_VERIFY_CALL_ARITIES=4,2,1,1
 * Readable identity: settings_load_subtree.
 * Raw/address backmap: settings_load_subtree <= FUN_0004e3e8 @ 0x0004e3e8.
 */
#include <stdint.h>

extern int k_mutex_lock(void *, int64_t); /* k_mutex_lock */
extern int settings_commit_subtree(const char *); /* settings_commit_subtree */
extern void k_mutex_unlock(void *); /* k_mutex_unlock */

struct settings_load_arg_recon {
    const char *subtree;
    void *callback;
    void *parameter;
};

struct settings_store_recon {
    struct settings_store_recon *next;
    const void **interface;
};

int settings_load_subtree(const char *subtree)
{
    struct settings_load_arg_recon argument = { subtree, 0, 0 };
    struct settings_store_recon *store;
    int result;

    k_mutex_lock((void *)0x20003868UL, INT64_C(-1));
    store = *(struct settings_store_recon * volatile *)0x2000a104UL;
    while (store != 0) {
        void (*load)(struct settings_store_recon *, const void *) =
            (void (*)(struct settings_store_recon *, const void *))store->interface[0];
        load(store, &argument);
        store = store->next;
    }
    result = settings_commit_subtree(subtree);
    k_mutex_unlock((void *)0x20003868UL);
    return result;
}
