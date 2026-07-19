#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00063c3c @ 0x00063c3c
 * public-name: power_manager_system_off
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   app_event_manager_submit                 <= FUN_0004f770 @ 0x0004f770
 *   ancs_notify_table_is_idle                <= FUN_00063ba8 @ 0x00063ba8
 *   app_event_submit_power                   <= FUN_00063bcc @ 0x00063bcc
 *   power_manager_set_system_off_flag        <= FUN_00063c14 @ 0x00063c14
 *   power_manager_system_off                 <= FUN_00063c3c @ 0x00063c3c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_88268                             @ 0x00088268
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6716                             @ 0x000f6716
 *   rodata_f6749                             @ 0x000f6749
 *   rodata_f6769                             @ 0x000f6769
 *   rodata_f67a5                             @ 0x000f67a5
 *   g_caf_power_manager_system_off_flag      @ 0x2001d563
 */
/* Reconstructed FUN_00063c3c @ 0x63c3c  (parity: 300/300 trials, PROVEN) */

extern int z_log_msg_runtime_create(unsigned,int,void*,int);
extern int app_event_manager_submit(int);
extern int ancs_notify_table_is_idle(int);
extern int app_event_submit_power(void);
extern int power_manager_set_system_off_flag(int);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
void power_manager_system_off(void){
  int iVar1; unsigned local_18, local_14;
  unsigned char r5 = *(volatile unsigned char*)((unsigned long)&g_caf_power_manager_system_off_flag) /*=0x2001d563*/;
  if(r5 != 0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f6749) /*=0xf6749*/,((unsigned long)&rodata_f6716) /*=0xf6716*/,0xab);
    assert_post_action(((unsigned long)&rodata_f6716) /*=0xf6716*/,0xab);
  }
  L:
  iVar1 = ancs_notify_table_is_idle(r5);
  if(iVar1==0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f6769) /*=0xf6769*/,((unsigned long)&rodata_f6716) /*=0xf6716*/,0xac);
    assert_post_action(((unsigned long)&rodata_f6716) /*=0xf6716*/,0xac);
    goto L;
  }
  local_14=((unsigned long)&rodata_f67a5) /*=0xf67a5*/; local_18=2;
  z_log_msg_runtime_create(((unsigned long)&rodata_88268) /*=0x88268*/,0x10c0,&local_18,0);
  iVar1=app_event_submit_power();
  *(unsigned char*)(iVar1+8)=r5;
  power_manager_set_system_off_flag(1);
  app_event_manager_submit(iVar1);
  return;
}
