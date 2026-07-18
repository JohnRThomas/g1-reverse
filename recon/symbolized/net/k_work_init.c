#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036bec @ 0x01036bec
 * public-name: k_work_init
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   k_work_init                              <= FUN_01036bec @ 0x01036bec
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103eaed                           @ 0x0103eaed
 */
/* net-core FUN_01036bec @ 0x1036bec  (parity 300 trials PROVEN) */

extern void assert_print(unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
extern void FUN_0103b62e(void*, int, int, unsigned int, unsigned int);
void k_work_init(int *param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int uVar1;
  if (param_1 == 0) {
    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eaed) /*=0x103eaed*/, 0x89);
    uVar1 = 0x89;
  } else {
    if (param_2 != 0) {
      FUN_0103b62e(param_1,0,0x10,param_4,param_4);
      *(int*)((char*)param_1+4) = param_2;
      return;
    }
    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eaed) /*=0x103eaed*/, 0x8a);
    uVar1 = 0x8a;
  }
  assert_post_action(((unsigned long)&rodata_103eaed) /*=0x103eaed*/, uVar1);
}
