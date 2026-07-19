#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00075dc8 @ 0x00075dc8
 * public-name: sqrtf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sqrtf                                    <= FUN_00075dc8 @ 0x00075dc8
 *   sqrtf_hw                                 <= FUN_000869c6 @ 0x000869c6
 * address symbols (name @ address):
 *   g_libm_ieee_mode_flag                    @ 0x200035af
 */
/* Reconstructed FUN_00075dc8 @ 0x75dc8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern float sqrtf_hw(void);
extern unsigned int* thunk_FUN_00071678(void);

float sqrtf(float param_1)
{
  float fVar3 = sqrtf_hw();
  float fVar1 = 0.0f;
  if ((*(volatile int8_t*)((unsigned long)&g_libm_ieee_mode_flag) /*=0x200035af*/ != -1) && (param_1 < fVar1)) {
    unsigned int *puVar2 = thunk_FUN_00071678();
    fVar3 = fVar1 / fVar1;
    *puVar2 = 0x21;
  }
  return fVar3;
}
