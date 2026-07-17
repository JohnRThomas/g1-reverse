/* readable reconstruction; identity: FUN_0102cbd8 @ 0x0102cbd8
 * public-name: FUN_0102cbd8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d406                           @ 0x0103d406
 */
/* net-core FUN_0102cbd8 @ 0x102cbd8  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_0103b62e(void *dst, uint32_t val, uint32_t len, uint32_t d1, uint32_t d2);
extern int32_t FUN_0103b224(int32_t a, uint32_t b, uint32_t c);
extern void FUN_01039bbe(uint32_t a, uint32_t b, uint32_t c);
extern void FUN_01039bb0(uint32_t a, uint32_t b);

void FUN_0102cbd8(int32_t param_1, uint32_t *param_2, uint32_t param_3, uint32_t param_4)
{
    FUN_0103b62e((void *)(intptr_t)param_1, 0, 0x20, param_4, param_4);

    *(volatile uint32_t *)(param_1 + 0x1c) = param_2[3];
    *(volatile uint32_t *)(param_1 + 0x18) = param_2[2];
    *(volatile uint32_t *)(param_1 + 0x20) = param_2[0];

    uint32_t uVar3 = param_2[1];
    *(volatile uint32_t *)(param_1 + 0x28) = 0;
    *(volatile uint32_t *)(param_1 + 0x24) = uVar3;

    uint32_t uVar2 = param_2[4];
    if ((uVar3 != 0) && (((uVar3 - 1) & uVar3) == 0)) {
        uVar2 = uVar2 | 1;
    }
    *(volatile uint32_t *)(param_1 + 0x10) = uVar2;

    int32_t iVar1 = FUN_0103b224(param_1 + 0x2c, 0, 1);
    if (iVar1 != 0) {
        FUN_01039bbe(0x0103d2a7, 0x0103d406, 0x2e);
        FUN_01039bb0(0x0103d406, 0x2e);
    }
}
