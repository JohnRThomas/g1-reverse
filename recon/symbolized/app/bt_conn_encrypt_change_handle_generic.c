#include "g1_app_symbols.h"
/* named: bt_conn_encrypt_change_handle_generic */
/* Reconstructed bt_conn_encrypt_change_handle_generic @ 0x54308  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int bt_security_err_lookup(int);
extern void ble_conn_unref(int);
extern int ble_conn_lookup_masked(unsigned,int);
extern void FUN_00056a68(int,int);
extern void ble_notify_remote_info_available(int,int,int);
extern void smp_alloc_pairing_keys(void);
extern int update_sec_level(int);
extern void FUN_00080ea2(int,int,void*);

void bt_conn_encrypt_change_handle_generic(int param_1){
    char *pcVar6 = *(char**)(param_1+0xc);
    unsigned uVar1 = *(unsigned short*)(pcVar6+1);
    char cVar5 = *pcVar6;
    int uVar3;
    volatile int loc[8];
    int iVar2 = ble_conn_lookup_masked(uVar1, 0xf);
    if (iVar2 == 0){
        loc[0]=3; loc[1]=0; loc[2]=uVar1; loc[3]="Unable to look up conn with handle %u" /*=0xf2e3c*/;
        FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1840, (void*)&loc[0]);
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
                loc[4]=2; loc[5]="Failed to set required security level" /*=0xf30dd*/;
                FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1040, (void*)&loc[4]);
                FUN_00056a68(iVar2, 5);
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

