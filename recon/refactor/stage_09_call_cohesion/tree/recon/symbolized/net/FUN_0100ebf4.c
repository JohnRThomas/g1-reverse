#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100ebf4 @ 0x0100ebf4
 * public-name: FUN_0100ebf4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_pending_work_list                  @ 0x21000ec8
 */
/* net-core FUN_0100ebf4 @ 0x100ebf4  (parity 300 trials PROVEN) */

void FUN_0100ebf4(void)
{
  unsigned int base = ((unsigned long)&g_net_pending_work_list) /*=0x21000ec8*/;

  *(volatile unsigned int *)(base + 4)  = 0;
  *(volatile unsigned short *)(base + 0x28) = 0;
  *(volatile unsigned int *)(base + 8)  = 0;
  *(volatile unsigned int *)(base + 0xc) = 0;
  *(volatile unsigned int *)(base + 0x10) = 0;
  *(volatile unsigned int *)(base + 0x14) = 0;
  *(volatile unsigned int *)(base + 0x18) = 0;
  *(volatile unsigned int *)(base + 0x1c) = 0;
  *(volatile unsigned int *)(base + 0x20) = 0;
  *(volatile unsigned int *)(base + 0x24) = 0;
  *(volatile unsigned char *)(base + 0x10) = 1;
  *(volatile unsigned int *)(base + 4) = base + 8;
  *(volatile unsigned int *)(base + 8) = base + 8;
}
