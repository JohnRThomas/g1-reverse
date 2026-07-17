#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083bca @ 0x00083bca
 * public-name: dev_update_bits5
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_write_bits5_diff                     <= FUN_00083b62 @ 0x00083b62
 *   dev_read_bits5                           <= FUN_00083ba6 @ 0x00083ba6
 *   dev_update_bits5                         <= FUN_00083bca @ 0x00083bca
 */
/* Reconstructed FUN_00083bca @ 0x83bca  (parity: 300/300 trials, PROVEN) */

extern int dev_read_bits5(unsigned int a, unsigned int *b, unsigned int c, unsigned int d, unsigned int e);
extern void dev_write_bits5_diff(unsigned int a, unsigned int b, unsigned int c);

void dev_update_bits5(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int local_14 = param_2;
  int iVar1 = dev_read_bits5(param_1, &local_14, param_3, param_4, param_1);
  if (iVar1 >= 0) {
    dev_write_bits5_diff(param_1, param_2, ~local_14);
  }
}
