struct k_poll_signal;
struct k_poll_event;
#include <stdint.h>
/* readable reconstruction; identity: FUN_000565c4 @ 0x000565c4
 * public-name: bt_conn_prepare_tx_events
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_tx_drain_and_reset               <= FUN_00056300 @ 0x00056300
 *   bt_conn_prepare_tx_events                <= FUN_000565c4 @ 0x000565c4
 *   k_poll_event_init                        <= FUN_00075574 @ 0x00075574
 *   atomic_and_2                             <= FUN_000813b4 @ 0x000813b4
 *   z_impl_k_poll_signal_init                <= FUN_000868aa @ 0x000868aa
 * address symbols (name @ address):
 *   g_bt_dev_hci_buf_ready                   @ 0x20002104
 *   g_ble_dev_le_pkts_sem                    @ 0x20002108
 *   g_ble_conn_ext_mode_pending              @ 0x20002110
 *   g_ble_conn_poll_signal                   @ 0x20002990
 *   g_ble_conn_pool                          @ 0x20006138
 *   g_ble_conn_ext_signal_buf                @ 0x20006170
 *   g_ble_conn_pool_enabled                  @ 0x20006208
 */
/* Reconstructed FUN_000565c4 @ 0x565c4  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_poll_signal_init(struct k_poll_signal *);
extern void k_poll_event_init(struct k_poll_event *, uint32_t,  int,  void *);
extern void bt_conn_tx_drain_and_reset(void*);
extern int atomic_and_2(volatile long*, long);
int bt_conn_prepare_tx_events(int param_1){
  z_impl_k_poll_signal_init(0x20002990);
  k_poll_event_init(param_1,1,0,0x20002990);
  if(*(volatile int*)0x20006208UL == 0) return 1;
  int r5=0x20006138;
  if(*(volatile unsigned char*)(r5+0xd) == 0){
    int ret=atomic_and_2((void*)(r5+4),0xffffffbf);
    if((ret<<0x19) < 0){ bt_conn_tx_drain_and_reset((void*)r5); return 1; }
  }
  if(*(volatile unsigned char*)(r5+0xd) != 7) return 1;
  if(*(volatile unsigned short*)0x20002104UL == 0) return 1;
  int r2b=*(volatile int*)0x20002110UL;
  int r1=*(volatile int*)(r5+0x38);
  int uVar3,iVar2;
  if(r1==0 || r2b!=0){ uVar3=4; iVar2=0x20006170; }
  else { uVar3=2; iVar2=0x20002108; }
  k_poll_event_init(param_1+0x14, uVar3, 0, iVar2);
  *(volatile unsigned char*)(param_1+0x20)=1;
  return 2;
}
