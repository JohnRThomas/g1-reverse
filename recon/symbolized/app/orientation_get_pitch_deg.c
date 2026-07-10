#include "g1_app_symbols.h"
/* named: orientation_get_pitch_deg */
/* Reconstructed orientation_get_pitch_deg @ 0x26808  (parity: 300/300 trials, PROVEN) */

extern void quaternion_to_euler(void);
float orientation_get_pitch_deg(int param_1)
{
  if (*(volatile char *)(param_1 + 0x28) == 0) {
    quaternion_to_euler();
  }
  float a = *(volatile float *)(param_1 + 0x30);
  union { unsigned int u; float f; } c;
  c.u = 0x42652e14u;
  return a * c.f;
}

