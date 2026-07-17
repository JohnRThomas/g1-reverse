#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102acb4 @ 0x0102acb4
 * public-name: FUN_0102acb4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   printk                                   <= FUN_01039722 @ 0x01039722
 * address symbols (name @ address):
 *   rodata_102b351                           @ 0x0102b351
 *   rodata_102b3ad                           @ 0x0102b3ad
 *   rodata_103cf0b                           @ 0x0103cf0b
 *   g_zephyr_log_level                       @ 0x21000580
 *   g_net_0x21004604_flag                    @ 0x21004604
 */
/* net-core FUN_0102acb4 @ 0x102acb4  (parity 300 trials PROVEN) */

extern void printk(unsigned int a);

unsigned int FUN_0102acb4(unsigned int param_1)
{
  *(unsigned int *)(param_1 + 0x60) = ((unsigned long)&rodata_102b3ad) /*=0x102b3ad*/;
  *(unsigned int *)(param_1 + 0x64) = ((unsigned long)&rodata_102b351) /*=0x102b351*/;
  *(volatile unsigned int *)((unsigned long)&g_net_0x21004604_flag) /*=0x21004604*/ = param_1;
  if (*(volatile int *)((unsigned long)&g_zephyr_log_level) /*=0x21000580*/ > 1) {
    printk(((unsigned long)&rodata_103cf0b) /*=0x103cf0b*/);
  }
  return 0;
}
