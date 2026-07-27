#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00054308 @ 0x00054308
 * public-name: bt_conn_encrypt_change_handle_generic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_security_err_lookup                   <= FUN_00054250 @ 0x00054250
 *   bt_conn_encrypt_change_handle_generic    <= FUN_00054308 @ 0x00054308
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   ble_conn_lookup_masked                   <= FUN_00056908 @ 0x00056908
 *   bt_conn_disconnect_by_state              <= FUN_00056a68 @ 0x00056a68
 *   ble_notify_remote_info_available         <= FUN_00056da8 @ 0x00056da8
 *   smp_alloc_pairing_keys                   <= FUN_0005e47c @ 0x0005e47c
 *   update_sec_level                         <= FUN_00080e38 @ 0x00080e38
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2e3c                             @ 0x000f2e3c
 *   rodata_f30dd                             @ 0x000f30dd
 */
/* Reconstructed FUN_00054308 @ 0x54308  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int bt_security_err_lookup(int);
extern void ble_conn_unref(int);
extern int ble_conn_lookup_masked(unsigned,int);
extern void bt_conn_disconnect_by_state(unsigned int, int);
extern void ble_notify_remote_info_available(int,int,int);
extern void smp_alloc_pairing_keys(void);
extern int update_sec_level(int);
extern void bt_log_forward_3arg(int,int,void*);

void bt_conn_encrypt_change_handle_generic(int param_1){
    char *pcVar6 = *(char**)(param_1+0xc);
    unsigned uVar1 = *(unsigned short*)(pcVar6+1);
    char cVar5 = *pcVar6;
    int uVar3;
    volatile int loc[8];
    int iVar2 = ble_conn_lookup_masked(uVar1, 0xf);
    if (iVar2 == 0){
        loc[0]=3; loc[1]=0; loc[2]=uVar1; loc[3]=((unsigned long)&rodata_f2e3c) /*=0xf2e3c*/;
        bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840, (void*)&loc[0]);
        return;
    }
    if (cVar5 == 0){
        cVar5 = pcVar6[3];
        *(char*)(iVar2+0xb) = cVar5;
        if (*(char*)(iVar2+2) == 1){
            if (cVar5 != 0) smp_alloc_pairing_keys();
            int iVar4 = update_sec_level(iVar2);
            if (iVar4 == 0){
                uVar3 = bt_security_err_lookup(5);
                ble_notify_remote_info_available(iVar2, 5, uVar3);
                loc[4]=2; loc[5]=((unsigned long)&rodata_f30dd) /*=0xf30dd*/;
                bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1040, (void*)&loc[4]);
                bt_conn_disconnect_by_state(iVar2, 5);
                goto LAB;
            }
        }
        uVar3 = bt_security_err_lookup(0);
        cVar5 = 0;
    } else {
        uVar3 = bt_security_err_lookup(cVar5);
    }
    ble_notify_remote_info_available(iVar2, cVar5, uVar3);
    LAB:
    ble_conn_unref(iVar2);
}
