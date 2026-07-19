#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00054260 @ 0x00054260
 * public-name: bt_conn_encrypt_change_handle_le
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_security_err_lookup                   <= FUN_00054250 @ 0x00054250
 *   bt_conn_encrypt_change_handle_le         <= FUN_00054260 @ 0x00054260
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
/* Reconstructed FUN_00054260 @ 0x54260  (parity: 300/300 trials, PROVEN) */

extern int bt_security_err_lookup(int a);
extern void ble_conn_unref(int a);
extern int ble_conn_lookup_masked(unsigned a, int b);
extern void bt_conn_disconnect_by_state(int a, int b);
extern void ble_notify_remote_info_available(int a, int b, int c);
extern void smp_alloc_pairing_keys(void);
extern int update_sec_level(int a);
extern void bt_log_forward_3arg(unsigned a, unsigned b, void*c);
void bt_conn_encrypt_change_handle_le(int param_1){
    char *p = *(char**)(param_1 + 0xc);
    unsigned uVar5 = *(volatile unsigned short*)(p + 1);
    unsigned cVar1 = *(volatile unsigned char*)p;
    int iVar2 = ble_conn_lookup_masked(uVar5, 0xf);
    unsigned loc[4];
    if (iVar2 == 0){
        loc[1] = ((unsigned long)&rodata_f2e3c) /*=0xf2e3c*/; loc[0]=3; loc[2]=uVar5;
        bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840, loc);
        return;
    }
    if (cVar1 == 0 && *(volatile unsigned char*)(iVar2 + 2) == 1){
        smp_alloc_pairing_keys();
        int iVar4 = update_sec_level(iVar2);
        if (iVar4 == 0){
            int u = bt_security_err_lookup(5);
            ble_notify_remote_info_available(iVar2, 5, u);
            loc[1] = ((unsigned long)&rodata_f30dd) /*=0xf30dd*/; loc[0]=2;
            bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1040, loc);
            bt_conn_disconnect_by_state(iVar2, 5);
            ble_conn_unref(iVar2);
            return;
        }
    }
    int u = bt_security_err_lookup((int)cVar1);
    ble_notify_remote_info_available(iVar2, (int)cVar1, u);
    ble_conn_unref(iVar2);
    return;
}
