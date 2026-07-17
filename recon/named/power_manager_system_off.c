/* readable reconstruction; identity: FUN_00063c3c @ 0x00063c3c
 * public-name: power_manager_system_off
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
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

extern int FUN_0004d944(unsigned,int,void*,int);
extern int FUN_0004f770(int);
extern int FUN_00063ba8(int);
extern int FUN_00063bcc(void);
extern int FUN_00063c14(int);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
void power_manager_system_off(void){
  int iVar1; unsigned local_18, local_14;
  unsigned char r5 = *(volatile unsigned char*)0x2001d563UL;
  if(r5 != 0){
    printk(0x99cbd,0xf6749,0xf6716,0xab);
    assert_post_action(0xf6716,0xab);
  }
  L:
  iVar1 = FUN_00063ba8(r5);
  if(iVar1==0){
    printk(0x99cbd,0xf6769,0xf6716,0xac);
    assert_post_action(0xf6716,0xac);
    goto L;
  }
  local_14=0xf67a5; local_18=2;
  FUN_0004d944(0x88268,0x10c0,&local_18,0);
  iVar1=FUN_00063bcc();
  *(unsigned char*)(iVar1+8)=r5;
  FUN_00063c14(1);
  FUN_0004f770(iVar1);
  return;
}
