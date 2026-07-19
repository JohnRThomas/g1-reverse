#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_cJSON__param_0322                      [param_0322; library]
 * Raw function identity: 0x0006466c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0006466c @ 0x0006466c
 * public-name: cjson_add_item_to_object
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_strdup                             <= FUN_00064640 @ 0x00064640
 *   cjson_add_item_to_object                 <= FUN_0006466c @ 0x0006466c
 *   sllist_insert_after                      <= FUN_00084f2e @ 0x00084f2e
 * address symbols (name @ address):
 *   g_cjson_free_hook                        @ 0x20002bb0
 */
/* Reconstructed FUN_0006466c @ 0x6466c  (parity: 300/300 trials, PROVEN) */

extern int cjson_strdup(int a);
extern int sllist_insert_after(int a, int b);

typedef void (*fn0_t)(void);

int cjson_add_item_to_object(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar2;
    if (param_1 != 0 && param_2 != 0 && param_3 != 0 && param_1 != param_3) {
        if (param_4 == 0) {
            param_2 = cjson_strdup(param_2);
            if (param_2 == 0) {
                return 0;
            }
            uVar2 = *(unsigned int *)(param_3 + 0xc) & 0xfffffdff;
        } else {
            uVar2 = *(unsigned int *)(param_3 + 0xc) | 0x200;
        }
        {
            int shifted = (*(int *)(param_3 + 0xc)) << 0x16;
            if (shifted >= 0 && *(int *)(param_3 + 0x20) != 0) {
                fn0_t f = *(volatile fn0_t *)((unsigned long)&g_cjson_free_hook) /*=0x20002bb0*/;
                f();
            }
        }
        *(int *)(param_3 + 0x20) = param_2;
        *(unsigned int *)(param_3 + 0xc) = uVar2;
        return sllist_insert_after(param_1, param_3);
    }
    return 0;
}
