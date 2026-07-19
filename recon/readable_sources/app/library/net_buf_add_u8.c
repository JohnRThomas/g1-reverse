#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008370a @ 0x0008370a
 * public-name: net_buf_add_u8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_push                      <= FUN_0005f518 @ 0x0005f518
 *   net_buf_add_u8                           <= FUN_0008370a @ 0x0008370a
 */
/* Reconstructed FUN_0008370a @ 0x8370a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint8_t* net_buf_simple_push(uint32_t a, uint32_t b);
void net_buf_add_u8(uint32_t param_1, uint8_t param_2)
{
  volatile uint8_t *puVar1 = net_buf_simple_push(param_1, 1);
  *puVar1 = param_2;
  return;
}
