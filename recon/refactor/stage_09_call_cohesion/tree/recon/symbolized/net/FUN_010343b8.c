#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010343b8 @ 0x010343b8
 * public-name: FUN_010343b8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e628                           @ 0x0103e628
 */
/* net-core FUN_010343b8 @ 0x10343b8  (parity 300 trials PROVEN) */

extern void assert_print(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void assert_post_action(unsigned int a, unsigned int b);

void FUN_010343b8(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = param_1;
  unsigned int r1 = param_2;
  if (param_2 == 0) {
    r1 = ((unsigned long)&rodata_103e628) /*=0x103e628*/;
    r0 = ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/;
    assert_print(r0, r1, 0x44, param_4, param_4);
    r1 = 0x44;
    r0 = ((unsigned long)&rodata_103e628) /*=0x103e628*/;
    assert_post_action(r0, r1);
  }
  *(unsigned int *)(r1 + 0x80) = (r0 | 0x80000000);
  return;
}
