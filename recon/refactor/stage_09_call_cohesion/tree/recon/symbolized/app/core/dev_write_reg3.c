#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083dc8 @ 0x00083dc8
 * public-name: dev_write_reg3
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_ctrl_write1                          <= FUN_00083d60 @ 0x00083d60
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 */
/* Reconstructed FUN_00083dc8 @ 0x83dc8  (parity: 300/300 trials, PROVEN) */

extern void dev_ctrl_write1(unsigned int, void *, unsigned int, unsigned int, unsigned int);

void dev_write_reg3(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char request[3];

  request[0] = (unsigned char)param_2;
  request[1] = (unsigned char)param_3;
  request[2] = (unsigned char)param_4;
  dev_ctrl_write1(*(unsigned int *)((unsigned char*)param_1 + 4), request, 3,
                param_4, (unsigned int)param_1);
  return;
}
