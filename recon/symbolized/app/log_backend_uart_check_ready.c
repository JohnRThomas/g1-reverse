#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0004df88 @ 0x0004df88
 * public-name: log_backend_uart_check_ready
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_backend_uart_check_ready             <= FUN_0004df88 @ 0x0004df88
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87bc0                             @ 0x00087bc0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0f71                             @ 0x000f0f71   [INLINED -- G6 literal batch]
 *   rodata_f0faf                             @ 0x000f0faf   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0004df88 @ 0x4df88  (parity: 300/300 trials, PROVEN) */

extern _Bool z_device_is_ready(const struct device *);
extern void assert_post_action(const char *, unsigned int);
void log_backend_uart_check_ready(void)
{
  int iVar1;
  iVar1 = z_device_is_ready(((unsigned long)&rodata_87bc0) /*=0x87bc0*/);
  if (iVar1 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"device_is_ready(uart_dev)") /*=0xf0faf*/,((unsigned long)"WEST_TOPDIR/zephyr/subsys/logging/backends/log_backend_uart.c") /*=0xf0f71*/,0x7f,0);
    assert_post_action(((unsigned long)"WEST_TOPDIR/zephyr/subsys/logging/backends/log_backend_uart.c") /*=0xf0f71*/,0x7f);
  }
  return;
}
