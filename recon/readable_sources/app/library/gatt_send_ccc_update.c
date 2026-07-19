#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_gatt_attr__param_0252               [param_0252; library]
 *   param_3          => struct g1_layout_gatt_ccc_update_ctx__param_0260        [param_0260; library]
 * Raw function identity: 0x0005b890.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005b890 @ 0x0005b890
 * public-name: gatt_send_ccc_update
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   bt_conn_lookup_addr_le                   <= FUN_00056e74 @ 0x00056e74
 *   bt_conn_lookup_state_le                  <= FUN_00056f08 @ 0x00056f08
 *   sc_save                                  <= FUN_0005a128 @ 0x0005a128
 *   gatt_indicate                            <= FUN_0005b270 @ 0x0005b270
 *   gatt_notify                              <= FUN_0005b680 @ 0x0005b680
 *   gatt_send_ccc_update                     <= FUN_0005b890 @ 0x0005b890
 *   bt_addr_le_eq_0                          <= FUN_000826b2 @ 0x000826b2
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   bt_gatt_check_perm                       <= FUN_00082cba @ 0x00082cba
 * address symbols (name @ address):
 *   ADDR_gatt_ccc_write_THUMB                @ 0x0005a465
 *   rodata_88128                             @ 0x00088128
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   rodata_f4ad5                             @ 0x000f4ad5
 *   g_bt_gatt_sc_ccc                         @ 0x20002a20
 *   g_bt_gatt_sc_cfg_addr_ff19               @ 0x2000ff19
 */
/* Reconstructed FUN_0005b890 @ 0x5b890  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int ble_conn_unref(int);
extern int bt_conn_lookup_addr_le(int,int);
extern int bt_conn_lookup_state_le(int,int,int);
extern int sc_save(int,int,int,int);
extern int gatt_indicate(int,int,int);
extern int gatt_notify(int,int,int);
extern int bt_addr_le_eq_0(int,int);
extern int log_msg_create_3arg(int,int,void*);
extern int bt_gatt_check_perm(int,int,int);

int gatt_send_ccc_update(int param_1, int param_2, int param_3)
{
    int uVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    short *puVar5;
    unsigned char *puVar6;
    unsigned int uVar7;
    int local_28;
    int local_24;

    uVar1 = ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/;
    if (*(int *)(param_1 + 8) != ADDR_gatt_ccc_write_THUMB /*=0x5a465*/) {
        return 1;
    }
    puVar6 = *(unsigned char **)(param_1 + 0xc);
    if (puVar6 == (unsigned char *)((unsigned long)&g_bt_gatt_sc_ccc) /*=0x20002a20*/) {
        iVar4 = 0;
        iVar2 = ((unsigned long)&g_bt_gatt_sc_cfg_addr_ff19) /*=0x2000ff19*/;
        do {
            iVar3 = bt_addr_le_eq_0(iVar2, uVar1);
            if (iVar3 == 0) {
                iVar3 = bt_conn_lookup_state_le(*(unsigned char *)(iVar2 + -1), iVar2, 7);
                if (iVar3 == 0) {
                    puVar5 = *(short **)(*(int *)(param_3 + 0x10) + 0x10);
                    sc_save(*(unsigned char *)(iVar2 + -1), iVar2, *puVar5, puVar5[1]);
                }
                else {
                    ble_conn_unref(0);
                }
            }
            iVar4 = iVar4 + 1;
            iVar2 = iVar2 + 0xc;
        } while (iVar4 != 3);
    }
    if (*(short *)(puVar6 + 8) != *(short *)(param_3 + 0xc)) {
        return 1;
    }
    iVar2 = bt_conn_lookup_addr_le(*puVar6, (int)(puVar6 + 1));
    if (iVar2 == 0) {
        return 1;
    }
    if ((*(char *)(iVar2 + 0xd) == '\a') &&
        ((*(int (**)(int,int))(puVar6 + 0x14) == 0 ||
         (iVar4 = (**(int (**)(int,int))(puVar6 + 0x14))(iVar2, param_1), iVar4 != 0)))) {
        iVar4 = bt_gatt_check_perm(iVar2, param_1, 0x94);
        if (iVar4 == 0) {
            if (*(short *)(param_3 + 0xc) == 2) {
                uVar7 = *(unsigned short *)(puVar6 + 8) & 2;
                if ((*(unsigned short *)(puVar6 + 8) & 2) != 0) {
                    iVar4 = gatt_indicate(iVar2, *(unsigned short *)(param_3 + 4), *(int *)(param_3 + 0x10));
                    if (iVar4 != 0) goto control_label_0005b9a4;
                    *(char *)(*(int *)(param_3 + 0x10) + 0x16) =
                         *(char *)(*(int *)(param_3 + 0x10) + 0x16) + '\x01';
                    uVar7 = 0;
                }
            }
            else {
                if (*(short *)(param_3 + 0xc) != 1) {
                    ble_conn_unref(iVar2);
                    *(int *)(param_3 + 8) = 0;
                    return 1;
                }
                uVar7 = *(unsigned short *)(puVar6 + 8) & 1;
                if ((*(unsigned short *)(puVar6 + 8) & 1) != 0) {
                    iVar4 = gatt_notify(iVar2, *(unsigned short *)(param_3 + 4), *(int *)(param_3 + 0x10));
control_label_0005b9a4:
                    ble_conn_unref(iVar2);
                    *(int *)(param_3 + 8) = iVar4;
                    if (-1 < iVar4) {
                        return 1;
                    }
                    return 0;
                }
            }
            ble_conn_unref(iVar2);
            *(unsigned int *)(param_3 + 8) = uVar7;
            return 1;
        }
        local_24 = ((unsigned long)&rodata_f4ad5) /*=0xf4ad5*/;
        local_28 = 2;
        log_msg_create_3arg(((unsigned long)&rodata_88128) /*=0x88128*/, 0x1080, &local_28);
    }
    ble_conn_unref(iVar2);
    return 1;
}
