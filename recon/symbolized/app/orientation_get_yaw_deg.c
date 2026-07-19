#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000267e8 @ 0x000267e8
 * public-name: orientation_get_yaw_deg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   orientation_get_yaw_deg                  <= FUN_000267e8 @ 0x000267e8
 *   quaternion_to_euler                      <= FUN_0007cab4 @ 0x0007cab4
 */
/* Reconstructed FUN_000267e8 @ 0x267e8  (parity: 300/300 trials, PROVEN) */

extern void quaternion_to_euler(void);
float orientation_get_yaw_deg(int param_1)
{
  if (*(volatile char *)(param_1 + 0x28) == 0) {
    quaternion_to_euler();
  }
  float a = *(volatile float *)(param_1 + 0x2c);
  union { unsigned int u; float f; } c;
  c.u = 0x42652e14u;
  return a * c.f;
}
