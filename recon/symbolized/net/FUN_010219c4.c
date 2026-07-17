#include "g1_net_symbols.h"
/* net-core FUN_010219c4 @ 0x10219c4  (parity 300 trials PROVEN) */
#include <stdint.h>
#include <stdbool.h>

bool FUN_010219c4(char *param_1)
{
    uint32_t uVar1;
    const uint32_t k_a14 = 0x0001863c;
    const uint32_t k_a18 = 0x0f424000;

    if (param_1 != 0) {
        if (*param_1 == 0) {
            if (((uint8_t)param_1[4] < 2) && ((uint8_t)param_1[5] < 2) &&
                (*(uint32_t *)(param_1 + 8) - 0x64u <= k_a14)) {
                uVar1 = *(uint32_t *)(param_1 + 0xc);
                return uVar1 < k_a18;
            }
        } else if ((*param_1 == 1) && ((uint8_t)param_1[4] < 2) &&
                   ((uint8_t)param_1[5] < 2) &&
                   (*(uint32_t *)(param_1 + 0xc) - 0x64u <= k_a14)) {
            uVar1 = *(uint32_t *)(param_1 + 8);
            return uVar1 < k_a18;
        }
    }
    return false;
}
