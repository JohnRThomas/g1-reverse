/* readable reconstruction; identity: FUN_00084d64 @ 0x00084d64
 * public-name: flash_calc_prev_ate_offset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_calc_prev_ate_offset               <= FUN_00084d64 @ 0x00084d64
 */
/* Reconstructed FUN_00084d64 @ 0x84d64  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int flash_calc_prev_ate_offset(int param_1)
{
  return (*(volatile uint32_t*)(param_1 + 8) - 0x18U & 0xfffffff8) - 0x10;
}
