#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005e7c8 @ 0x0005e7c8
 * public-name: bt_keys_find
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_keys_find                             <= FUN_0005e7c8 @ 0x0005e7c8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f52ac                             @ 0x000f52ac
 *   bt_keys_pool                             @ 0x2000af4c
 *   g_bt_keys_pool_entry1_addr               @ 0x2000afa9
 */
/* Reconstructed FUN_0005e7c8 @ 0x5e7c8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,unsigned int,unsigned int,int);
extern void assert_post_action(unsigned int,int);
extern int memcmp(unsigned int,int,int,unsigned int,unsigned int);
unsigned char* bt_keys_find(unsigned short param_1,unsigned int param_2,int param_3,unsigned int param_4){
  unsigned char* pbVar1=(unsigned char*)((unsigned long)&bt_keys_pool) /*=0x2000af4c*/;
  int iVar2;
  if(param_3==0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f52ac) /*=0xf52ac*/,((unsigned long)&rodata_f5268) /*=0xf5268*/,0xc0);
    assert_post_action(((unsigned long)&rodata_f5268) /*=0xf5268*/,0xc0);
  }
  if(((*(volatile unsigned short*)(((unsigned long)&bt_keys_pool) /*=0x2000af4c*/+0xe)&param_1)==0) ||
     (*(volatile unsigned char*)((unsigned long)&bt_keys_pool) /*=0x2000af4c*/!=param_2) ||
     (iVar2=memcmp(((unsigned long)&bt_keys_pool) /*=0x2000af4c*/+1,param_3,7,*(volatile unsigned char*)((unsigned long)&bt_keys_pool) /*=0x2000af4c*/,param_4),iVar2!=0)){
    if((*(volatile unsigned short*)(pbVar1+0x6a)&param_1)==0) return 0;
    if((pbVar1[0x5c]!=param_2) || (iVar2=memcmp(((unsigned long)&g_bt_keys_pool_entry1_addr) /*=0x2000afa9*/,param_3,7,pbVar1[0x5c],param_4),iVar2!=0)) return 0;
    iVar2=0x5c;
  }
  return pbVar1+iVar2;
}
