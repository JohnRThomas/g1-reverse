#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000265b8 @ 0x000265b8
 * public-name: imu_fusion_state_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   imu_fusion_state_init                    <= FUN_000265b8 @ 0x000265b8
 */
/* Reconstructed FUN_000265b8 @ 0x265b8  (parity: 300/300 trials, PROVEN) */

void imu_fusion_state_init(volatile unsigned int *param_1)
{
    param_1[0] = 0x3dcccccdu;
    param_1[1] = 0x40800000u;
    param_1[2] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[3] = 0x3f800000u;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    *(volatile unsigned char*)(param_1 + 10) = 0;
}
