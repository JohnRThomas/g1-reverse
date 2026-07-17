#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000821a4 @ 0x000821a4
 * public-name: bt_att_chan_send_rsp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_destroy_default                  <= FUN_0005f200 @ 0x0005f200
 *   bt_att_chan_send_rsp                     <= FUN_000821a4 @ 0x000821a4
 */
/* Reconstructed FUN_000821a4 @ 0x821a4  (parity: 300/300 trials, PROVEN) */

extern int FUN_00058a54(void);
extern void net_buf_destroy_default(unsigned int,unsigned int,unsigned int,unsigned int);
void bt_att_chan_send_rsp(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  int iVar1 = FUN_00058a54();
  if (iVar1 != 0) {
    net_buf_destroy_default(param_1 + 0x128, param_2, param_3, param_4);
  }
}
