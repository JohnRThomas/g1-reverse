#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00056c78 @ 0x00056c78
 * public-name: ble_notify_disconnected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_notify_disconnected                  <= FUN_00056c78 @ 0x00056c78
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_le_conn_params_valid                  <= FUN_00080f14 @ 0x00080f14
 * address symbols (name @ address):
 *   rodata_87fec                             @ 0x00087fec
 *   rodata_88058                             @ 0x00088058
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3a8d                             @ 0x000f3a8d   [INLINED -- G6 literal batch]
 *   g_ble_conn_cb_list_head                  @ 0x2000ad1c
 */
/* Reconstructed FUN_00056c78 @ 0x56c78  (parity: 300/300 trials, PROVEN) */

extern int bt_le_conn_params_valid(int);
extern void assert_post_action(int,int);
int ble_notify_disconnected(int param_1,int param_2){
  int iVar2=bt_le_conn_params_valid(param_2);
  if(iVar2==0) return 0;
  unsigned uVar1,uVar5; int iVar3,iVar4;
  for(iVar4=*(int*)((unsigned long)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/; uVar1=((unsigned long)&rodata_88058) /*=0x88058*/, uVar5=((unsigned long)&rodata_87fec) /*=0x87fec*/, iVar4!=0; iVar4=*(int*)(iVar4+0x20)){
    if(*(void**)(iVar4+8)!=0){
      iVar3=(*(int(**)(int,int))(iVar4+8))(param_1,param_2);
      if(iVar3==0) return 0;
      iVar3=bt_le_conn_params_valid(param_2);
      if(iVar3==0) return 0;
    }
  }
  while(1){
    if(uVar1<uVar5){ printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"cb <= _bt_conn_cb_list_end") /*=0xf3a8d*/,((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x676); printk(((unsigned long)"\tunexpected list end location\n") /*=0xf0d20*/); assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x676); }
    if(uVar1<=uVar5) break;
    if(*(void**)(uVar5+8)!=0){
      iVar4=(*(int(**)(int,int))(uVar5+8))(param_1,param_2);
      if(iVar4==0) return 0;
      iVar4=bt_le_conn_params_valid(param_2);
      if(iVar4==0) return 0;
    }
    uVar5=uVar5+0x24;
  }
  return iVar2;
}
