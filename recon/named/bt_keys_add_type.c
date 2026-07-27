/* readable reconstruction; identity: FUN_0005e9a0 @ 0x0005e9a0
 * public-name: bt_keys_add_type
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_keys_add_type                         <= FUN_0005e9a0 @ 0x0005e9a0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f5298                             @ 0x000f5298   [INLINED -- G6 literal batch]
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_0005e9a0 @ 0x5e9a0  (parity: 300/300 trials, PROVEN) */

extern int assert_post_action(int, int);

void bt_keys_add_type(int param_1, unsigned short param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 == 0) {
    unsigned long long r;
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"keys != ((void *)0)"), 0x000f5268, 0x12a);
    r = assert_post_action(0x000f5268, 0x12a);
    param_1 = (int)r;
    param_2 = (unsigned short)(r >> 32);
  }
  *(volatile unsigned short *)(param_1 + 0xe) = param_2 | *(volatile unsigned short *)(param_1 + 0xe);
}
