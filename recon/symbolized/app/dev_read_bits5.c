#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083ba6 @ 0x00083ba6
 * public-name: dev_read_bits5
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_read_bits5                           <= FUN_00083ba6 @ 0x00083ba6
 *   dev_ctrl_read1                           <= FUN_00083dba @ 0x00083dba
 */
/* Reconstructed FUN_00083ba6 @ 0x83ba6  (parity: 300/300 trials, PROVEN) */

extern int dev_ctrl_read1(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

int dev_read_bits5(int param_1, unsigned int *param_2)
{
  int iVar1;
  unsigned int uStack_c = (unsigned int)param_2;
  iVar1 = dev_ctrl_read1(*(volatile unsigned int *)((unsigned int)(*(volatile unsigned int *)((unsigned int)param_1 + 4)) + 4), 6, 0x1e, (unsigned int)&uStack_c + 3, (unsigned int)param_1);
  if (iVar1 >= 0) {
    iVar1 = 0;
    *param_2 = uStack_c >> 0x18;
  }
  return iVar1;
}
