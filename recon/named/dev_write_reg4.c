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
