#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007fae4 @ 0x0007fae4
 * public-name: FUN_0007fae4
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_0007fae4 @ 0x7fae4  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007f97c(unsigned int a,int b,void *c,int d);
void FUN_0007fae4(unsigned int param_1, unsigned short *param_2)
{
  unsigned int local_10 = param_1;
  unsigned int local_c = (unsigned int)param_2;
  FUN_0007f97c(param_1, 0x28, &local_10, 6);
  *(volatile unsigned short *)&param_2[0] = (unsigned short)(local_10 & 0xffff);
  *(volatile unsigned short *)&param_2[1] = (unsigned short)((local_10 >> 16) & 0xffff);
  *(volatile unsigned short *)&param_2[2] = (unsigned short)(local_c & 0xffff);
}
