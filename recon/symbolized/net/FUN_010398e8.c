#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010398e8 @ 0x010398e8
 * public-name: FUN_010398e8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010398e8 @ 0x10398e8  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int32_t FUN_01039752(uint32_t a, int32_t b, int32_t c, int32_t d);
extern int32_t FUN_01039768(uint32_t a, int32_t b);
extern int32_t FUN_010397a4(uint32_t a, int32_t b, int32_t c);

void FUN_010398e8(uint32_t param_1, int32_t param_2, int32_t param_3)
{
    int32_t iVar1;
    int32_t iVar2;

    iVar1 = FUN_01039768(param_1, param_2);
    iVar1 = (param_2 - param_3) + iVar1;
    FUN_010397a4(param_1, param_2, param_3 - param_2);
    FUN_010397a4(param_1, param_3, iVar1);
    FUN_01039752(param_1, param_3, 0, param_3 - param_2);
    iVar2 = FUN_01039768(param_1, param_3);
    FUN_01039752(param_1, param_3 + iVar2, 0, iVar1);
}
