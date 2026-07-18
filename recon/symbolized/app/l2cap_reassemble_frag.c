#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00082e04 @ 0x00082e04
 * public-name: l2cap_reassemble_frag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_prepare_write_rsp                   <= FUN_0005c310 @ 0x0005c310
 *   l2cap_reassemble_frag                    <= FUN_00082e04 @ 0x00082e04
 */
/* Reconstructed FUN_00082e04 @ 0x82e04  (parity: 300/300 trials, PROVEN) */
extern void gatt_prepare_write_rsp(int,int,int,void*);
void l2cap_reassemble_frag(int param_1,int param_2,int param_3,int param_4,void **param_5){
  (void)param_4;
  if (param_2 != 0){
    (*(void(*)(int,int,void*))*param_5)(param_1,param_2,param_5);
  } else {
    gatt_prepare_write_rsp(param_1,param_3,param_4,param_5);
  }
}
