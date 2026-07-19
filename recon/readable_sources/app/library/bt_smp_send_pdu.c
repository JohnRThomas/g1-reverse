#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_smp__param_0265                     [param_0265; library]
 * Raw function identity: 0x0005cb38.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005cb38 @ 0x0005cb38
 * public-name: bt_smp_send_pdu
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_smp_send_pdu                          <= FUN_0005cb38 @ 0x0005cb38
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   k_work_reschedule                        <= FUN_0007350c @ 0x0007350c
 *   bt_conn_create_pdu                       <= FUN_00081820 @ 0x00081820
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_f0000                             @ 0x000f0000
 *   rodata_f4557                             @ 0x000f4557
 */
/* Reconstructed FUN_0005cb38 @ 0x5cb38  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long bt_conn_create_pdu(unsigned,int,unsigned,unsigned,int);
extern void net_buf_unref(unsigned);
extern void smp_log_message(unsigned,unsigned,void*);
extern void k_work_reschedule(int,int,unsigned,int);

void bt_smp_send_pdu(int param_1, unsigned param_2, unsigned param_3){
  long long uVar1 = bt_conn_create_pdu(*(volatile unsigned*)(param_1+0xf0), 6, param_2, param_3, 0);
  if((int)uVar1 != 0){
    if((int)uVar1 == -0x69){
      unsigned local_18, local_14;
      local_14 = ((unsigned long)&rodata_f4557) /*=0xf4557*/;
      local_18 = 2;
      smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1040, &local_18);
      (void)local_14;
    }
    net_buf_unref(param_2);
    return;
  }
  k_work_reschedule(param_1+0x208, (int)((unsigned long long)uVar1 >> 0x20), ((unsigned long)&rodata_f0000) /*=0xf0000*/, 0);
}
