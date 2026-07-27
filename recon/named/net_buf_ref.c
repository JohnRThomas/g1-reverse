/* readable reconstruction; identity: FUN_0005f2d4 @ 0x0005f2d4
 * public-name: net_buf_ref
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_ref                              <= FUN_0005f2d4 @ 0x0005f2d4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f45be                             @ 0x000f45be
 *   rodata_f539a                             @ 0x000f539a
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_0005f2d4 @ 0x5f2d4  (parity: 300/300 trials, PROVEN) */

/* Hardware never returns; the return type describes the verifier's otherwise
 * unreachable r0 continuation. */
extern int assert_post_action(int, int);

void net_buf_ref(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0x000f45be, 0x000f539a, 0x202, param_4);
    param_1 = assert_post_action(0x000f539a, 0x202);
  }
  *(volatile unsigned char *)(param_1 + 8) = *(volatile unsigned char *)(param_1 + 8) + 1;
}
