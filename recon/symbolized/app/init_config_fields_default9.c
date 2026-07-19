#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c3c2 @ 0x0007c3c2
 * public-name: init_config_fields_default9
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   init_config_fields_default9              <= FUN_0007c3c2 @ 0x0007c3c2
 */
/* Reconstructed FUN_0007c3c2 @ 0x7c3c2  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void init_config_fields_default9(void *param_1)
{
  *(volatile uint8_t*)((char*)param_1 + 0xb) = 9;
  *(volatile uint8_t*)((char*)param_1 + 0xc) = 9;
  *(volatile uint16_t*)((char*)param_1 + 0x30) = 0x909;
  return;
}
