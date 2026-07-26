#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002ea78 @ 0x0002ea78
 * public-name: device_reg3_init_config
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   device_reg3_init_config                  <= FUN_0002ea78 @ 0x0002ea78
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 * address symbols (name @ address):
 *   rodata_a3e1a                             @ 0x000a3e1a   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0002ea78 @ 0x2ea78  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern void log_message(unsigned int a0);

unsigned int device_reg3_init_config(void)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int base = *(volatile unsigned int*)((unsigned long)&rodata_87ce0 + 4) /*=0x87ce0*/;
  iVar1 = dev_write_reg3(*(volatile unsigned int*)(base + 0x1c), 3, 0xc, 8);
  if (iVar1 < 0) {
    log_message(((unsigned long)"Could not change termination voltage to 4.2V\n") /*=0xa3e1a*/);
    uVar2 = 0xffffffff;
  } else {
    uVar2 = 0;
  }
  return uVar2;
}
