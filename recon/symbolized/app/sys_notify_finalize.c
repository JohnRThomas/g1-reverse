#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0004bb0c @ 0x0004bb0c
 * public-name: sys_notify_finalize
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sys_notify_finalize                      <= FUN_0004bb0c @ 0x0004bb0c
 *   poll_signal_event_locked                 <= FUN_000757b0 @ 0x000757b0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0959                             @ 0x000f0959
 *   rodata_f7a30                             @ 0x000f7a30
 */
/* Reconstructed FUN_0004bb0c @ 0x4bb0c  (parity: 300/300 trials, PROVEN) */

extern void poll_signal_event_locked(unsigned int, unsigned int);
extern void assert_post_action(unsigned int a, unsigned int b);
int sys_notify_finalize(int *param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int uVar1;
  int r0;
  uVar1 = param_1[1] & 3;
  param_1[2] = param_2;
  if (uVar1 == 2) {
    r0 = param_1[0];
    param_1[1] = 0;
    if (r0 != 0) {
      poll_signal_event_locked((unsigned int)r0, (unsigned int)param_2);
    }
    return 0;
  } else if (uVar1 == 3) {
    r0 = param_1[0];
    param_1[1] = 0;
    return r0;
  } else if (uVar1 == 1) {
    param_1[1] = 0;
    return 0;
  } else {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f7a30) /*=0xf7a30*/, ((unsigned long)&rodata_f0959) /*=0xf0959*/, 0x45, param_4);
    assert_post_action(((unsigned long)&rodata_f0959) /*=0xf0959*/, 0x45);
    poll_signal_event_locked(((unsigned long)&rodata_f0959) /*=0xf0959*/, 0x45);
    return 0;
  }
}
