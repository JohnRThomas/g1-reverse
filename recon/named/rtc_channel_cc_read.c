/* readable reconstruction; identity: FUN_000635d8 @ 0x000635d8
 * public-name: rtc_channel_cc_read
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rtc_channel_cc_read                      <= FUN_000635d8 @ 0x000635d8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6659                             @ 0x000f6659
 *   rodata_f668a                             @ 0x000f668a   [INLINED -- G6 literal batch]
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_000635d8 @ 0x635d8  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(const char *, unsigned int);

unsigned int rtc_channel_cc_read(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 > 1) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"chan >= 0 && chan < (1 + 1)"), 0x000f6659, 0xc3, param_4);
    assert_post_action(0x000f6659, 0xc3);
  }
  return *(volatile unsigned int *)(0x50015000UL + (param_1 + 0x150) * 4);
}
