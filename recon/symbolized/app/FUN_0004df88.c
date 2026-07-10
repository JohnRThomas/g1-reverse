#include "g1_app_symbols.h"
/* named: FUN_0004df88 */
/* Reconstructed FUN_0004df88 @ 0x4df88  (parity: 300/300 trials, PROVEN) */

extern int z_device_is_ready(unsigned int);
extern void printk(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void assert_post_action(unsigned int,unsigned int);
void FUN_0004df88(void)
{
  int iVar1;
  iVar1 = z_device_is_ready(((uintptr_t)&tbl_87b30) /*=0x87bc0*/);
  if (iVar1 == 0) {
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"device_is_ready(uart_dev)" /*=0xf0faf*/,"WEST_TOPDIR/zephyr/subsys/logging/backends/log_backend_uart.c" /*=0xf0f71*/,0x7f,0);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/logging/backends/log_backend_uart.c" /*=0xf0f71*/,0x7f);
  }
  return;
}

