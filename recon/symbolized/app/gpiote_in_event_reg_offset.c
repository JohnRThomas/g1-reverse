#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000655ec @ 0x000655ec
 * public-name: gpiote_in_event_reg_offset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpiote_in_event_reg_offset               <= FUN_000655ec @ 0x000655ec
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6b3e                             @ 0x000f6b3e
 *   rodata_f6b73                             @ 0x000f6b73   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_000655ec @ 0x655ec  (parity: 300/300 trials, PROVEN) */

extern int assert_post_action(unsigned int a, unsigned int b);

int gpiote_in_event_reg_offset(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = param_1;
  if (param_1 > 7) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"index < 8") /*=0xf6b73*/, ((unsigned long)&rodata_f6b3e) /*=0xf6b3e*/, 0x2aa, param_4);
    r0 = assert_post_action(((unsigned long)&rodata_f6b3e) /*=0xf6b3e*/, 0x2aa);
  }
  return r0 * 4 + 0x100;
}
