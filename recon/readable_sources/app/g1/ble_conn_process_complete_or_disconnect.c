#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_ble_conn_complete_ctx__param_0215      [param_0215; G1-original]
 * Raw function identity: 0x000570a0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000570a0 @ 0x000570a0
 * public-name: ble_conn_process_complete_or_disconnect
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_disconnected                        <= FUN_00018adc @ 0x00018adc
 *   ble_conn_unref                           <= FUN_000566a4 @ 0x000566a4
 *   send_conn_le_param_update                <= FUN_00057038 @ 0x00057038
 *   ble_conn_process_complete_or_disconnect  <= FUN_000570a0 @ 0x000570a0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   atomic_and_2                             <= FUN_000813b4 @ 0x000813b4
 *   bt_conn_call_4arg_zero                   <= FUN_000813ca @ 0x000813ca
 *   bt_l2cap_disconnected                    <= FUN_000817ea @ 0x000817ea
 * address symbols (name @ address):
 *   rodata_87fec                             @ 0x00087fec
 *   rodata_88058                             @ 0x00088058
 *   log_module_bt_conn                       @ 0x00088108
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3a8d                             @ 0x000f3a8d   [INLINED -- G6 literal batch]
 *   rodata_f3dff                             @ 0x000f3dff
 *   rodata_f3e24                             @ 0x000f3e24
 *   g_ble_conn_cb_list_head                  @ 0x2000ad1c
 */
/* Reconstructed FUN_000570a0 @ 0x570a0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern void ancs_disconnected(void);
extern void ble_conn_unref(int);
extern int send_conn_le_param_update(int,void*);
extern void assert_post_action(unsigned,unsigned);
extern int atomic_and_2(volatile unsigned*,unsigned);
extern void bt_conn_call_4arg_zero(unsigned,unsigned,void*);
extern void bt_l2cap_disconnected(int);

void ble_conn_process_complete_or_disconnect(int param_1){
  int iVar5 = param_1 - 0x60;
  unsigned uVar1, uVar3;
  int iVar2;
  if(*(volatile char*)(param_1-0x53) == 0){
    bt_l2cap_disconnected(iVar5);
    for(iVar2 = *(volatile int*)((unsigned long)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
        uVar1 = ((unsigned long)&rodata_88058) /*=0x88058*/, uVar3 = ((unsigned long)&rodata_87fec) /*=0x87fec*/, iVar2 != 0;
        iVar2 = *(volatile int*)(iVar2+0x20)){
      if(*(void**)(iVar2+4) != 0)
        (*(void(**)(int,unsigned char))(iVar2+4))(iVar5,*(volatile uint8_t*)(param_1-0x54));
    }
    while(1){
      if(uVar1 < uVar3){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"cb <= _bt_conn_cb_list_end") /*=0xf3a8d*/,((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x5fe);
        printk(((unsigned long)"\tunexpected list end location\n") /*=0xf0d20*/);
        assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x5fe);
      }
      if(uVar1 <= uVar3) break;
      if(*(void**)(uVar3+4) != 0)
        (*(void(**)(int,unsigned char))(uVar3+4))(iVar5,*(volatile uint8_t*)(param_1-0x54));
      uVar3 = uVar3 + 0x24;
    }
    ble_conn_unref(iVar5);
    return;
  }
  if(*(volatile char*)(param_1-0x5e) != 1) return;
  volatile unsigned *puVar4 = (volatile unsigned*)(param_1-0x5c);
  unsigned local_20, local_1c, local_2c, local_30;
  int iStack_28;
  iVar2 = atomic_and_2(puVar4, 0xfffffdffU);
  if((int)(iVar2 << 0x16) < 0){
    local_20 = *(volatile unsigned*)(param_1+0x48);
    local_1c = *(volatile unsigned*)(param_1+0x50);
    iStack_28 = send_conn_le_param_update(iVar5,&local_20);
    local_2c = ((unsigned long)&rodata_f3dff) /*=0xf3dff*/;
    if(iStack_28 == 0){
      atomic_and_2(puVar4, 0xfffffeffU);
      goto LAB;
    }
  } else {
    local_20 = 0x00280018U;
    local_1c = 0x2a0000U;
    iStack_28 = send_conn_le_param_update(iVar5,&local_20);
    local_2c = ((unsigned long)&rodata_f3e24) /*=0xf3e24*/;
    if(iStack_28 == 0){
      *puVar4 = *puVar4 | 0x100;
      goto LAB;
    }
  }
  local_30 = 3;
  bt_conn_call_4arg_zero(((unsigned long)&log_module_bt_conn) /*=0x88108*/, 0x1880, &local_30);
LAB:
  *puVar4 = *puVar4 | 0x80;
  (void)local_2c; (void)local_1c;
  return;
}
