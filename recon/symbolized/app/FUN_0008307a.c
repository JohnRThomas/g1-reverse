#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008307a @ 0x0008307a
 * public-name: FUN_0008307a
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_l2cap_le_lookup_rx_cid                <= FUN_00081aca @ 0x00081aca
 */
/* Reconstructed FUN_0008307a @ 0x8307a  (parity: 300/300 trials, PROVEN) */

extern long long bt_l2cap_le_lookup_rx_cid(unsigned int, int);
extern int FUN_00083074(int, int, unsigned int, unsigned int);

int FUN_0008307a(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  long long uVar1;
  uVar1 = bt_l2cap_le_lookup_rx_cid(param_1, 6);
  if ((int)uVar1 == 0) {
    return FUN_00083074(0, (int)(uVar1 >> 32), param_3, param_4);
  }
  return (int)uVar1 - 0xf0;
}
