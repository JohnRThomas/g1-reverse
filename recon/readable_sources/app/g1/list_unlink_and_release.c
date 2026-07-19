#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_refcounted_list_node__param_0247       [param_0247; G1-original]
 *   param_4          => struct g1_layout_gatt_ccc_list_node__param_0249         [param_0249; library]
 * Raw function identity: 0x000828e8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000828e8 @ 0x000828e8
 * public-name: list_unlink_and_release
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_sub_free                            <= FUN_00059e78 @ 0x00059e78
 *   list_unlink_and_release                  <= FUN_000828e8 @ 0x000828e8
 */
/* Reconstructed FUN_000828e8 @ 0x828e8  (parity: 300/300 trials, PROVEN) */

extern void gatt_sub_free(int);
typedef void (*fp_t)(unsigned int, void*, int);

void list_unlink_and_release(unsigned int param_1, int param_2, unsigned int *param_3, unsigned int *param_4)
{
    unsigned int uVar1;
    if (param_4 != 0) {
        uVar1 = param_4[6];
        if (param_3 == 0) {
            *(unsigned int*)(param_2+8) = uVar1;
            if ((unsigned int*)(param_4+6) == *(unsigned int**)(param_2+0xc)) {
                *(unsigned int*)(param_2+0xc) = uVar1;
            }
        } else {
            *param_3 = uVar1;
            if ((unsigned int*)(param_4+6) == *(unsigned int**)(param_2+0xc)) {
                *(unsigned int**)(param_2+0xc) = param_3;
            }
        }
        param_4[6] = 0;
        fp_t fp = (fp_t)(*(unsigned int*)param_4);
        fp(param_1, param_4, 0);
    }
    if (*(int*)(param_2+8) != 0) return;
    gatt_sub_free(param_2);
}
