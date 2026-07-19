/* readable reconstruction; identity: FUN_0005b680 @ 0x0005b680
 * public-name: gatt_notify
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_chan_req_free                        <= FUN_0005833c @ 0x0005833c
 *   att_get                                  <= FUN_0005858c @ 0x0005858c
 *   bt_att_create_pdu                        <= FUN_00058eb0 @ 0x00058eb0
 *   gatt_find_ccc_for_conn                   <= FUN_0005b0dc @ 0x0005b0dc
 *   gatt_notify                              <= FUN_0005b680 @ 0x0005b680
 *   net_buf_put                              <= FUN_0005f200 @ 0x0005f200
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   process_queue                            <= FUN_00082114 @ 0x00082114
 *   bt_att_set_tx_meta_data                  <= FUN_000825ac @ 0x000825ac
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   bt_gatt_check_perm                       <= FUN_00082cba @ 0x00082cba
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4ad5                             @ 0x000f4ad5
 *   rodata_f4aeb                             @ 0x000f4aeb
 *   rodata_f4b3d                             @ 0x000f4b3d
 *   rodata_f4b44                             @ 0x000f4b44
 *   rodata_f4bde                             @ 0x000f4bde
 */
/* Reconstructed FUN_0005b680 @ 0x5b680  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int att_chan_req_free(int,...);
extern int att_get(int,...);
extern int bt_att_create_pdu(int,...);
extern int gatt_find_ccc_for_conn(int,...);
extern int net_buf_put(int,...);
extern int net_buf_unref(int,...);
extern int net_buf_simple_add(int,...);
extern int assert_post_action(int,...) __attribute__((noreturn));
extern int printk(int,...);
extern int process_queue(int,...);
extern int bt_att_set_tx_meta_data(int,...);
extern int log_msg_create_3arg(int,...);
extern int bt_gatt_check_perm(int,...);
extern int memcpy(int,...);

unsigned gatt_notify(int param_1, unsigned short param_2, int param_3)
{
    int iVar1,iVar2; unsigned uVar3; unsigned short *puVar4; int *piVar5,*piVar6;
    unsigned local_28,local_24;
    iVar2 = bt_gatt_check_perm(param_1, *(unsigned*)(param_3+4), 0x94);
    if(iVar2 == 0){
        iVar2 = gatt_find_ccc_for_conn(param_1, *(unsigned*)(param_3+4), 1);
        if(iVar2 == 0){
            local_24 = 0x000f4aeb; local_28 = 2;
            log_msg_create_3arg(0x00088128, 0x1080, &local_28);
            uVar3 = 0xffffffea;
        } else {
            iVar2 = bt_att_create_pdu(param_1, 0x1b, *(unsigned short*)(param_3+0xc) + 2);
            if(iVar2 != 0){
                puVar4 = (unsigned short*)net_buf_simple_add(iVar2+0xc, 2);
                *puVar4 = param_2;
                net_buf_simple_add(iVar2+0xc, *(unsigned short*)(param_3+0xc));
                memcpy((int)(puVar4+1), *(unsigned*)(param_3+8), *(unsigned short*)(param_3+0xc));
                bt_att_set_tx_meta_data(iVar2, *(unsigned*)(param_3+0x10), *(unsigned*)(param_3+0x14), 1);
                if(param_1 == 0){
                    printk(0x00099cbd, 0x000f4b3d, 0x000f46b8, 0xf22);
                    uVar3 = 0xf22;
                } else {
                    if(iVar2 != 0){
                        iVar1 = att_get(0);
                        if(iVar1 == 0){
                            att_chan_req_free(*(unsigned*)(iVar2+0x18));
                            net_buf_unref(iVar2);
                            uVar3 = 0xffffff80;
                        } else {
                            net_buf_put(iVar1+0xc, iVar2);
                            piVar5 = *(int**)(iVar1+0x30);
                            if(piVar5 != 0){
                                piVar6 = (int*)*piVar5;
                                piVar5 = piVar5 - 100;
                                if(piVar6 != 0){ piVar6 = piVar6 - 100; }
                                while(iVar2 = process_queue((int)piVar5, iVar1+0xc), piVar5 = piVar6, iVar2 != 0){
                                    while(1){
                                        if(piVar5 == 0) goto LAB_00059a5a;
                                        piVar6 = (int*)piVar5[100];
                                        if(piVar6 != 0){ piVar6 = piVar6 - 100; }
                                        if(iVar2 != -2) break;
                                        iVar2 = -2;
                                        piVar5 = piVar6;
                                    }
                                }
                            }
LAB_00059a5a:
                            uVar3 = 0;
                        }
                        return uVar3;
                    }
                    printk(0x00099cbd, 0x000f4b44, 0x000f46b8, 0xf23);
                    uVar3 = 0xf23;
                }
                assert_post_action(0x000f46b8, uVar3);
            }
            local_24 = 0x000f4bde; local_28 = 2;
            log_msg_create_3arg(0x00088128, 0x1080, &local_28);
            uVar3 = 0xfffffff4;
        }
    } else {
        local_24 = 0x000f4ad5; local_28 = 2;
        log_msg_create_3arg(0x00088128, 0x1080, &local_28);
        uVar3 = 0xffffffff;
    }
    return uVar3;
}
