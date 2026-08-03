#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026828 @ 0x00026828
 * public-name: orientation_get_heading_deg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   orientation_get_heading_deg              <= FUN_00026828 @ 0x00026828
 *   quaternion_to_euler                      <= FUN_0007cab4 @ 0x0007cab4
 */
/* Reconstructed FUN_00026828 @ 0x26828 */
#include <stdint.h>
#include "g1_imu.h"


float orientation_get_heading_deg(uint8_t *state)
{
    if (state[0x28] == 0)
        quaternion_to_euler(state);
    return 180.0f + *(volatile float *)(state + 0x34) * 57.295f;
}
