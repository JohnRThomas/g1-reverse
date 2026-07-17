#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083b62 @ 0x00083b62
 * public-name: dev_write_bits5_diff
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_write_bits5_diff                     <= FUN_00083b62 @ 0x00083b62
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 */
/* Reconstructed FUN_00083b62 @ 0x83b62  (parity: 300/300 trials, PROVEN) */

extern int dev_write_reg3(unsigned int a, int b, unsigned int c, unsigned int d, unsigned int e);

int dev_write_bits5_diff(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    int iVar4;

    uVar3 = 0;
    iVar4 = *(int *)(param_1 + 4);
    do {
        if ((int)((param_2 >> (uVar3 & 0xff)) << 0x1f) < 0) {
            if ((int)((param_3 >> (uVar3 & 0xff)) << 0x1f) < 0) {
                uVar2 = 8;
            } else {
                uVar2 = 9;
            }
            iVar1 = dev_write_reg3(*(unsigned int *)(iVar4 + 4), 6, uVar3 & 0xff, uVar2, param_4);
            if (iVar1 != 0) {
                return iVar1;
            }
        }
        uVar3 = uVar3 + 1;
        if (uVar3 == 5) {
            return 0;
        }
    } while (1);
}
