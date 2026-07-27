#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004f564 @ 0x0004f564
 * public-name: app_event_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   app_event_alloc                          <= FUN_0004f564 @ 0x0004f564
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   malloc_impl                              <= FUN_000868c2 @ 0x000868c2
 */
/* Reconstructed FUN_0004f564 @ 0x4f564  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(void);
extern void printk(unsigned long, ...);
extern void assert_post_action(unsigned long, unsigned long);
extern int malloc_impl(void);

void app_event_alloc(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  iVar1 = malloc_impl();
  if (iVar1 == 0) {
    z_log_msg_runtime_create();
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"0"), ((unsigned long)"WEST_TOPDIR/nrf/subsys/app_event_manager/app_event_manager.c"), 123);
    assert_post_action(((unsigned long)"WEST_TOPDIR/nrf/subsys/app_event_manager/app_event_manager.c"), 123);
  }
}
