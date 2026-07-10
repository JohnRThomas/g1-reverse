#include "g1_app_symbols.h"
/* named: FUN_00053530 */
/* Reconstructed FUN_00053530 @ 0x53530  (parity: 300/300 trials, PROVEN) */

extern void net_buf_slist_put(unsigned int a, unsigned int b);
extern void FUN_00080ea2(unsigned int a, unsigned int b, void *c);
extern int k_work_submit_to_queue(unsigned int a, unsigned int b);

void FUN_00053530(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int local_20;
    unsigned int local_1c;
    int iStack_18;

    net_buf_slist_put(((uintptr_t)&g_bt_hci_recv_fifo) /*=0x20002144*/, param_1);
    iStack_18 = k_work_submit_to_queue(((uintptr_t)&bt_workqueue) /*=0x20005f08*/, ((uintptr_t)&g_bt_hci_rx_work) /*=0x20002980*/);
    if (iStack_18 < 0) {
        local_1c = "Could not submit rx_work: %d" /*=0xf2ddb*/;
        local_20 = 3;
        FUN_00080ea2(((uintptr_t)&tbl_880d8) /*=0x88138*/, 0x1840, &local_20);
    }
}

