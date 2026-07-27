#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000332dc @ 0x000332dc
 * public-name: init_serial_port
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   init_serial_port                         <= FUN_000332dc @ 0x000332dc
 *   uart_read_start                          <= FUN_000336a0 @ 0x000336a0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87bc0                             @ 0x00087bc0
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_a7892                             @ 0x000a7892   [INLINED -- G6 literal batch]
 *   rodata_a78b9                             @ 0x000a78b9   [INLINED -- G6 literal batch]
 *   rodata_a78d1                             @ 0x000a78d1   [INLINED -- G6 literal batch]
 *   rodata_a78eb                             @ 0x000a78eb   [INLINED -- G6 literal batch]
 *   g_serial_port_ready                      @ 0x2001a127
 */
/* Reconstructed FUN_000332dc @ 0x332dc  (parity: 300/300 trials, PROVEN) */

extern _Bool z_device_is_ready(const struct device *);
extern int uart_read_start(void*);
extern void assert_post_action(const char *, unsigned int);

unsigned int init_serial_port(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)((unsigned long)&g_serial_port_ready) /*=0x2001a127*/;
  int iVar2;

  if (*pcVar1 == 0) {
    iVar2 = z_device_is_ready((void*)((unsigned long)&rodata_87bc0) /*=0x87bc0*/);
    if (iVar2 == 0) {
      printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, (void*)((unsigned long)"device_is_ready(lpuart)") /*=0xa78b9*/, (void*)((unsigned long)"../src/production_test/serial_thread.c") /*=0xa7892*/, 0x2e, 0);
      printk((unsigned long)((unsigned long)"\tLPUART device not ready\n") /*=0xa78d1*/, 0, 0, 0, 0);
      assert_post_action((void*)((unsigned long)"../src/production_test/serial_thread.c") /*=0xa7892*/, 0x2e);
    }
    iVar2 = uart_read_start((void*)((unsigned long)&rodata_87bc0) /*=0x87bc0*/);
    if (iVar2 != 0) {
      *pcVar1 = 0;
      log_message((unsigned long)((unsigned long)"init_serial_port is failed\n") /*=0xa78eb*/);
      return 0xffffffff;
    }
    *pcVar1 = 1;
  }
  return 0;
}
