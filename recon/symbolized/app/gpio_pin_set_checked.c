#include "g1_app_symbols.h"
/* named: gpio_pin_set_checked */
/* Reconstructed gpio_pin_set_checked @ 0x17768  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void assert_post_action(unsigned int a, unsigned int b);
typedef void (*jfn847)(void);
void gpio_pin_set_checked(int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  jfn847 UNRECOVERED_JUMPTABLE;

  uVar1 = 1u << (param_2 & 0xff);
  if ((uVar1 & **(volatile unsigned int **)(param_1 + 4)) == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U" /*=0x99de0*/, "WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/, 0x64f);
    printk("\tUnsupported pin\n" /*=0x99e1e*/, 0, 0, 0);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/, 0x64f);
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

