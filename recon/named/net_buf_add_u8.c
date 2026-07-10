/* named: net_buf_add_u8 */
/* Reconstructed net_buf_add_u8 @ 0x8370a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint8_t* net_buf_simple_push(uint32_t a, uint32_t b);
void net_buf_add_u8(uint32_t param_1, uint8_t param_2)
{
  volatile uint8_t *puVar1 = net_buf_simple_push(param_1, 1);
  *puVar1 = param_2;
  return;
}

