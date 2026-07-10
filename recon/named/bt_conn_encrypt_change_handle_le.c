/* named: bt_conn_encrypt_change_handle_le */
/* Reconstructed bt_conn_encrypt_change_handle_le @ 0x54260  (parity: 300/300 trials, PROVEN) */

extern int bt_security_err_lookup(int a);
extern void ble_conn_unref(int a);
extern int ble_conn_lookup_masked(unsigned a, int b);
extern void FUN_00056a68(int a, int b);
extern void ble_notify_remote_info_available(int a, int b, int c);
extern void smp_alloc_pairing_keys(void);
extern int update_sec_level(int a);
extern void FUN_00080ea2(unsigned a, unsigned b, void*c);
void bt_conn_encrypt_change_handle_le(int param_1){
    char *p = *(char**)(param_1 + 0xc);
    unsigned uVar5 = *(volatile unsigned short*)(p + 1);
    unsigned cVar1 = *(volatile unsigned char*)p;
    int iVar2 = ble_conn_lookup_masked(uVar5, 0xf);
    unsigned loc[4];
    if (iVar2 == 0){
        loc[1] = 0x000f2e3c; loc[0]=3; loc[2]=uVar5;
        FUN_00080ea2(0x00088138, 0x1840, loc);
        return;
    }
    if (cVar1 == 0 && *(volatile unsigned char*)(iVar2 + 2) == 1){
        smp_alloc_pairing_keys();
        int iVar4 = update_sec_level(iVar2);
        if (iVar4 == 0){
            int u = bt_security_err_lookup(5);
            ble_notify_remote_info_available(iVar2, 5, u);
            loc[1] = 0x000f30dd; loc[0]=2;
            FUN_00080ea2(0x00088138, 0x1040, loc);
            FUN_00056a68(iVar2, 5);
            ble_conn_unref(iVar2);
            return;
        }
    }
    int u = bt_security_err_lookup((int)cVar1);
    ble_notify_remote_info_available(iVar2, (int)cVar1, u);
    ble_conn_unref(iVar2);
    return;
}

