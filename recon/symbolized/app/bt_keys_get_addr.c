#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005e6a8 @ 0x0005e6a8
 * public-name: bt_keys_get_addr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_keys_pool_find_or_alloc               <= FUN_0005e614 @ 0x0005e614
 *   bt_keys_get_addr                         <= FUN_0005e6a8 @ 0x0005e6a8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f52ac                             @ 0x000f52ac   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0005e6a8 @ 0x5e6a8  (parity: 300/300 trials, PROVEN) */

extern void bt_keys_pool_find_or_alloc(void);
extern void assert_post_action(unsigned int,unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void bt_keys_get_addr(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  if (param_2 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"addr != ((void *)0)") /*=0xf52ac*/,((unsigned long)&rodata_f5268) /*=0xf5268*/,0x59,param_4);
    assert_post_action(((unsigned long)&rodata_f5268) /*=0xf5268*/,0x59);
  }
  bt_keys_pool_find_or_alloc();
  return;
}
