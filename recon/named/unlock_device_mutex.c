/* readable reconstruction; identity: FUN_0007c8c4 @ 0x0007c8c4
 * public-name: unlock_device_mutex
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   unlock_device_mutex                      <= FUN_0007c8c4 @ 0x0007c8c4
 */
/* Reconstructed FUN_0007c8c4 @ 0x7c8c4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void thunk_FUN_00072558(unsigned int);
void unlock_device_mutex(int param_1)
{
  if (param_1 != 0) {
    thunk_FUN_00072558(*(volatile uint32_t*)(param_1 + 0x10));
  }
  return;
}
