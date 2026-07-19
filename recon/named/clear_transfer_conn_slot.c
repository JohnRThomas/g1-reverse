/* readable reconstruction; identity: FUN_00080c06 @ 0x00080c06
 * public-name: clear_transfer_conn_slot
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clear_transfer_conn_slot                 <= FUN_00080c06 @ 0x00080c06
 */
/* Reconstructed FUN_00080c06 @ 0x80c06  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void clear_transfer_conn_slot(volatile int *param_1)
{
  if (*param_1 != 0) {
    *param_1 = 0;
    *(volatile uint8_t*)((int*)param_1 + 1) = 0;
  }
  return;
}
