/* readable reconstruction; identity: FUN_0007c9f2 @ 0x0007c9f2
 * public-name: send_box_event_ipc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_send_len_prefixed_packet_locked_retry <= FUN_00025788 @ 0x00025788
 *   send_box_event_ipc                       <= FUN_0007c9f2 @ 0x0007c9f2
 */
/* Reconstructed FUN_0007c9f2 @ 0x7c9f2  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int ipc_send_len_prefixed_packet_locked_retry(unsigned long, unsigned long, void*, unsigned long);
void send_box_event_ipc(unsigned int param_1,unsigned int param_2)
{
  ipc_send_len_prefixed_packet_locked_retry(param_1,0x2002,param_2,1);
  return;
}
