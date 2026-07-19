#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083d80 @ 0x00083d80
 * public-name: dev_ctrl_write2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_ctrl_write2                          <= FUN_00083d80 @ 0x00083d80
 */
/* Reconstructed FUN_00083d80 @ 0x83d80  (parity: 300/300 trials, PROVEN) */

void dev_ctrl_write2(int param_1, unsigned char param_2, unsigned char param_3,
                   unsigned int param_4, unsigned int param_5)
{
    int iVar1;
    unsigned char local_2c;
    unsigned char local_2b;
    unsigned char *local_28;
    unsigned int local_24;
    unsigned char local_20;
    unsigned int local_1c;
    unsigned int local_18;
    unsigned char local_14;
    int *r4;

    r4 = *(int **)(param_1 + 4);
    iVar1 = *(int *)r4;
    local_20 = 0;
    local_28 = &local_2c;
    local_18 = param_5;
    local_24 = 2;
    local_14 = 7;
    local_2c = param_2;
    local_2b = param_3;
    local_1c = param_4;
    (*(void (**)(int, unsigned char **, int, unsigned short))(*(int *)(iVar1 + 8) + 8))(
        iVar1, &local_28, 2, *(unsigned short *)((char *)r4 + 4));
}
