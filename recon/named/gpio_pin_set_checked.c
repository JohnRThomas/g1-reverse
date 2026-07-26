/* readable reconstruction; identity: FUN_00017768 @ 0x00017768
 * public-name: gpio_pin_set_checked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_set_checked                     <= FUN_00017768 @ 0x00017768
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99c53                             @ 0x00099c53
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_99de0                             @ 0x00099de0   [INLINED -- G6 literal batch]
 *   rodata_99e1e                             @ 0x00099e1e   [INLINED -- G6 literal batch]
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_00017768 @ 0x17768  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a, unsigned int b);
typedef void (*jfn847)(void);
void gpio_pin_set_checked(int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  jfn847 UNRECOVERED_JUMPTABLE;

  uVar1 = 1u << (param_2 & 0xff);
  if ((uVar1 & **(volatile unsigned int **)(param_1 + 4)) == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U"), 0x99c53, 0x64f);
    printk(((unsigned long)"\tUnsupported pin\n"), 0, 0, 0);
    assert_post_action(0x99c53, 0x64f);
  }
  if ((uVar1 & **(volatile unsigned int **)(param_1 + 0x10)) != 0) {
    param_3 = param_3 ^ 1;
  }
  if (param_3 == 0) {
    UNRECOVERED_JUMPTABLE = *(jfn847 *)(*(int *)(param_1 + 8) + 0x10);
  } else {
    UNRECOVERED_JUMPTABLE = *(jfn847 *)(*(int *)(param_1 + 8) + 0xc);
  }
  (*UNRECOVERED_JUMPTABLE)();
}
