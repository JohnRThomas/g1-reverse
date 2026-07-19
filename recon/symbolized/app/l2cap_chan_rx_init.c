#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00057484 @ 0x00057484
 * public-name: l2cap_chan_rx_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_chan_rx_init                       <= FUN_00057484 @ 0x00057484
 *   log_msg_3arg_thunk                       <= FUN_00081746 @ 0x00081746
 * address symbols (name @ address):
 *   rodata_88160                             @ 0x00088160
 *   rodata_f3f11                             @ 0x000f3f11
 */
/* Reconstructed FUN_00057484 @ 0x57484  (parity: 300/300 trials, PROVEN) */
extern void log_msg_3arg_thunk(unsigned,int,void*);
void l2cap_chan_rx_init(int param_1){
    if (*(short*)(param_1 + 0x16) == 0){
        *(short*)(param_1 + 0x16) = 0x1f0;
    }
    unsigned uVar1 = *(unsigned short*)(param_1 + 0x16);
    unsigned uVar2 = uVar1;
    if (uVar1 >= 0x1f0) uVar2 = 0x1f0;
    *(short*)(param_1 + 0x18) = (short)(uVar2 + 2);
    if (*(int*)(*(int*)(param_1 + 4) + 0x10) == 0 && ((uVar2 + 2) & 0xffff) <= (uVar1 + 1)){
        struct { unsigned count, format; } record = {2, ((unsigned long)&rodata_f3f11) /*=0xf3f11*/};
        log_msg_3arg_thunk(((unsigned long)&rodata_88160) /*=0x88160*/, 0x1080, &record);
        *(short*)(param_1 + 0x16) = *(short*)(param_1 + 0x18) - 2;
    }
    __atomic_exchange_n((unsigned int *)(param_1 + 0x1c), 1,
                        __ATOMIC_ACQ_REL);
}
