#include "g1_app_symbols.h"
/* named: gatt_notify */
/* Reconstructed gatt_notify @ 0x5b680  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005833c(int,...);
extern int att_get(int,...);
extern int bt_att_create_pdu(int,...);
extern int FUN_0005b0dc(int,...);
extern int net_buf_destroy_default(int,...);
extern int net_buf_unref(int,...);
extern int net_buf_simple_add(int,...);
extern int assert_post_action(int,...) __attribute__((noreturn));
extern int printk(int,...);
extern int process_queue(int,...);
extern int bt_att_set_tx_meta_data(int,...);
extern int FUN_00082a42(int,...);
extern int bt_gatt_check_perm(int,...);
extern int memcpy(int,...);

unsigned gatt_notify(int param_1, unsigned short param_2, int param_3)
{
    int iVar1,iVar2; unsigned uVar3; unsigned short *puVar4; int *piVar5,*piVar6;
    unsigned local_28,local_24;
    iVar2 = bt_gatt_check_perm(param_1, *(unsigned*)(param_3+4), 0x94);
    if(iVar2 == 0){
        iVar2 = FUN_0005b0dc(param_1, *(unsigned*)(param_3+4), 1);
        if(iVar2 == 0){
            local_24 = "Device is not subscribed to characteristic" /*=0xf4aeb*/; local_28 = 2;
            FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1080, &local_28);
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
                    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "params" /*=0xf4b3d*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0xf22);
                    uVar3 = 0xf22;
                } else {
                    if(iVar2 != 0){
                        iVar1 = att_get(0);
                        if(iVar1 == 0){
                            FUN_0005833c(*(unsigned*)(iVar2+0x18));
                            net_buf_unref(iVar2);
                            uVar3 = 0xffffff80;
                        } else {
                            net_buf_destroy_default(iVar1+0xc, iVar2);
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
                    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "params->attr || params->uuid" /*=0xf4b44*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0xf23);
                    uVar3 = 0xf23;
                }
                assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, uVar3);
            }
            local_24 = "No buffer available to send notification" /*=0xf4bde*/; local_28 = 2;
            FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1080, &local_28);
            uVar3 = 0xfffffff4;
        }
    } else {
        local_24 = "Link is not encrypted" /*=0xf4ad5*/; local_28 = 2;
        FUN_00082a42(((uintptr_t)&tbl_880d8) /*=0x88128*/, 0x1080, &local_28);
        uVar3 = 0xffffffff;
    }
    return uVar3;
}

