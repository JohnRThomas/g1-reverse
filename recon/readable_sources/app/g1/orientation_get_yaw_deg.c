#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_orientation_state__param_0071          [param_0071; G1-original]
 * Raw function identity: 0x000267e8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000267e8 @ 0x000267e8
 * public-name: orientation_get_yaw_deg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   orientation_get_yaw_deg                  <= FUN_000267e8 @ 0x000267e8
 *   quaternion_to_euler                      <= FUN_0007cab4 @ 0x0007cab4
 */
/* Reconstructed FUN_000267e8 @ 0x267e8  (parity: 300/300 trials, PROVEN) */

extern void quaternion_to_euler(unsigned long);
float orientation_get_yaw_deg(int param_1)
{
  if (*(volatile char *)(param_1 + 0x28) == 0) {
    quaternion_to_euler(param_1);
  }
  float a = *(volatile float *)(param_1 + 0x2c);
  union { unsigned int u; float f; } c;
  c.u = 0x42652e14u;
  return a * c.f;
}
