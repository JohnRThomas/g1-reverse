/* readable reconstruction; identity: FUN_0005a9f4 @ 0x0005a9f4
 * public-name: bt_gatt_attr_get_handle
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_attr_get_handle                  <= FUN_0005a9f4 @ 0x0005a9f4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_88058                             @ 0x00088058
 *   rodata_88070                             @ 0x00088070
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f49a5                             @ 0x000f49a5
 */
/* Reconstructed FUN_0005a9f4 @ 0x5a9f4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,...);
extern void assert_post_action(unsigned int,...);
unsigned int bt_gatt_attr_get_handle(unsigned int param_1){
  unsigned int uVar1=param_1; volatile unsigned int* puVar2;
  unsigned int uVar3,uVar4,uVar5,uVar6,uVar7;
  if(param_1!=0 && (uVar1=(unsigned int)*(unsigned short*)(param_1+0x10), uVar1==0)){
    puVar2=(volatile unsigned int*)0x00088058UL; uVar4=1;
    while(1){
      if((volatile unsigned int*)0x00088070UL < puVar2){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0x000f49a5,0x000f46b8,0x713);
        printk(((unsigned long)"\tunexpected list end location\n"));
        assert_post_action(0x000f46b8,0x713);
      }
      if((volatile unsigned int*)0x00088070UL <= puVar2) break;
      uVar7=puVar2[0]; uVar6=puVar2[1];
      if((param_1<uVar7)||(((uVar6*0x14+uVar7)-0x14)<param_1)){
        uVar3=(uVar4+uVar6)&0xffff;
      } else {
        for(uVar5=0; uVar3=(uVar4+uVar5)&0xffff, uVar5!=uVar6; uVar5=uVar5+1){
          if(param_1==uVar5*0x14+uVar7) return uVar3;
        }
      }
      puVar2=puVar2+2; uVar4=uVar3;
    }
  }
  return uVar1;
}
