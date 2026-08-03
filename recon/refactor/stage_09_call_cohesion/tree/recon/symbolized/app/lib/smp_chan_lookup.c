#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008307a @ 0x0008307a
 * public-name: smp_chan_lookup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_l2cap_le_lookup_rx_cid                <= FUN_00081aca @ 0x00081aca
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 *   smp_chan_lookup                          <= FUN_0008307a @ 0x0008307a
 */
/* Reconstructed FUN_0008307a @ 0x8307a  (parity: 300/300 trials, PROVEN) */

extern long long bt_l2cap_le_lookup_rx_cid(unsigned int, int);
extern int smp_log_message(int, int, unsigned int, unsigned int);

int smp_chan_lookup(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  long long uVar1;
  uVar1 = bt_l2cap_le_lookup_rx_cid(param_1, 6);
  if ((int)uVar1 == 0) {
    return smp_log_message(0, (int)(uVar1 >> 32), param_3, param_4);
  }
  return (int)uVar1 - 0xf0;
}
