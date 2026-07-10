#include "g1_app_symbols.h"
/* named: gpio_pin_get_checked */
/* globals referenced:
//   0x00087b60  g_gpio0_dev                  
*/
/* Reconstructed gpio_pin_get_checked @ 0x17980  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void assert_post_action(unsigned int a, unsigned int b);
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
  if ((uVar3 & *(volatile unsigned int *)(*(volatile unsigned int *)(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/ + 4))) == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U" /*=0x99de0*/, "WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/, 0x5f6);
    printk("\tUnsupported pin\n" /*=0x99e1e*/, 0, 0, 0);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/, 0x5f6);
  }
  puVar4 = *(volatile unsigned int **)(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/ + 0x10);
  pcVar2 = *(ifn5 *)(*(volatile unsigned int *)(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/ + 8) + 4);
  iVar1 = (*pcVar2)(((uintptr_t)&g_gpio0_dev) /*=0x87b60*/, &local_14, param_3, (unsigned int)pcVar2, param_1);
  if (iVar1 == 0) {
    if (((local_14 ^ *puVar4) & uVar3) == 0) iVar1 = 0; else iVar1 = 1;
  }
  return iVar1;
}

