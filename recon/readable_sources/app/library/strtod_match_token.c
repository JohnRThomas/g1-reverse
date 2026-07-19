#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008738e @ 0x0008738e
 * public-name: strtod_match_token
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strtod_match_token                       <= FUN_0008738e @ 0x0008738e
 */
/* Reconstructed FUN_0008738e @ 0x8738e  (parity: 300/300 trials, PROVEN) */

typedef unsigned char byte;
typedef unsigned int uint;

uint strtod_match_token(char **param_1, byte *param_2)
{
    byte bVar1;
    uint uVar2;
    byte *pbVar3;
    pbVar3 = (byte*)*param_1;
    do {
        pbVar3 = pbVar3 + 1;
        bVar1 = *param_2;
        if (bVar1 == 0) {
            *param_1 = (char*)pbVar3;
            return 1;
        }
        uVar2 = (uint)*pbVar3;
        if (uVar2 - 0x41 < 0x1a) {
            uVar2 = uVar2 + 0x20;
        }
        param_2 = param_2 + 1;
    } while (uVar2 == bVar1);
    return 0;
}
