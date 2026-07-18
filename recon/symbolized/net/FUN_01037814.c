#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01037814 @ 0x01037814
 * public-name: FUN_01037814
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103eb0e                           @ 0x0103eb0e
 */
/* net-core FUN_01037814 @ 0x1037814  (parity 300 trials PROVEN) */

extern void assert_print(unsigned int, unsigned int, unsigned int);
extern unsigned int assert_post_action(unsigned int, unsigned int);
extern void FUN_0103735c(unsigned int, int*);
void FUN_01037814(int *param_1)
{
  unsigned int r0 = *(unsigned int*)((char*)param_1+8);
  if (r0 == 0) {
    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x2d2);
    r0 = assert_post_action(((unsigned long)&rodata_103eb0e) /*=0x103eb0e*/, 0x2d2);
  }
  FUN_0103735c(r0, param_1);
  *(unsigned char*)((char*)param_1+0xd) &= 0xfd;
  *(unsigned int*)((char*)param_1+8) = 0;
}
