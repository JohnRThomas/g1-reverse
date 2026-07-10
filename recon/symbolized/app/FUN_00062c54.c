#include "g1_app_symbols.h"
/* named: FUN_00062c54 */
/* Reconstructed FUN_00062c54 @ 0x62c54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int assert_post_action(int,int);
extern int printk(int,int,int,int);
extern int is_tx_ready(int);
extern int pinctrl_apply_state_constprop_0(int,int) __asm__("pinctrl_apply_state.constprop.0");
extern int thunk_FUN_00086384(int);

unsigned int FUN_00062c54(int param_1, int param_2)
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
                goto LAB_00062cb8;
            }
            if (*(int *)(iVar6 + 0xc) != 0) {
                printk(0, 0, 0, 0x769);
                uVar3 = 0x769;
LAB_00062cb8:
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
            uVar1 = pinctrl_apply_state_constprop_0(puVar5[3], 1);
            return uVar1 & ((int)uVar1 >> 0x1f);
        }
    } else {
        if (param_2 != 1) {
            return 0xffffff7a;
        }
        if (((int)(puVar5[1] << 0x1f) < 0) && (uVar1 = pinctrl_apply_state_constprop_0(puVar5[3], 0), (int)uVar1 < 0)) {
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

