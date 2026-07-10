#include "g1_app_symbols.h"
/* named: gpio_pin_get_raw_checked */
/* Reconstructed gpio_pin_get_raw_checked @ 0x177c4  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
typedef int (*fnptr)(int, unsigned int*, unsigned int, void*, int);

int gpio_pin_get_raw_checked(char *param_1, unsigned int param_2)
{
  unsigned int uVar3 = 1u << (param_2 & 0xff);
  unsigned int local_c = param_2;
  if ((uVar3 & **(unsigned int**)(param_1+4)) == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U" /*=0x99de0*/, "WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/, 0x5d1);
    printk("\tUnsupported pin\n" /*=0x99e1e*/, 0, 0, 0);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h" /*=0x99c53*/, 0x5d1);
  }
  fnptr pcVar2 = *(fnptr*)(*(int*)(param_1+8)+4);
  int iVar1 = pcVar2((int)param_1, &local_c, **(unsigned int**)(param_1+4), (void*)pcVar2, (int)param_1);
  if (iVar1==0) {
    iVar1 = (uVar3 & local_c)!=0 ? 1:0;
  }
  return iVar1;
}

