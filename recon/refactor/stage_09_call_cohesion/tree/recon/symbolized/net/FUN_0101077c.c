#include "g1_net_symbols.h"
#include "../../headers/g1_dedupe.h"
/* readable reconstruction; identity: FUN_0101077c @ 0x0101077c
 * public-name: FUN_0101077c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_lookup_table_desc                  @ 0x21000f14
 */
/* net-core FUN_0101077c @ 0x101077c  (parity 37 trials PROVEN) */

extern int sdc_assertion_fail(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e)
  __attribute__((noreturn));

int FUN_0101077c(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r2 = param_1 & 7;
  if (r2 != 0) {
    G1_NORETURN_CALL(sdc_assertion_fail(0x48, 99, r2, param_4, param_4));
  }
  if (param_1 != 0) {
    volatile unsigned char *p = (volatile unsigned char *)((unsigned long)&g_net_lookup_table_desc) /*=0x21000f14*/;
    p[8] = (unsigned char)param_2;
    *(volatile unsigned int *)(p + 4) = param_1;
    *p = (unsigned char)r2;
  }
  return param_2 << 3;
}
