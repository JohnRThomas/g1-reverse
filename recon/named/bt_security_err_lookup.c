/* readable reconstruction; identity: FUN_00054250 @ 0x00054250
 * public-name: bt_security_err_lookup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_security_err_lookup                   <= FUN_00054250 @ 0x00054250
 */
/* Reconstructed FUN_00054250 @ 0x54250  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t bt_security_err_lookup(unsigned int param_1)
{
  uint8_t uVar1;
  if (param_1 < 0x2a) {
    uVar1 = *(volatile uint8_t*)(0x000f33e9UL + param_1);
  } else {
    uVar1 = 9;
  }
  return uVar1;
}
