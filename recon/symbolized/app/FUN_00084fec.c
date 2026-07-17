#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084fec @ 0x00084fec
 * public-name: FUN_00084fec
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 */
/* Reconstructed FUN_00084fec @ 0x84fec  (parity: 300/300 trials, PROVEN) */

extern int strlen(void);
extern void FUN_00064b64(int,int,unsigned int,unsigned int);
void FUN_00084fec(int param_1,unsigned int param_2,unsigned int param_3)
{
  int iVar1;
  if (param_1 != 0) {
    iVar1 = strlen();
    FUN_00064b64(param_1,iVar1+1,param_2,param_3);
    return;
  }
  return;
}
