#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_reg_dev_ctx__param_0506                [param_0506; G1-original]
 *   local_c          => struct g1_layout_dev_write_reg4_locals__stack_1552      [stack_1552; G1-original]
 * Raw function identity: 0x00083de6.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00083de6 @ 0x00083de6
 * public-name: dev_write_reg4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_ctrl_write1                          <= FUN_00083d60 @ 0x00083d60
 *   dev_write_reg4                           <= FUN_00083de6 @ 0x00083de6
 */
/* Reconstructed FUN_00083de6 @ 0x83de6  (parity: 300/300 trials, PROVEN) */

extern void dev_ctrl_write1(int a, void *b, unsigned int c, unsigned int d, void *e);

void dev_write_reg4(int *param_1, unsigned char param_2, unsigned int param_3, unsigned char param_4, unsigned char param_5)
{
    unsigned char local_c[4];
    local_c[0] = param_2;
    local_c[1] = (unsigned char)param_3;
    local_c[2] = param_4;
    local_c[3] = param_5;
    dev_ctrl_write1(*(volatile int*)((char*)param_1 + 4), local_c, 4, param_5, param_1);
}
