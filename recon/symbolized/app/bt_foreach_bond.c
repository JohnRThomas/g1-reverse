#include "g1_app_symbols.h"
/* named: bt_foreach_bond */
/* globals referenced:
//   0x2000af4c  bt_keys_pool                 
*/
/* Reconstructed bt_foreach_bond @ 0x5e6d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t);
void bt_foreach_bond(uint32_t param_1, void* param_2, uint32_t param_3){
  volatile uint32_t local_20; volatile uint8_t local_1c[8];
  (void)local_1c;
  if(param_2==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"func != ((void *)0)" /*=0xf52c0*/,"WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/,0xa0);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/keys.c" /*=0xf5268*/,0xa0);
  }
  if(*(volatile int16_t*)(((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/+0xe)!=0 && *(volatile uint8_t*)((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/==param_1){
    local_20=*(volatile uint32_t*)(((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/+1);
    ((void(*)(void*,uint32_t))param_2)((void*)&local_20,param_3);
  }
  if(*(volatile int16_t*)(((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/+0x6a)!=0 && *(volatile uint8_t*)(((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/+0x5c)==param_1){
    local_20=*(volatile uint32_t*)(((uintptr_t)&bt_keys_pool) /*=0x2000af4c*/+0x5d);
    ((void(*)(void*,uint32_t))param_2)((void*)&local_20,param_3);
  }
}

