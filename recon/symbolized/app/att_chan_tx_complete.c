#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00082326 @ 0x00082326
 * public-name: att_chan_tx_complete
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_chan_req_free                        <= FUN_0005833c @ 0x0005833c
 *   atomic_clear_bit_0                       <= FUN_00081e14 @ 0x00081e14
 *   att_optional_sent_cb_dispatch            <= FUN_000822ae @ 0x000822ae
 *   att_chan_tx_complete                     <= FUN_00082326 @ 0x00082326
 */
/* Reconstructed FUN_00082326 @ 0x82326  (parity: 300/300 trials, PROVEN) */

extern void att_optional_sent_cb_dispatch(void);
extern void atomic_clear_bit_0(int,unsigned int);
extern void att_chan_req_free(int*);
void att_chan_tx_complete(unsigned int param_1,int *param_2,int param_3)
{
  if (param_3 == 0) {
    att_optional_sent_cb_dispatch();
  }
  atomic_clear_bit_0(*param_2 + 0x120,1);
  att_chan_req_free(param_2);
  return;
}
