#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051134 @ 0x00051134
 * public-name: __retarget_lock_release_recursive
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __retarget_lock_release_recursive        <= FUN_00051134 @ 0x00051134
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f22d5                             @ 0x000f22d5
 *   rodata_f23d4                             @ 0x000f23d4
 */
/* Reconstructed FUN_00051134 @ 0x51134  (parity: 300/300 trials, PROVEN) */

extern void printk(int a, int b, int c, int d, int e);
extern void assert_post_action(int a, int b);
extern void k_mutex_unlock(void);
void __retarget_lock_release_recursive(int param_1, int param_2, int param_3, int param_4)
{
  if (param_1 == 0) {
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f23d4) /*=0xf23d4*/, ((unsigned long)&rodata_f22d5) /*=0xf22d5*/, 0x1c2, param_4);
    assert_post_action(((unsigned long)&rodata_f22d5) /*=0xf22d5*/, 0x1c2);
  }
  k_mutex_unlock();
}
