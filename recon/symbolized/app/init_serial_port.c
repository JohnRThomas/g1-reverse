#include "g1_app_symbols.h"
/* named: init_serial_port */
/* Reconstructed init_serial_port @ 0x332dc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void*);
extern int z_device_is_ready(void*);
extern int uart_read_start(void*);
extern void assert_post_action(void*, int);
extern void printk(void*, void*, void*, int, unsigned int);

unsigned int init_serial_port(void)
{
  volatile unsigned char *pcVar1 = (volatile unsigned char*)((uintptr_t)&g_serial_port_ready) /*=0x2001a127*/;
  int iVar2;

  if (*pcVar1 == 0) {
    iVar2 = z_device_is_ready((void*)((uintptr_t)&tbl_87b30) /*=0x87bc0*/);
    if (iVar2 == 0) {
      printk((void*)"ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, (void*)"device_is_ready(lpuart)" /*=0xa78b9*/, (void*)"../src/production_test/serial_thread.c" /*=0xa7892*/, 0x2e, 0);
      printk((void*)"\tLPUART device not ready\n" /*=0xa78d1*/, 0, 0, 0, 0);
      assert_post_action((void*)"../src/production_test/serial_thread.c" /*=0xa7892*/, 0x2e);
    }
    iVar2 = uart_read_start((void*)((uintptr_t)&tbl_87b30) /*=0x87bc0*/);
    if (iVar2 != 0) {
      *pcVar1 = 0;
      DEBUG_PRINT((void*)"init_serial_port is failed\n" /*=0xa78eb*/);
      return 0xffffffff;
    }
    *pcVar1 = 1;
  }
  return 0;
}

