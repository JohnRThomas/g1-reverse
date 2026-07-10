/* named: ble_privacy_id_remove */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed ble_privacy_id_remove @ 0x55094  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int bt_hci_cmd_create(int,...);
extern int FUN_00053d70(int,...);
extern int FUN_00055710(int,...);
extern int ble_conn_unref(void);
extern int bt_conn_lookup_state_le(int,...);
extern int bt_keys_foreach_type(int,...);
extern int net_buf_simple_add(int,...);
extern int printk(int,...);
extern void assert_post_action(int,...) __attribute__((noreturn));
extern int FUN_00080fc4(int,...);
extern int FUN_0008104a(int,...);
extern int addr_res_enable(int,...);

void ble_privacy_id_remove(int param_1)
{
    unsigned char bVar1; int iVar2,iVar3; unsigned uVar4;
    unsigned local_48,local_44; int iStack_40; unsigned local_28,local_24;
    iVar2 = 0x20002000;
    if(param_1==0) return;
    bVar1 = *(volatile unsigned char*)0x20002121U;
    if(*(volatile unsigned char*)0x20002120U == 0){
        if(bVar1==0){
            printk(0x00099cbd,0x000f369a,0x000f3509,0x433);
            assert_post_action(0x000f3509,0x433);
        }
    } else if((unsigned)bVar1 <= *(volatile unsigned char*)0x20002120U + 1){
        iVar3 = bt_conn_lookup_state_le(0,0,6);
        if(iVar3 != 0){
            *(volatile unsigned*)(iVar2+0xd4) |= 0x8000;
            *(unsigned char*)(param_1+8) |= 2;
            ble_conn_unref();
            return;
        }
        FUN_00055710(0x000810ab,0);
        iVar3 = addr_res_enable(0);
        if(iVar3==0){
            if(*(volatile unsigned char*)(iVar2+0x120) < *(volatile unsigned char*)(iVar2+0x121)){
                *(volatile unsigned char*)(iVar2+0x121) = *(volatile unsigned char*)(iVar2+0x121) - 1;
                uVar4 = 0x00081035;
                *(unsigned char*)(param_1+8) &= 0xfb;
                bt_keys_foreach_type(2,uVar4,0);
            } else {
                iVar3 = bt_hci_cmd_create(0x2028,7);
                if(iVar3!=0){
                    uVar4 = net_buf_simple_add(iVar3+0xc,7);
                    FUN_00080fc4(uVar4,param_1+1);
                    iVar3 = FUN_00053d70(0x2028,iVar3,0);
                    if(iVar3==0){
                        *(char*)(iVar2+0x121) = *(char*)(iVar2+0x121) - 1;
                        *(unsigned char*)(param_1+8) &= 0xfb;
                        goto LAB_00055142;
                    }
                }
                local_24 = 0x000f36e0;
                local_28 = 2;
                FUN_0008104a(0x00088150,0x1040,&local_28);
            }
        } else {
            local_44 = 0x000f36b3;
            local_48 = 3;
            iStack_40 = iVar3;
            FUN_0008104a(0x00088150,0x1840,&local_48);
        }
LAB_00055142:
        if(*(char*)(iVar2+0x121) != 0){
            addr_res_enable(1);
        }
        FUN_00055710(0x00081081,0);
        return;
    }
    *(volatile unsigned char*)0x20002121U = bVar1 - 1;
    *(unsigned char*)(param_1+8) &= 0xfb;
    return;
}

