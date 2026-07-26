#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000730b4 @ 0x000730b4
 * public-name: k_work_queue_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_queue_init                        <= FUN_000730b4 @ 0x000730b4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f824d                             @ 0x000f824d
 */
/* Reconstructed FUN_000730b4 @ 0x730b4  (parity: 300/300 trials, PROVEN) */

extern int printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern int assert_post_action(unsigned int a, unsigned int b);
extern void memset_bytes(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void k_work_queue_init(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = (unsigned int)param_1;
  if (param_1 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f824d) /*=0xf824d*/, ((unsigned long)&rodata_f820f) /*=0xf820f*/, 0x2b9);
    r0 = assert_post_action(((unsigned long)&rodata_f820f) /*=0xf820f*/, 0x2b9);
  }
  memset_bytes(r0, 0, 0xf8, param_4, param_4);
}
