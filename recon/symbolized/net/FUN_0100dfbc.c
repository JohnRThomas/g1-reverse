#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100dfbc @ 0x0100dfbc
 * public-name: FUN_0100dfbc
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 */
/* net-core FUN_0100dfbc @ 0x100dfbc  (parity 300 trials PROVEN) */

extern __attribute__((noreturn)) void sdc_assertion_fail(unsigned int a, unsigned int b,
                                                   unsigned int c, unsigned int d,
                                                   unsigned int e);

void FUN_0100dfbc(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1 = (*param_1 & 0xfffffff0) | (param_2 & 0xf);
    *param_1 = (unsigned char)uVar1;
    switch (param_2) {
    case 0: case 2: case 4: case 6:
        param_1[1] = 6; return;
    case 1: case 3:
        param_1[1] = 0xc; return;
    case 5:
        param_1[1] = 0x22; return;
    case 7:
        param_1[3] = 0;
        param_1[1] = 1;
        return;
    case 8:
        param_1[1] = 0xe; return;
    default:
        sdc_assertion_fail(0x2a, 0xa8, param_2 & 0xf, uVar1, param_4);
    }
}
