#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007e260 @ 0x0007e260
 * public-name: _ldiv5
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _ldiv5                                   <= FUN_0007e260 @ 0x0007e260
 */
/* Reconstructed FUN_0007e260 @ 0x7e260  (parity: 300/300 trials, PROVEN) */

void _ldiv5(unsigned int *param_1)
{
    unsigned long long lVar1 = (unsigned long long)param_1[0] * 0x33333333ULL;
    unsigned long long lVar2 = lVar1 + (unsigned long long)param_1[1] * 0x33333333ULL;
    unsigned int lo1 = (unsigned int)lVar1;
    unsigned int hi1 = (unsigned int)(lVar1 >> 32);
    unsigned int termb = hi1 + (unsigned int)(0xccccccccU < lo1) + 0x33333333U;
    unsigned int lo2 = (unsigned int)lVar2;
    unsigned int hi2 = (unsigned int)(lVar2 >> 32);
    unsigned int carry2 = (unsigned int)((lo2 + termb) < lo2);
    unsigned long long X = (unsigned long long)hi2 + carry2;
    unsigned long long result = (unsigned long long)param_1[1]*0x33333333ULL + X;
    *(volatile unsigned long long*)param_1 = result;
}
