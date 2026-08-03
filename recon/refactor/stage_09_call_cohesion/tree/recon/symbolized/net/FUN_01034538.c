#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01034538 @ 0x01034538
 * public-name: FUN_01034538
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_res_pool_slot_tbl                  @ 0x210006a8
 */
/* net-core FUN_01034538 @ 0x1034538  (parity 300 trials PROVEN) */

extern unsigned long long FUN_010344a8(void);
typedef unsigned int (*fnptr)(unsigned int,unsigned int,unsigned int);

void FUN_01034538(unsigned int param_1)
{
    unsigned long long uVar4;
    unsigned int iVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    fnptr f;

    uVar4 = FUN_010344a8();
    iVar1 = ((unsigned long)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/;
    uVar2 = (unsigned int)(uVar4 >> 32);
    uVar3 = (unsigned int)(unsigned short)(*(unsigned short *)(iVar1 + ((unsigned int)uVar4 + 8) * 2));
    if ((int)(uVar3 << 0x17) < 0) {
        uVar3 = (uVar3 << 0x13) >> 0x1c;
        f = *(fnptr *)(iVar1 + uVar3 * 8);
        f(param_1, uVar2, *(unsigned int *)(iVar1 + uVar3 * 8 + 4));
    }
    f = *(fnptr *)(iVar1 + 8);
    if (f != 0) {
        f(param_1, uVar2, *(unsigned int *)(iVar1 + 0xc));
    }
}
