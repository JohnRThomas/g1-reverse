#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00062fe8 @ 0x00062fe8
 * public-name: uarte_nrfx_tx_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   uarte_nrfx_tx_start                      <= FUN_00062fe8 @ 0x00062fe8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   post_event_tag2_from_node                <= FUN_0008484e @ 0x0008484e
 *   post_event_tag4_and_clear                <= FUN_00084880 @ 0x00084880
 *   post_event_tag5                          <= FUN_000848b0 @ 0x000848b0
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 */
/* Reconstructed FUN_00062fe8 @ 0x62fe8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern int assert_post_action(int,int);
extern int post_event_tag2_from_node(int,int);
extern int post_event_tag4_and_clear(int,int);
extern int post_event_tag5(int);
extern int memcpy(int,int,int);

int uarte_nrfx_tx_start(int param_1, int param_2, unsigned int param_3, int param_4)
{
    int iVar3, iVar4;
    unsigned int uVar5;
    unsigned int *puVar6;
    unsigned int *puVar7;

    puVar7 = *(unsigned int **)(param_1 + 4);
    iVar4 = *(int *)(param_1 + 0x10);
    puVar6 = (unsigned int *)*puVar7;
    if (*(char *)((char *)puVar7 + 8) != '\0') {
        printk(0, 0, 0, 0x342);
        printk(0);
        assert_post_action(0, 0x342);
    }
    iVar3 = *(int *)(iVar4 + 0xc);
    if ((*(char *)(iVar3 + 0xca) == '\0') && (*(char *)(iVar3 + 0xcb) == '\0')) {
        *(int *)(iVar3 + 0x74) = param_4;
        if (param_4 < 0x1d1) {
            param_4 = 0x5c;
        } else {
            param_4 = param_4 / 5;
        }
        *(int *)(*(int *)(iVar4 + 0xc) + 0x78) = param_4;
        *(int *)(*(int *)(iVar4 + 0xc) + 0x58) = param_2;
        *(unsigned int *)(*(int *)(iVar4 + 0xc) + 0x5c) = param_3;
        *(int *)(*(int *)(iVar4 + 0xc) + 0x60) = 0;
        *(int *)(*(int *)(iVar4 + 0xc) + 100) = 0;
        *(int *)(*(int *)(iVar4 + 0xc) + 0x68) = 0;
        if ((int)(puVar7[1] << 0x1b) < 0) {
            uVar5 = (unsigned int)*(unsigned char *)(*(int *)(iVar4 + 0xc) + 0xc9);
            if (uVar5 != 0) {
                if (param_3 <= uVar5) {
                    uVar5 = param_3;
                }
                memcpy(param_2, *(int *)(iVar4 + 0xc) + 0xc4, uVar5);
                param_3 = param_3 - uVar5;
                param_2 = param_2 + uVar5;
                if (param_3 == 0) {
                    *(char *)(*(int *)(iVar4 + 0xc) + 0xc9) =
                         *(char *)(*(int *)(iVar4 + 0xc) + 0xc9) - (char)uVar5;
                    post_event_tag2_from_node(param_1, uVar5);
                    post_event_tag4_and_clear(param_1, *(int *)(iVar4 + 0xc) + 0x58);
                    post_event_tag5(param_1);
                    return 0;
                }
            }
        }
        puVar6[0x14d] = param_2;
        puVar6[0x14e] = param_3;
        puVar6[0x44] = 0;
        puVar6[0x53] = 0;
        *(unsigned char *)(*(int *)(iVar4 + 0xc) + 0xca) = 1;
        if ((int)(puVar7[1] << 0x1b) < 0) {
            iVar4 = *(int *)(*(int *)(param_1 + 0x10) + 0xc);
            if (iVar4 != 0) {
                *(unsigned int *)(iVar4 + 0xc0) = *(unsigned int *)(iVar4 + 0xc0) | 2;
            }
            *(int *)(**(int **)(param_1 + 4) + 0x500) = 8;
        }
        *puVar6 = 1;
        return 0;
    }
    return 0xfffffff0;
}
