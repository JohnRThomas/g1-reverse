/* readable reconstruction; identity: FUN_01020368 @ 0x01020368
 * public-name: FUN_01020368
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01020368 @ 0x1020368  (parity 1 trials PROVEN) */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);

void FUN_01020368(char *param_1, int32_t param_2, uint32_t param_3, uint32_t param_4)
{
    const uint32_t iVar1 = 0x41008000;
    *(volatile uint32_t *)(iVar1 + 0x1ac) = 0x80000006;
    const uint32_t iVar2 = 0x210015f0;

    if (*param_1 == 3) {
        uint32_t uVar4 = (*(volatile uint32_t *)(iVar1 + 0x514)) & 0xfff0ffff;
        if (param_2 == 1) {
            uVar4 |= 0x80000;
        }
        uint32_t uVar3 = ((uint32_t)(uint8_t)param_1[1] & 0x3f) | 0x00023280;
        *(volatile uint32_t *)(iVar1 + 0x514) = uVar4;
        uVar4 = (*(volatile uint32_t *)(iVar2 + 0x14)) | 3;
        *(volatile uint32_t *)(iVar1 + 0x900) = uVar4;
        *(volatile uint32_t *)(iVar1 + 0x910) = uVar3;
        *(volatile uint32_t *)(iVar2 + 0x14) = uVar4;
        *(volatile uint8_t *)(iVar2 + 0x44) = 1;
        return;
    }

    sdc_assertion_fail(0x3e, 0x349, (uint32_t)(uint8_t)*param_1, iVar1, param_4);
    return;
}
