#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00054828 @ 0x00054828
 * public-name: bt_hci_core_recv_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_rx_work_submit                    <= FUN_00053530 @ 0x00053530
 *   hci_event_prio                           <= FUN_00054784 @ 0x00054784
 *   bt_hci_core_recv_dispatch                <= FUN_00054828 @ 0x00054828
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   bt_hci_evt_get_flags                     <= FUN_00080e14 @ 0x00080e14
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f3191                             @ 0x000f3191
 */
/* Reconstructed FUN_00054828 @ 0x54828  (parity: 300/300 trials, PROVEN) */
extern void bt_hci_rx_work_submit(int);
extern int bt_hci_evt_get_flags(unsigned);
extern void hci_event_prio(int);
extern void net_buf_unref(int);
extern void bt_log_forward_3arg(unsigned,int,void*);
unsigned bt_hci_core_recv_dispatch(int param_1){
    unsigned char uStack_18 = *(unsigned char*)(param_1 + 0x18);
    if (uStack_18 == 1){
        int r3 = *(int*)(param_1 + 0xc);
        int iVar1 = bt_hci_evt_get_flags(*(unsigned char*)r3);
        if ((int)((unsigned)iVar1 << 31) < 0) hci_event_prio(param_1);
        if ((int)((unsigned)iVar1 << 30) >= 0) return 0;
    } else if (uStack_18 != 3){
        volatile unsigned local[8];
        local[4]=3; local[5]=((unsigned long)&rodata_f3191) /*=0xf3191*/;
        bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x1840, (void*)&local[4]);
        net_buf_unref(param_1);
        return 0xffffffea;
    }
    bt_hci_rx_work_submit(param_1);
    return 0;
}
