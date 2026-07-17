#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103a38a @ 0x0103a38a
 * public-name: FUN_0103a38a
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103a38a @ 0x103a38a  (parity 300 trials PROVEN) */

extern void FUN_0102e974(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void FUN_0102eb8c(unsigned int a, unsigned int b, unsigned int c);

unsigned int FUN_0103a38a(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned int param_5)
{
  FUN_0102e974(param_1, param_3, param_4, param_4, param_4);
  FUN_0102eb8c(param_1, param_2, param_5);
  return param_1;
}
