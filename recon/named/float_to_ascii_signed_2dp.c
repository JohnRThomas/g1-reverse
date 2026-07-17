/* readable reconstruction; identity: FUN_0004a300 @ 0x0004a300
 * public-name: float_to_ascii_signed_2dp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   float_to_ascii_signed_2dp                <= FUN_0004a300 @ 0x0004a300
 */
/* Reconstructed FUN_0004a300 @ 0x4a300  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>

int float_to_ascii_signed_2dp(float param_1, char *param_2v){
    volatile char *param_2 = param_2v;
    char local_25[17];
    int32_t t = (int32_t)(param_1 * 100.0f);
    uint32_t uVar7 = (uint32_t)t;
    int32_t s = (int32_t)uVar7 >> 31;
    uint32_t uVar4 = (uVar7 ^ (uint32_t)s) - (uint32_t)s;
    for (int i = 1; i <= 0xc; i++) local_25[i] = 0;
    int iVar6;
    if ((int)uVar4 < 10) iVar6 = 2;
    else if ((int)uVar4 < 100) iVar6 = 1;
    else iVar6 = 0;
    int iVar1 = 0;
    while (uVar4 != 0){
        if (iVar1 == 2 && iVar6 == 0){ iVar1 = 3; local_25[3] = 0x2e; }
        local_25[iVar1+1] = (char)((char)uVar4 + (char)(uVar4/10)*(-10) + '0');
        iVar1 = iVar1 + 1;
        uVar4 = uVar4 / 10;
    }
    char cVar3;
    if (iVar6 == 2){
        cVar3 = ((int32_t)uVar7 < 1) ? '-' : '+';
        local_25[iVar1+1] = '0';
        *param_2 = cVar3;
        iVar1 = iVar1 + 1;
    } else {
        cVar3 = ((int32_t)uVar7 < 1) ? '-' : '+';
        *param_2 = cVar3;
        if (iVar6 == 0){
            char *pcVar5 = local_25 + iVar1 + 1;
            volatile char *pcVar2 = param_2 + iVar1;
            while (param_2 != pcVar2){ pcVar5 = pcVar5 - 1; param_2 = param_2 + 1; *param_2 = *pcVar5; }
            param_2[1] = 0;
            return iVar1 + 1;
        }
    }
    param_2[1] = '0';
    param_2 = param_2 + 2;
    *param_2 = '.';
    iVar6 = iVar1;
    while (iVar6 - 1 != -1){ param_2 = param_2 + 1; *param_2 = local_25[iVar6]; iVar6 = iVar6 - 1; }
    return iVar1 + 3;
}
