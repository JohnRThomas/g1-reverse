#include "g1_app_symbols.h"
/* named: bt_keys_find */
/* globals referenced:
//   0x2000af4c  bt_keys_pool                 
*/
/* Reconstructed bt_keys_find @ 0x5e7c8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,unsigned int,unsigned int,int);
extern void assert_post_action(unsigned int,int);
extern int memcmp(unsigned int,int,int,unsigned int,unsigned int);
unsigned char* bt_keys_find(unsigned short param_1,unsigned int param_2,int param_3,unsigned int param_4){
  unsigned char* pbVar1=(unsigned char*)((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/;
  int iVar2;
  if(param_3==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"addr != ((void *)0)" /*=0xf52ac*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/,0xc0);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/,0xc0);
  }
  if(((*(volatile unsigned short*)(((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/+0xe)&param_1)==0) ||
     (*(volatile unsigned char*)((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/!=param_2) ||
     (iVar2=memcmp(((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/+1,param_3,7,*(volatile unsigned char*)((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/,param_4),iVar2!=0)){
    if((*(volatile unsigned short*)(pbVar1+0x6a)&param_1)==0) return 0;
    if((pbVar1[0x5c]!=param_2) || (iVar2=memcmp(((uintptr_t)&g_bt_keys_pool_entry1_addr) /*=0x2000afa9*/,param_3,7,pbVar1[0x5c],param_4),iVar2!=0)) return 0;
    iVar2=0x5c;
  }
  return pbVar1+iVar2;
}

