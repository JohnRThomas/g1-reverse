#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_orientation_state__param_0073          [param_0073; G1-original]
 * Raw function identity: 0x00026828.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00026828 @ 0x00026828
 * public-name: orientation_get_heading_deg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   orientation_get_heading_deg              <= FUN_00026828 @ 0x00026828
 *   quaternion_to_euler                      <= FUN_0007cab4 @ 0x0007cab4
 */
/* Reconstructed FUN_00026828 @ 0x26828 */
#include <stdint.h>

extern void quaternion_to_euler(unsigned long);

float orientation_get_heading_deg(uint8_t *state)
{
    if (state[0x28] == 0)
        quaternion_to_euler(state);
    return 180.0f + *(volatile float *)(state + 0x34) * 57.295f;
}
