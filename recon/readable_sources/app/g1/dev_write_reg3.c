#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_reg_dev_ctx__param_0506                [param_0506; G1-original]
 * Raw function identity: 0x00083dc8.  See ../include/g1_recovered_layouts.h. */
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
