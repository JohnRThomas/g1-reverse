#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103a32a @ 0x0103a32a
 * public-name: FUN_0103a32a
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103a32a @ 0x103a32a  (parity 214 trials PROVEN) */

typedef int (*fnptr)(int,int,unsigned int);

void FUN_0103a32a(fnptr param_1, int param_2, int param_3, unsigned int param_4)
{
  int iVar1;
  do {
    iVar1 = param_1(param_2, param_3, param_4);
    param_3 = param_3 - iVar1;
    param_2 = param_2 + iVar1;
  } while (param_3 != 0);
}
