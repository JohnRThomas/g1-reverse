#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000821a4 @ 0x000821a4
 * public-name: bt_att_chan_send_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_chan_send                            <= FUN_00058a54 @ 0x00058a54
 *   net_buf_put                              <= FUN_0005f200 @ 0x0005f200
 *   bt_att_chan_send_rsp                     <= FUN_000821a4 @ 0x000821a4
 */
/* Reconstructed FUN_000821a4 @ 0x821a4  (parity: 300/300 trials, PROVEN) */

extern int att_chan_send(unsigned long, unsigned long);
extern void net_buf_put(unsigned int,unsigned int,unsigned int,unsigned int);
void bt_att_chan_send_rsp(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  int iVar1 = att_chan_send(param_1, param_2);
  if (iVar1 != 0) {
    net_buf_put(param_1 + 0x128, param_2, param_3, param_4);
  }
}
