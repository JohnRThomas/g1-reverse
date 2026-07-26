#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_net_buf__param_0276                    [param_0276; library]
 * Raw function identity: 0x0005ee6c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005ee6c @ 0x0005ee6c
 * public-name: net_buf_reset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_reset                            <= FUN_0005ee6c @ 0x0005ee6c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f539a                             @ 0x000f539a
 *   rodata_f53be                             @ 0x000f53be   [INLINED -- G6 literal batch]
 *   rodata_f53cf                             @ 0x000f53cf   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0005ee6c @ 0x5ee6c  (parity: 300/300 trials, PROVEN) */

extern int assert_post_action(unsigned int, unsigned int);

void net_buf_reset(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  int fakeParam1;
  if (*(char *)(param_1 + 9) == 0) {
    if (*(int *)(param_1 + 4) == 0) {
      *(unsigned short *)(param_1 + 0x10) = 0;
      *(unsigned int *)(param_1 + 0xc) = *(unsigned int *)(param_1 + 0x14);
      return;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"buf->frags == ((void *)0)") /*=0xf53cf*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x5b, param_4);
    uVar1 = 0x5b;
  } else {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"buf->flags == 0U") /*=0xf53be*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x5a, param_4);
    uVar1 = 0x5a;
  }
  fakeParam1 = assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/, uVar1);
  while (1) {
    if (*(int *)(fakeParam1 + 4) == 0) {
      *(unsigned short *)(fakeParam1 + 0x10) = 0;
      *(unsigned int *)(fakeParam1 + 0xc) = *(unsigned int *)(fakeParam1 + 0x14);
      return;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"buf->frags == ((void *)0)") /*=0xf53cf*/, ((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x5b, param_4);
    fakeParam1 = assert_post_action(((unsigned long)&rodata_f539a) /*=0xf539a*/, 0x5b);
  }
}
