#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103b5dc @ 0x0103b5dc
 * public-name: FUN_0103b5dc
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103b5dc @ 0x103b5dc  (parity 300 trials PROVEN) */

void FUN_0103b5dc(unsigned int param_1, char *param_2, unsigned int param_3)
{
    int c2;
    unsigned int uVar4;
    unsigned char cVar3;
    int bVar1;
    if ((int)(param_3 << 0x16) < 0) {
        param_3 = param_3 & 0xfffffdff;
        c2 = 7;
    } else {
        c2 = 0x27;
    }
    do {
        uVar4 = param_1 - param_3 * (param_1/param_3);
        cVar3 = (unsigned char)uVar4;
        if (9 < cVar3) {
            cVar3 = cVar3 + c2;
        }
        *param_2 = cVar3 + (char)0x30;
        bVar1 = param_3 <= param_1;
        param_2 = param_2 + 1;
        param_1 = param_1 / param_3;
    } while (bVar1);
}
