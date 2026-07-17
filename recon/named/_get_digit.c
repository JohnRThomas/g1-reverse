/* readable reconstruction; identity: FUN_0007e290 @ 0x0007e290
 * public-name: _get_digit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _get_digit                               <= FUN_0007e290 @ 0x0007e290
 */
/* Reconstructed FUN_0007e290 @ 0x7e290  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int _get_digit(uint32_t *param_1, int32_t *param_2)
{
    int iVar1;
    uint32_t uVar2;
    if (*param_2 < 1) {
        iVar1 = 0x30;
    } else {
        *param_2 = *param_2 - 1;
        uint64_t prod = (uint64_t)(*param_1) * 10;
        uVar2 = param_1[1] * 10 + (uint32_t)(prod >> 32);
        *param_1 = (uint32_t)prod;
        param_1[1] = uVar2 & 0xfffffffU;
        iVar1 = (int)(uVar2 >> 0x1c) + 0x30;
    }
    return iVar1;
}
