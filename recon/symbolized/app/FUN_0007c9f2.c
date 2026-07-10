#include "g1_app_symbols.h"
/* named: FUN_0007c9f2 */
/* Reconstructed FUN_0007c9f2 @ 0x7c9f2  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void ipc_send_len_prefixed_packet_locked_retry(unsigned int,unsigned int,unsigned int,unsigned int);
void FUN_0007c9f2(unsigned int param_1,unsigned int param_2)
{
  ipc_send_len_prefixed_packet_locked_retry(param_1,0x2002,param_2,1);
  return;
}

