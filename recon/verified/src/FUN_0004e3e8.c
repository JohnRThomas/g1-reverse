/* Reconstructed FUN_0004e3e8 @ 0x4e3e8
 * CFG_VERIFY_CALL_ARITIES=4,2,1,1
 * Readable identity: settings_load_subtree.
 * Raw/address backmap: settings_load_subtree <= FUN_0004e3e8 @ 0x0004e3e8.
 */
#include <stdint.h>

extern void FUN_000723b8(void *, int32_t, int32_t, int32_t); /* k_mutex_lock */
extern int FUN_0004e6a8(const char *); /* settings_commit_subtree */
extern void FUN_00072558(void *); /* k_mutex_unlock */

struct settings_load_arg_recon {
    const char *subtree;
    void *callback;
    void *parameter;
};

struct settings_store_recon {
    struct settings_store_recon *next;
    const void **interface;
};

int FUN_0004e3e8(const char *subtree, uint32_t abi_padding)
{
    struct settings_load_arg_recon argument = { subtree, 0, 0 };
    struct settings_store_recon *store;
    int result;

    FUN_000723b8((void *)0x20003868UL, (int32_t)abi_padding, -1, -1);
    store = *(struct settings_store_recon * volatile *)0x2000a104UL;
    while (store != 0) {
        void (*load)(struct settings_store_recon *, const void *) =
            (void (*)(struct settings_store_recon *, const void *))store->interface[0];
        load(store, &argument);
        store = store->next;
    }
    result = FUN_0004e6a8(subtree);
    FUN_00072558((void *)0x20003868UL);
    return result;
}
