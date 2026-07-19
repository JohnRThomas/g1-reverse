/* readable reconstruction; identity: FUN_00081a76 @ 0x00081a76
 * public-name: l2cap_chan_disconnected_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_tx_meta_free                       <= FUN_000573ac @ 0x000573ac
 *   conn_ctx_cleanup_if_pending              <= FUN_00081720 @ 0x00081720
 *   bt_l2cap_le_lookup_tx_cid                <= FUN_00081a4e @ 0x00081a4e
 *   l2cap_chan_disconnected_cb               <= FUN_00081a76 @ 0x00081a76
 */
/* Reconstructed FUN_00081a76 @ 0x81a76  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int l2cap_tx_meta_free(int);
extern int conn_ctx_cleanup_if_pending(int);
extern int bt_l2cap_le_lookup_tx_cid(int,int);
int l2cap_chan_disconnected_cb(int param_1, int param_2, int param_3){
  uint32_t r6 = *(volatile uint32_t*)(param_2+8);
  uint32_t r7 = *(volatile uint32_t*)(param_2+0xc);
  uint16_t u1 = *(volatile uint16_t*)(param_2+4);
  int ret573 = l2cap_tx_meta_free(param_2);
  if(param_3 != 0){
    if(r6 != 0){
      return ((int(*)(int,int,int))(uintptr_t)r6)(param_1, r7, param_3);
    }
    return ret573;
  }
  int iVar2 = bt_l2cap_le_lookup_tx_cid(param_1, u1);
  if(iVar2 == 0) return 0;
  uint32_t p = *(volatile uint32_t*)(*(volatile uint32_t*)(iVar2+4)+0x18);
  if(p != 0){
    ((void(*)(void))(uintptr_t)p)();
  }
  if(r6 != 0){
    ((void(*)(int,int,int))(uintptr_t)r6)(param_1, r7, 0);
  }
  return conn_ctx_cleanup_if_pending(iVar2);
}
