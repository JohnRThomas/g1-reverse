#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102a448 @ 0x0102a448
 * public-name: FUN_0102a448
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   __memcpy_chk                             <= FUN_0103b53a @ 0x0103b53a
 * address symbols (name @ address):
 *   g_net_ctrl_report_len                    @ 0x210045e4
 */
/* net-core FUN_0102a448 @ 0x102a448  (parity 300 trials PROVEN) */

extern void __memcpy_chk(unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int FUN_0102a448(unsigned int param_1, unsigned int param_2) {
  __memcpy_chk(0x21004b9f, param_1, param_2, 0xfc);
  *(volatile unsigned int *)((unsigned long)&g_net_ctrl_report_len) /*=0x210045e4*/ = param_2;
  return 0;
}
