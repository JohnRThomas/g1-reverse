#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_uarte_nrfx_data__param_0313            [param_0313; library]
 * Raw function identity: 0x00062c54.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00062c54 @ 0x00062c54
 * public-name: uarte_nrfx_pm_action
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   uarte_nrfx_pm_action                     <= FUN_00062c54 @ 0x00062c54
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   is_tx_ready                              <= FUN_00084abe @ 0x00084abe
 *   pinctrl_apply_state                      <= FUN_00084b14 @ 0x00084b14
 *   thunk_FUN_00086384                       <= FUN_000850d8 @ 0x000850d8
 */
/* Reconstructed FUN_00062c54 @ 0x62c54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int assert_post_action(int,int);
extern int printk(int,int,int,int);
extern int is_tx_ready(int);
extern int pinctrl_apply_state(int,int);
extern void thunk_FUN_00086384(int);

unsigned int uarte_nrfx_pm_action(int param_1, int param_2)
{
    unsigned int uVar1;
    int iVar2;
    unsigned int uVar3;
    uint32_t *puVar4;
    uint32_t *puVar5;
    int iVar6;
    int iVar7;

    puVar5 = *(uint32_t **)(param_1 + 4);
    puVar4 = (uint32_t *)*puVar5;
    iVar6 = *(int *)(param_1 + 0x10);
    if (param_2 == 0) {
        iVar6 = *(int *)(iVar6 + 0xc);
        if (iVar6 != 0) {
            if (*(char *)(iVar6 + 0xca) != '\0') {
                printk(0, 0, 0, 0x768);
                uVar3 = 0x768;
                goto control_label_00062cb8;
            }
            if (*(int *)(iVar6 + 0xc) != 0) {
                printk(0, 0, 0, 0x769);
                uVar3 = 0x769;
control_label_00062cb8:
                assert_post_action(0, uVar3);
            }
        }
        if (puVar4[0x53] != 0) {
            puVar4[1] = 1;
            do {
                if (puVar4[0x51] != 0) break;
            } while (puVar4[0x49] == 0);
            puVar4[0x53] = 0;
            puVar4[0x51] = 0;
            puVar4[0x44] = 0;
        }
        iVar6 = **(int **)(param_1 + 4);
        uVar1 = (*(int **)(param_1 + 4))[1] & 2;
        if (uVar1 == 0) {
            iVar7 = 1000;
            *(uint32_t *)(iVar6 + 0x308) = 0x100;
            do {
                iVar2 = is_tx_ready(*(int *)(param_1 + 4));
                if (iVar2 != 0) break;
                thunk_FUN_00086384(1);
                iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
            if (*(int *)(iVar6 + 0x158) == 0) {
                *(uint32_t *)(iVar6 + 0x120) = 0;
                *(uint32_t *)(iVar6 + 0xc) = 1;
            }
        }
        iVar7 = 1000;
        do {
            if (*(int *)(iVar6 + 0x158) != 0) break;
            thunk_FUN_00086384(1);
            iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
        if (uVar1 == 0) {
            *(uint32_t *)(iVar6 + 0x304) = 0x100;
        }
        *(uint32_t *)(**(int **)(param_1 + 4) + 0x500) = 0;
        if ((int)(puVar5[1] << 0x1f) < 0) {
            uVar1 = pinctrl_apply_state(puVar5[3], 1);
            return uVar1 & ((int)uVar1 >> 0x1f);
        }
    } else {
        if (param_2 != 1) {
            return 0xffffff7a;
        }
        if (((int)(puVar5[1] << 0x1f) < 0) && (uVar1 = pinctrl_apply_state(puVar5[3], 0), (int)uVar1 < 0)) {
            return uVar1;
        }
        puVar4[0x140] = 8;
        if ((*(int *)(iVar6 + 0xc) == 0) && (*(char *)((int)puVar5 + 8) == '\0')) {
            puVar4[0x44] = 0;
            *puVar4 = 1;
        }
    }
    return 0;
}
