#include "g1_app_symbols.h"
/* named: power_manager_system_off */
/* Reconstructed power_manager_system_off @ 0x63c3c  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004d944(unsigned,int,void*,int);
extern int FUN_0004f770(int);
extern int FUN_00063ba8(int);
extern int FUN_00063bcc(void);
extern int FUN_00063c14(int);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
void power_manager_system_off(void){
  int iVar1; unsigned local_18, local_14;
  unsigned char r5 = *(volatile unsigned char*)((uintptr_t)&g_caf_power_manager_system_off_flag) /*=0x2001d563*/;
  if(r5 != 0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"power_state == POWER_STATE_IDLE" /*=0xf6749*/,"WEST_TOPDIR/nrf/subsys/caf/modules/power_manager.c" /*=0xf6716*/,0xab);
    assert_post_action("WEST_TOPDIR/nrf/subsys/caf/modules/power_manager.c" /*=0xf6716*/,0xab);
  }
  L:
  iVar1 = FUN_00063ba8(r5);
  if(iVar1==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"check_if_power_state_allowed(POWER_MANAGER_LEVEL_SUSPENDED)" /*=0xf6769*/,"WEST_TOPDIR/nrf/subsys/caf/modules/power_manager.c" /*=0xf6716*/,0xac);
    assert_post_action("WEST_TOPDIR/nrf/subsys/caf/modules/power_manager.c" /*=0xf6716*/,0xac);
    goto L;
  }
  local_14="System power down" /*=0xf67a5*/; local_18=2;
  FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88268*/,0x10c0,&local_18,0);
  iVar1=FUN_00063bcc();
  *(unsigned char*)(iVar1+8)=r5;
  FUN_00063c14(1);
  FUN_0004f770(iVar1);
  return;
}

