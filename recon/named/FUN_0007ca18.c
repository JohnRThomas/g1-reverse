/* readable reconstruction; identity: FUN_0007ca18 @ 0x0007ca18
 * public-name: FUN_0007ca18
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_send_len_prefixed_packet_locked_retry <= FUN_00025788 @ 0x00025788
 */
/* Reconstructed FUN_0007ca18 @ 0x7ca18  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void ipc_send_len_prefixed_packet_locked_retry(unsigned int,unsigned int,unsigned int,unsigned int);
void FUN_0007ca18(unsigned int param_1,unsigned int param_2)
{
  ipc_send_len_prefixed_packet_locked_retry(param_1,0x2005,param_2,1);
  return;
}
