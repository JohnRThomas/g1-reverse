#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103467c @ 0x0103467c
 * public-name: FUN_0103467c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103467c @ 0x103467c  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"

extern int32_t FUN_01034650(uint32_t a);

uint32_t FUN_0103467c(uint32_t param_1)
{
    uint32_t uVar3 = 0;
    uint32_t uVar4 = 0;

    do {
        int32_t iVar1 = FUN_01034650(uVar3 & 0xff);
        uint32_t uVar2 = 1u << (((uint32_t)(iVar1 - 0x100) >> 2) & 0xff);
        if ((param_1 & uVar2) != 0) {
            volatile int32_t *p = (int32_t *)(iVar1 + G1_NRF_GPIOTE_NS_BASE);
            if (*p != 0) {
                *p = 0;
                uVar4 |= uVar2;
            }
        }
        uVar3 = uVar3 + 1;
    } while (uVar3 != 8);

    volatile int32_t * const p2 = (int32_t *)(G1_NRF_GPIOTE_NS_BASE + 0x17c);
    if (*p2 != 0) {
        *p2 = 0;
        uVar4 |= 0x80000000;
    }
    return uVar4;
}
