#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00066130 @ 0x00066130
 * public-name: pdm_release_pin
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpio_pin_port_decode_65ff4           <= FUN_00065ff4 @ 0x00065ff4
 *   pdm_release_pin                          <= FUN_00066130 @ 0x00066130
 */
/* Reconstructed FUN_00066130 @ 0x66130  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int nrf_gpio_pin_port_decode_65ff4(int *p);

void pdm_release_pin(int param_1, unsigned int param_2, unsigned int param_3)
{
  int local_c = param_1;
  unsigned int uStack_8 = param_3;
  (void)uStack_8;
  int iVar1 = nrf_gpio_pin_port_decode_65ff4(&local_c);
  iVar1 = iVar1 + local_c * 4;
  volatile uint32_t *p = (volatile uint32_t *)(iVar1 + 0x200);
  *p = (0xfffcf0f0u & *p) | 2;
}
