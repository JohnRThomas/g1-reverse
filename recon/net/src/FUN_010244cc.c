/* net-core FUN_010244cc @ 0x10244cc  (parity 300 trials PROVEN) */
#include <stdint.h>

void FUN_010244cc(uint32_t param_1, int32_t *param_2, int8_t *param_3)
{
    uint32_t uVar3 = ((param_1 >> 0xd) * 0x8637) >> 0x10;
    param_1 = param_1 + uVar3 * (uint32_t)(-0x3d09);
    uint32_t uVar1 = (param_1 * 0x00010c6fU) >> 0x15;
    uint32_t iVar4 = uVar1 * 0x3d09;
    int32_t iVar2 = uVar1 + uVar3 * 0x200;

    if (param_1 <= ((iVar4 + 0x3d08U) >> 9)) {
        *param_2 = iVar2;
        *param_3 = (int8_t)((uint8_t)param_1 - (uint8_t)((iVar4 + 0x100U) >> 9));
        return;
    }
    *param_2 = iVar2 + 1;
    *param_3 = 0;
}

