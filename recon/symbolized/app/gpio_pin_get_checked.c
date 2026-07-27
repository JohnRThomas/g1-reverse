#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00017980 @ 0x00017980
 * public-name: gpio_pin_get_checked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_get_checked                     <= FUN_00017980 @ 0x00017980
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   g_gpio0_dev                              @ 0x00087b60
 *   rodata_99c53                             @ 0x00099c53
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_99de0                             @ 0x00099de0   [INLINED -- G6 literal batch]
 *   rodata_99e1e                             @ 0x00099e1e   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00017980 @ 0x17980  (parity: 300/300 trials, PROVEN) */

extern int assert_post_action(int, int);
typedef int (*ifn5)(unsigned int, void*, unsigned int, unsigned int, unsigned int);
int gpio_pin_get_checked(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  ifn5 pcVar2;
  unsigned int uVar3;
  volatile unsigned int *puVar4;
  unsigned int local_14;
  unsigned int uStack_10;

  uVar3 = 1u << (param_1 & 0xff);
  local_14 = param_2;
  uStack_10 = param_3;
  if ((uVar3 & *(volatile unsigned int *)(*(volatile unsigned int *)(((unsigned long)&g_gpio0_dev) /*=0x87b60*/ + 4))) == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U") /*=0x99de0*/, ((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x5f6);
    printk(((unsigned long)"\tUnsupported pin\n") /*=0x99e1e*/, 0, 0, 0);
    assert_post_action(((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x5f6);
  }
  puVar4 = *(volatile unsigned int **)(((unsigned long)&g_gpio0_dev) /*=0x87b60*/ + 0x10);
  pcVar2 = *(ifn5 *)(*(volatile unsigned int *)(((unsigned long)&g_gpio0_dev) /*=0x87b60*/ + 8) + 4);
  iVar1 = (*pcVar2)(((unsigned long)&g_gpio0_dev) /*=0x87b60*/, &local_14, param_3, (unsigned int)pcVar2, param_1);
  if (iVar1 == 0) {
    if (((local_14 ^ *puVar4) & uVar3) == 0) iVar1 = 0; else iVar1 = 1;
  }
  return iVar1;
}
