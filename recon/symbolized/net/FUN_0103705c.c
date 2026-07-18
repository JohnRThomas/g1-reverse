#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103705c @ 0x0103705c
 * public-name: FUN_0103705c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_0103705c @ 0x103705c  (parity 300 trials PROVEN) */
extern int FUN_0103610c(unsigned int);
extern void FUN_01036144(unsigned int);
extern void FUN_01036fcc(unsigned int);
extern int FUN_01036128(unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);

void FUN_0103705c(unsigned int param_1)
{
  int iVar3;
  unsigned int r1val;

  iVar3 = FUN_0103610c(0x21004b68);
  if (iVar3 == 0) {
    assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
    r1val = 0x72;
    goto L_shared;
  }

L_main:
  FUN_01036144(0x21004b68);
  FUN_01036fcc(param_1);
  iVar3 = FUN_01036128(0x21004b68);
  if (iVar3 != 0) {
    return;
  }
  assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
  r1val = 0xf0;

L_shared:
  assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, r1val);
  goto L_main;
}
