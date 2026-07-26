/* readable reconstruction; identity: FUN_000635a4 @ 0x000635a4
 * public-name: rtc_timer_cc_reg_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rtc_timer_cc_reg_get                     <= FUN_000635a4 @ 0x000635a4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6659                             @ 0x000f6659
 *   rodata_f668a                             @ 0x000f668a   [INLINED -- G6 literal batch]
 */
#include "../headers/g1_nrf_regs.h"
/* Reconstructed FUN_000635a4 @ 0x635a4  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a0, unsigned int a1);
extern void printk(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

unsigned int rtc_timer_cc_reg_get(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  if (param_1 > 1) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"chan >= 0 && chan < (1 + 1)"), 0x000f6659, 0x8d, param_4);
    assert_post_action(0x000f6659, 0x8d);
  }
  uVar1 = (G1_NRF_RTC1_S_BASE + 0x44);
  if (param_1 == 0) {
    uVar1 = 0;
  }
  return uVar1;
}
