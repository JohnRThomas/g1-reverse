#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01032988 @ 0x01032988
 * public-name: FUN_01032988
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103cafc                           @ 0x0103cafc
 *   g_net_log_msg_ctx                        @ 0x21000698
 */
/* net-core FUN_01032988 @ 0x1032988  (parity 300 trials PROVEN) */

extern int FUN_010218cc(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void FUN_01033c74(void);

void FUN_01032988(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  volatile unsigned int * const *pp = (volatile unsigned int * const *)((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/;

  iVar1 = FUN_010218cc(((unsigned long)&rodata_103cafc) /*=0x103cafc*/, G1N_2100065c, param_3, param_4, param_4);
  if (iVar1 == 0) {
    FUN_01033c74();
    *(volatile unsigned int *)((*pp) + (0x200/4)) = 0x40004;
  }
  return;
}
