#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055094 @ 0x00055094
 * public-name: ble_privacy_id_remove
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_create                        <= FUN_00053cd4 @ 0x00053cd4
 *   ble_privacy_id_remove                    <= FUN_00055094 @ 0x00055094
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   bt_conn_lookup_state_le                  <= FUN_00056f08 @ 0x00056f08
 *   bt_keys_foreach_type                     <= FUN_0005e758 @ 0x0005e758
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_81035                             @ 0x00081035
 *   ADDR_bt_le_adv_clear_pending_flag_THUMB  @ 0x00081081
 *   rodata_810ab                             @ 0x000810ab
 *   rodata_88150                             @ 0x00088150
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f3509                             @ 0x000f3509
 *   rodata_f369a                             @ 0x000f369a
 *   rodata_f36b3                             @ 0x000f36b3
 *   rodata_f36e0                             @ 0x000f36e0
 *   g_ble_dev_state                          @ 0x20002000
 *   g_ble_rl_entries_max                     @ 0x20002120
 *   g_ble_rl_entries_cnt                     @ 0x20002121
 */
/* Reconstructed FUN_00055094 @ 0x55094  (parity: 300/300 trials, PROVEN) */
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
extern int FUN_00081050(int,...);

void ble_privacy_id_remove(int param_1)
{
    unsigned char bVar1; int iVar2,iVar3; unsigned uVar4;
    unsigned local_48,local_44; int iStack_40; unsigned local_28,local_24;
    iVar2 = ((unsigned long)&g_ble_dev_state) /*=0x20002000*/;
    if(param_1==0) return;
    bVar1 = *(volatile unsigned char*)((unsigned long)&g_ble_rl_entries_cnt) /*=0x20002121*/;
    if(*(volatile unsigned char*)((unsigned long)&g_ble_rl_entries_max) /*=0x20002120*/ == 0){
        if(bVar1==0){
            printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f369a) /*=0xf369a*/,((unsigned long)&rodata_f3509) /*=0xf3509*/,0x433);
            assert_post_action(((unsigned long)&rodata_f3509) /*=0xf3509*/,0x433);
        }
    } else if((unsigned)bVar1 <= *(volatile unsigned char*)((unsigned long)&g_ble_rl_entries_max) /*=0x20002120*/ + 1){
        iVar3 = bt_conn_lookup_state_le(0,0,6);
        if(iVar3 != 0){
            __atomic_fetch_or((unsigned *)(uintptr_t)(iVar2 + 0xd4), 0x8000,
                              __ATOMIC_RELAXED);
            *(unsigned char*)(param_1+8) |= 2;
            ble_conn_unref();
            return;
        }
        FUN_00055710(((unsigned long)&rodata_810ab) /*=0x810ab*/,0);
        iVar3 = FUN_00081050(0);
        if(iVar3==0){
            if(*(volatile unsigned char*)(iVar2+0x120) < *(volatile unsigned char*)(iVar2+0x121)){
                *(volatile unsigned char*)(iVar2+0x121) = *(volatile unsigned char*)(iVar2+0x121) - 1;
                uVar4 = ((unsigned long)&rodata_81035) /*=0x81035*/;
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
                local_24 = ((unsigned long)&rodata_f36e0) /*=0xf36e0*/;
                local_28 = 2;
                FUN_0008104a(((unsigned long)&rodata_88150) /*=0x88150*/,0x1040,&local_28);
            }
        } else {
            local_44 = ((unsigned long)&rodata_f36b3) /*=0xf36b3*/;
            local_48 = 3;
            iStack_40 = iVar3;
            FUN_0008104a(((unsigned long)&rodata_88150) /*=0x88150*/,0x1840,&local_48);
        }
LAB_00055142:
        if(*(char*)(iVar2+0x121) != 0){
            FUN_00081050(1);
        }
        FUN_00055710(ADDR_bt_le_adv_clear_pending_flag_THUMB /*=0x81081*/,0);
        return;
    }
    *(volatile unsigned char*)((unsigned long)&g_ble_rl_entries_cnt) /*=0x20002121*/ = bVar1 - 1;
    *(unsigned char*)(param_1+8) &= 0xfb;
    return;
}
