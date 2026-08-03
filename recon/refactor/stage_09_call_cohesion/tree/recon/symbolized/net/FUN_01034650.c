#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01034650 @ 0x01034650
 * public-name: FUN_01034650
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e6ad                           @ 0x0103e6ad
 */
/* net-core FUN_01034650 @ 0x1034650  (parity 300 trials PROVEN) */

extern void assert_print(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern unsigned int assert_post_action(unsigned int a, unsigned int b);

int FUN_01034650(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = param_1;
  if (param_1 > 7) {
    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e6ad) /*=0x103e6ad*/, 0x2aa, param_4, param_4);
    r0 = assert_post_action(((unsigned long)&rodata_103e6ad) /*=0x103e6ad*/, 0x2aa);
  }
  return (int)(r0 << 2) + 0x100;
}
