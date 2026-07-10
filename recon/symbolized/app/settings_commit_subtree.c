#include "g1_app_symbols.h"
/* named: settings_commit_subtree */
/* globals referenced:
//   0x000882b0  __settings_handler_static_list_start 
//   0x00088328  __settings_handler_static_list_end 
//   0x2000a10c  g_settings_handlers          
*/
/* Reconstructed settings_commit_subtree @ 0x4e6a8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_000530c4(int,...);
extern void assert_post_action(int,...);
extern void printk(int,...);
extern int settings_name_steq(int,...);
int settings_commit_subtree(int param_1,unsigned param_2,unsigned param_3,unsigned param_4){
  unsigned *puVar1 = (unsigned*)((uintptr_t)&__settings_handler_static_list_end) /*=0x88328*/;
  unsigned *puVar3 = (unsigned*)((uintptr_t)&__settings_handler_static_list_start) /*=0x882b0*/;
  int iVar2=0;
  int iVar5=0;
  while(1){
    if(puVar1 < puVar3){
      printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"ch <= _settings_handler_static_list_end" /*=0xf1158*/,"WEST_TOPDIR/zephyr/subsys/settings/src/settings.c" /*=0xf1126*/,0xf4,param_4);
      printk("\tunexpected list end location\n" /*=0xf0d20*/);
      assert_post_action("WEST_TOPDIR/zephyr/subsys/settings/src/settings.c" /*=0xf1126*/,0xf4);
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
  for(piVar4=(int*)*(volatile unsigned*)((uintptr_t)&g_settings_handlers) /*=0x2000a10c*/; piVar4!=0; piVar4=(int*)*piVar4){
    if((((param_1==0)||(iVar2=settings_name_steq(piVar4[-5],param_1,0),iVar2!=0)) &&
        ((void*)piVar4[-2]!=0)) && (iVar2=((int(*)(void))piVar4[-2])(),iVar5==0)){
      iVar5=iVar2;
    }
  }
  return iVar5;
}

