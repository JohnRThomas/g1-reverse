#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005e6d4 @ 0x0005e6d4
 * public-name: bt_foreach_bond
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_foreach_bond                          <= FUN_0005e6d4 @ 0x0005e6d4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f52c0                             @ 0x000f52c0
 *   bt_keys_pool                             @ 0x2000af4c
 */
/* Reconstructed FUN_0005e6d4 @ 0x5e6d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern void assert_post_action(uint32_t,uint32_t);
void bt_foreach_bond(uint32_t param_1, void* param_2, uint32_t param_3){
  volatile uint32_t local_20; volatile uint8_t local_1c[8];
  (void)local_1c;
  if(param_2==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f52c0) /*=0xf52c0*/,((unsigned long)&rodata_f5268) /*=0xf5268*/,0xa0);
    assert_post_action(((unsigned long)&rodata_f5268) /*=0xf5268*/,0xa0);
  }
  if(*(volatile int16_t*)(((unsigned long)&bt_keys_pool) /*=0x2000af4c*/+0xe)!=0 && *(volatile uint8_t*)((unsigned long)&bt_keys_pool) /*=0x2000af4c*/==param_1){
    local_20=*(volatile uint32_t*)(((unsigned long)&bt_keys_pool) /*=0x2000af4c*/+1);
    ((void(*)(void*,uint32_t))param_2)((void*)&local_20,param_3);
  }
  if(*(volatile int16_t*)(((unsigned long)&bt_keys_pool) /*=0x2000af4c*/+0x6a)!=0 && *(volatile uint8_t*)(((unsigned long)&bt_keys_pool) /*=0x2000af4c*/+0x5c)==param_1){
    local_20=*(volatile uint32_t*)(((unsigned long)&bt_keys_pool) /*=0x2000af4c*/+0x5d);
    ((void(*)(void*,uint32_t))param_2)((void*)&local_20,param_3);
  }
}
