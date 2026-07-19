#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00058f80 @ 0x00058f80
 * public-name: att_exec_write_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_notify_or_indicate                  <= FUN_00058c34 @ 0x00058c34
 *   bt_att_create_rsp_pdu                    <= FUN_00058f34 @ 0x00058f34
 *   att_exec_write_process                   <= FUN_00058f80 @ 0x00058f80
 *   net_buf_slist_get                        <= FUN_0005f148 @ 0x0005f148
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   bt_att_chan_send_rsp                     <= FUN_000821a4 @ 0x000821a4
 *   att_send_error_rsp                       <= FUN_000821f4 @ 0x000821f4
 *   net_buf_simple_add_mem                   <= FUN_00083740 @ 0x00083740
 * address symbols (name @ address):
 *   att_prep_write_rsp_buf                   @ 0x200029a0
 */
/* Reconstructed FUN_00058f80 @ 0x58f80  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int gatt_notify_or_indicate(int, ...);
extern int bt_att_create_rsp_pdu(int,int,int);
extern int net_buf_slist_get(int);
extern int net_buf_unref(int);
extern int bt_att_chan_send_rsp(int,int);
extern int att_send_error_rsp(int, ...);
extern int net_buf_simple_add_mem(int, ...);

unsigned int att_exec_write_process(int *param_1, int param_2)
{
    volatile uint32_t *puVar5 = (volatile uint32_t *)((unsigned long)&att_prep_write_rsp_buf) /*=0x200029a0*/;
    char cVar1;
    short sVar4;
    int iVar6;
    unsigned int uVar7;
    int iVar8;
    uint32_t *puVar9;
    uint32_t *puVar10;
    uint32_t *puVar11;
    uint32_t *puVar12;
    unsigned short uVar3;
    unsigned short uVar2;

    iVar8 = 0;
    cVar1 = **(char **)(param_2 + 0xc);
    do {
        if (*(int *)(*param_1 + 0x28) == 0) {
            if (iVar8 == 0) {
                iVar8 = bt_att_create_rsp_pdu((int)param_1, 0x19, 0);
                if (iVar8 == 0) {
                    return 0xe;
                }
                bt_att_chan_send_rsp((int)param_1, iVar8);
            }
            return 0;
        }
        iVar6 = net_buf_slist_get(*param_1 + 0x28);
        *(volatile unsigned short *)(puVar5 + 1) = 0;
        sVar4 = *(short *)(iVar6 + 0x18);
        uVar2 = *(unsigned short *)(iVar6 + 0x10);
        uVar7 = *(unsigned int *)(iVar6 + 0xc);
        *puVar5 = puVar5[2];
        net_buf_simple_add_mem((int)puVar5, uVar7, uVar2);
        iVar8 = *param_1;
        uVar3 = *(unsigned short *)(iVar6 + 0x1a);
        puVar9 = *(uint32_t **)(iVar8 + 0x28);
        if (puVar9 != (uint32_t *)0x0) {
            puVar10 = (uint32_t *)*puVar9;
            puVar11 = (uint32_t *)0x0;
            while (puVar9 != (uint32_t *)0x0) {
                puVar12 = puVar9;
                if (*(short *)(puVar9 + 6) == sVar4) {
                    if (*(unsigned short *)((int)puVar9 + 0x1a) == 0) break;
                    if ((unsigned int)*(unsigned short *)((int)puVar9 + 0x1a) !=
                        (unsigned int)uVar3 + (unsigned int)*(volatile unsigned short *)(puVar5 + 1)) {
                        uVar7 = 7;
control_label_000590a6:
                        att_send_error_rsp((int)param_1, 0x18, sVar4, uVar7);
                        return 0;
                    }
                    if ((unsigned int)*(volatile unsigned short *)((int)puVar5 + 6) <
                        (unsigned int)*(volatile unsigned short *)(puVar5 + 1) + (unsigned int)*(unsigned short *)(puVar9 + 4)) {
                        uVar7 = 0xd;
                        goto control_label_000590a6;
                    }
                    net_buf_simple_add_mem((int)puVar5, puVar9[3]);
                    uVar7 = *puVar9;
                    if (puVar11 == (uint32_t *)0x0) {
                        *(uint32_t *)(iVar8 + 0x28) = uVar7;
                        if (puVar9 == *(uint32_t **)(iVar8 + 0x2c)) {
                            *(uint32_t *)(iVar8 + 0x2c) = uVar7;
                        }
                    } else {
                        *puVar11 = uVar7;
                        if (puVar9 == *(uint32_t **)(iVar8 + 0x2c)) {
                            *(uint32_t **)(iVar8 + 0x2c) = puVar11;
                        }
                    }
                    *puVar9 = 0;
                    net_buf_unref((int)puVar9);
                    puVar12 = puVar11;
                }
                puVar9 = puVar10;
                puVar11 = puVar12;
                if (puVar10 != (uint32_t *)0x0) {
                    puVar10 = (uint32_t *)*puVar10;
                }
            }
        }
        if (cVar1 == '\x01') {
            iVar8 = gatt_notify_or_indicate((int)param_1, 0x18, 0, sVar4, *(unsigned short *)(iVar6 + 0x1a), *puVar5,
                                 *(volatile unsigned short *)(puVar5 + 1));
            if (iVar8 != 0) {
                att_send_error_rsp((int)param_1, 0x18, *(unsigned short *)(iVar6 + 0x18), iVar8);
            }
        } else {
            iVar8 = 0;
        }
        net_buf_unref(iVar6);
    } while (1);
}
