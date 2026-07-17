/* readable reconstruction; identity: FUN_01020a00 @ 0x01020a00
 * public-name: FUN_01020a00
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01020a00 @ 0x1020a00  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01008d00(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);

void FUN_01020a00(int32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    const uint32_t iVar1 = 0x210015f0;
    *(volatile uint8_t *)(iVar1 + 0x18) = (uint8_t)param_1;

    const uint32_t iVar2 = 0x41008000;
    const uint32_t iVar3 = 0x01ff0000;

    switch (param_1) {
    case 1:
        *(volatile uint32_t *)(iVar2 + 0x510) = 3;
        break;
    case 2:
        *(volatile uint32_t *)(iVar2 + 0x510) = 4;
        *(volatile uint32_t *)(iVar2 + 0x588) = *(volatile uint32_t *)(iVar3 + 0x84);
        return;
    case 4:
        *(volatile uint32_t *)(iVar2 + 0x510) = 6;
        break;
    case 8:
        *(volatile uint32_t *)(iVar2 + 0x510) = 5;
        break;
    default:
        FUN_01008d00(0x3e, 0xd35, iVar1, (uint32_t)(param_1 - 1), param_4);
        return;
    }
    *(volatile uint32_t *)(iVar2 + 0x588) = *(volatile uint32_t *)(iVar3 + 0x80);
}
