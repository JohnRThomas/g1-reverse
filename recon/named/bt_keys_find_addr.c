/* readable reconstruction; identity: FUN_0005e938 @ 0x0005e938
 * public-name: bt_keys_find_addr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_keys_find_addr                        <= FUN_0005e938 @ 0x0005e938
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f52ac                             @ 0x000f52ac   [INLINED -- G6 literal batch]
 *   bt_keys_pool                             @ 0x2000af4c
 *   g_bt_keys_pool_entry1_addr               @ 0x2000afa9
 */
/* Reconstructed FUN_0005e938 @ 0x5e938  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int assert_post_action(int, int);
extern int memcmp(const void*, const void*, unsigned long);
int bt_keys_find_addr(unsigned char param_1, int param_2) {
  unsigned char *pbVar1 = (unsigned char*)0x2000af4cUL;
  int iVar2;
  if(param_2==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"addr != ((void *)0)"), 0x000f5268, 0x11a);
    assert_post_action(0x000f5268, 0x11a);
    return (unsigned char *)0x5c;
  }
  if((uint32_t)*(volatile uint8_t*)pbVar1 != param_1 ||
     memcmp((int)(pbVar1+1), param_2, 7) != 0){
    if((uint32_t)*(volatile uint8_t*)(pbVar1+0x5c) != param_1 ||
       memcmp(0x2000afa9, param_2, 7) != 0){
      return (unsigned char*)0;
    }
    iVar2 = 1;
  } else {
    iVar2 = 0;
  }
  return pbVar1 + iVar2*0x5c;
}
