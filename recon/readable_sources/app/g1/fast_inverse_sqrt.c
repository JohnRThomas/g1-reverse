#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000265e8 @ 0x000265e8
 * public-name: fast_inverse_sqrt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fast_inverse_sqrt                        <= FUN_000265e8 @ 0x000265e8
 */
/* Reconstructed FUN_000265e8 @ 0x265e8  (parity: 300/300 trials, PROVEN) */

float fast_inverse_sqrt(float param_1)
{
  union { float f; int i; } u;
  int r3;
  float half, fVar1, t;
  volatile float tf;
  half = param_1 * 0.5f;
  u.f = param_1;
  r3 = 0x5f3759df - (u.i >> 1);
  u.i = r3;
  fVar1 = u.f;
  t = fVar1 * half;
  tf = t*fVar1;
  fVar1 = (1.5f - tf) * fVar1;
  t = fVar1 * half;
  tf = t*fVar1;
  return (1.5f - tf) * fVar1;
}
