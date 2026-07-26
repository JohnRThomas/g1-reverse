#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e6a8 @ 0x0004e6a8
 * public-name: settings_commit_subtree
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_commit_subtree                  <= FUN_0004e6a8 @ 0x0004e6a8
 *   bt_dev_settings_commit                   <= FUN_000530c4 @ 0x000530c4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   settings_name_steq                       <= FUN_0007f1a0 @ 0x0007f1a0
 * address symbols (name @ address):
 *   __settings_handler_static_list_start     @ 0x000882b0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   rodata_f1126                             @ 0x000f1126
 *   rodata_f1158                             @ 0x000f1158   [INLINED -- G6 literal batch]
 *   g_settings_handlers                      @ 0x2000a10c
 */
/* Reconstructed FUN_0004e6a8 @ 0x4e6a8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int bt_dev_settings_commit(int,...);
extern void assert_post_action(int,...);
extern int settings_name_steq(int,...);
int settings_commit_subtree(int param_1,unsigned param_2,unsigned param_3,unsigned param_4){
  unsigned *puVar1 = (unsigned*)0x88328UL;
  unsigned *puVar3 = (unsigned*)((unsigned long)&__settings_handler_static_list_start) /*=0x882b0*/;
  int iVar2=0;
  int iVar5=0;
  while(1){
    if(puVar1 < puVar3){
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"ch <= _settings_handler_static_list_end") /*=0xf1158*/,((unsigned long)&rodata_f1126) /*=0xf1126*/,0xf4,param_4);
      printk(((unsigned long)"\tunexpected list end location\n") /*=0xf0d20*/);
      assert_post_action(((unsigned long)&rodata_f1126) /*=0xf1126*/,0xf4);
    }
    if(puVar1 <= puVar3) break;
    if(((param_1!=0) && (iVar2=settings_name_steq(puVar3[0],param_1,0), iVar2==0)) ||
       ((((void*)puVar3[3]==0) || (iVar2=((int(*)(void))puVar3[3])(), iVar5!=0)))){
      iVar2=iVar5;
    }
    puVar3 += 5;
    iVar5 = iVar2;
  }
  int *piVar4;
  for(piVar4=(int*)*(volatile unsigned*)((unsigned long)&g_settings_handlers) /*=0x2000a10c*/; piVar4!=0; piVar4=(int*)*piVar4){
    if((((param_1==0)||(iVar2=settings_name_steq(piVar4[-5],param_1,0),iVar2!=0)) &&
        ((void*)piVar4[-2]!=0)) && (iVar2=((int(*)(void))piVar4[-2])(),iVar5==0)){
      iVar5=iVar2;
    }
  }
  return iVar5;
}
