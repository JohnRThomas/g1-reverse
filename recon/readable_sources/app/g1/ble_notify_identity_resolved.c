#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00056d1c @ 0x00056d1c
 * public-name: ble_notify_identity_resolved
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_notify_identity_resolved             <= FUN_00056d1c @ 0x00056d1c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_87fec                             @ 0x00087fec
 *   rodata_88058                             @ 0x00088058
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3a8d                             @ 0x000f3a8d   [INLINED -- G6 literal batch]
 *   g_ble_conn_cb_list_head                  @ 0x2000ad1c
 */
/* Reconstructed FUN_00056d1c @ 0x56d1c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
typedef unsigned int uint;
extern void assert_post_action(const char *, unsigned int);
void ble_notify_identity_resolved(int param_1){
  int iVar4 = (*(volatile int8_t*)(param_1+3)==0) ? param_1+0x9e : param_1+0x97;
  int iVar2=*(volatile int*)((unsigned long)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
  while(iVar2!=0){
    int t=*(volatile int*)(iVar2+0x10);
    if(t!=0) ((void(*)(int,int,int))t)(param_1,iVar4,param_1+0x90);
    iVar2=*(volatile int*)(iVar2+0x20);
  }
  uint uVar1=((unsigned long)&rodata_88058) /*=0x88058*/;
  uint uVar3=((unsigned long)&rodata_87fec) /*=0x87fec*/;
  while(1){
    if(uVar1<uVar3){
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"cb <= _bt_conn_cb_list_end") /*=0xf3a8d*/,((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x85c);
      printk(((unsigned long)"\tunexpected list end location\n") /*=0xf0d20*/,0,0,0);
      assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/,0x85c);
    }
    if(uVar1<=uVar3) break;
    int t=*(volatile int*)(uVar3+0x10);
    if(t!=0) ((void(*)(int,int,int))t)(param_1,iVar4,param_1+0x90);
    uVar3=uVar3+0x24;
  }
}
