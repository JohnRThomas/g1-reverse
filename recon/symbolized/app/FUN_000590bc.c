#include "g1_app_symbols.h"
/* named: FUN_000590bc */
/* Reconstructed FUN_000590bc @ 0x590bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern short* net_buf_simple_pull_5f594(int,int);
extern void bt_gatt_foreach_attr(int,int,int,void*);
extern void att_send_error_rsp(int*,int,int,int);
extern int atomic_test_and_set_bit_0(void*,int);
extern int bt_gatt_change_aware(int,int);
extern void memset_bytes(void*,int,int);
uint32_t FUN_000590bc(int* param_1, int param_2){
    short* psVar5=(short*)net_buf_simple_pull_5f594(param_2+0xc,4);
    short sVar2=*psVar5;
    (void)psVar5[1];
    int iVar6=bt_gatt_change_aware(*(volatile int*)*param_1,1);
    if(iVar6==0){
        iVar6=atomic_test_and_set_bit_0((void*)(param_1+0x48),5);
        if(iVar6==0) return 0x12;
        return 0;
    }
    if((uint16_t)sVar2==0) return 1;
    char stackbuf[0x30];
    memset_bytes(stackbuf,0,0x14);
    bt_gatt_foreach_attr(sVar2,sVar2,((uintptr_t)&tbl_588b0) /*=0x588b5*/,stackbuf);
    att_send_error_rsp(param_1,0x16,sVar2,1);
    return 0;
}

