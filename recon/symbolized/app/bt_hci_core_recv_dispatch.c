#include "g1_app_symbols.h"
/* named: bt_hci_core_recv_dispatch */
/* Reconstructed bt_hci_core_recv_dispatch @ 0x54828  (parity: 300/300 trials, PROVEN) */
extern void FUN_00053530(int);
extern int bt_hci_evt_get_flags(unsigned);
extern void hci_event_prio(int);
extern void net_buf_unref(int);
extern void FUN_00080ea2(unsigned,int,void*);
unsigned bt_hci_core_recv_dispatch(int param_1){
    unsigned char uStack_18 = *(unsigned char*)(param_1 + 0x18);
    if (uStack_18 == 1){
        int r3 = *(int*)(param_1 + 0xc);
        int iVar1 = bt_hci_evt_get_flags(*(unsigned char*)r3);
        if ((int)((unsigned)iVar1 << 31) < 0) hci_event_prio(param_1);
        if ((int)((unsigned)iVar1 << 30) >= 0) return 0;
    } else if (uStack_18 != 3){
        volatile unsigned local[8];
        local[4]=3; local[5]="Invalid buf type %u" /*=0xf3191*/;
        FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1840, (void*)&local[4]);
        net_buf_unref(param_1);
        return 0xffffffea;
    }
    FUN_00053530(param_1);
    return 0;
}

