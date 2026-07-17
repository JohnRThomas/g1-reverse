#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083758 @ 0x00083758
 * public-name: net_buf_push_u8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   net_buf_push_u8                          <= FUN_00083758 @ 0x00083758
 */
/* Reconstructed FUN_00083758 @ 0x83758  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint8_t* net_buf_simple_add(uint32_t a, uint32_t b);
void net_buf_push_u8(uint32_t param_1, uint8_t param_2)
{
  volatile uint8_t *puVar1 = net_buf_simple_add(param_1, 1);
  *puVar1 = param_2;
  return;
}
