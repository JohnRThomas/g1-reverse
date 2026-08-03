#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00063570 @ 0x00063570
 * public-name: rtc_cc_reg_addr_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rtc_cc_reg_addr_get                      <= FUN_00063570 @ 0x00063570
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6659                             @ 0x000f6659
 *   rodata_f668a                             @ 0x000f668a   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00063570 @ 0x63570  (parity: 300/300 trials, PROVEN) */

extern int assert_post_action(int, int);
unsigned int rtc_cc_reg_addr_get(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int idx = param_1;
  if (1 < param_1) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"chan >= 0 && chan < (1 + 1)") /*=0xf668a*/, ((unsigned long)&rodata_f6659) /*=0xf6659*/, 0x86, param_4);
    idx = assert_post_action(((unsigned long)&rodata_f6659) /*=0xf6659*/, 0x86);
  }
  return 0x50015140UL + idx * 4;
}
