#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026808 @ 0x00026808
 * public-name: orientation_get_pitch_deg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   orientation_get_pitch_deg                <= FUN_00026808 @ 0x00026808
 *   quaternion_to_euler                      <= FUN_0007cab4 @ 0x0007cab4
 */
/* Reconstructed FUN_00026808 @ 0x26808  (parity: 300/300 trials, PROVEN) */

extern void quaternion_to_euler(unsigned long);
float orientation_get_pitch_deg(int param_1)
{
  if (*(volatile char *)(param_1 + 0x28) == 0) {
    quaternion_to_euler(param_1);
  }
  float a = *(volatile float *)(param_1 + 0x30);
  union { unsigned int u; float f; } c;
  c.u = 0x42652e14u;
  return a * c.f;
}
