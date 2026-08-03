#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01010990 @ 0x01010990
 * public-name: FUN_01010990
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c1bc                           @ 0x0103c1bc
 */
/* net-core FUN_01010990 @ 0x1010990  (parity 300 trials PROVEN) */
#include <stdint.h>

int32_t FUN_01010990(int32_t param_1, int32_t param_2)
{
    volatile uint16_t * const tab = (uint16_t *)((unsigned long)&rodata_103c1bc) /*=0x103c1bc*/;
    const uint64_t mul = 0x10624dd3ULL;

    int32_t iVar2 = (param_1 - 1) * 0x80;
    uint32_t uVar3 = (uint32_t)((mul * (uint64_t)(tab[param_2] + 999)) >> 0x26);

    if (param_2 == 8) {
        return param_1 * 0x690 + uVar3 + iVar2;
    }
    if (param_2 == 4) {
        return param_1 * 0x2be + uVar3 + iVar2;
    }
    int32_t iVar1;
    if (param_2 == 2) {
        iVar1 = 0x60;
    } else {
        iVar1 = 0xf0;
    }
    return iVar1 * param_1 + uVar3 + iVar2;
}
