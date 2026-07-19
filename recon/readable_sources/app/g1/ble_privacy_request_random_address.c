#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_34         => struct g1_layout_ble_rpa_gen_locals__stack_1170         [stack_1170; G1-original]
 * Raw function identity: 0x000552ac.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000552ac @ 0x000552ac
 * public-name: ble_privacy_request_random_address
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_cmd_send_sync                     <= FUN_00053d70 @ 0x00053d70
 *   ble_privacy_request_random_address       <= FUN_000552ac @ 0x000552ac
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   bt_addr_copy                             <= FUN_00080fba @ 0x00080fba
 *   bt_id_addr_update_thunk                  <= FUN_0008104a @ 0x0008104a
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 * address symbols (name @ address):
 *   rodata_88150                             @ 0x00088150
 *   rodata_f2b41                             @ 0x000f2b41
 *   rodata_f2b47                             @ 0x000f2b47
 *   rodata_f3733                             @ 0x000f3733
 *   rodata_f374c                             @ 0x000f374c
 */
/* Reconstructed FUN_000552ac @ 0x552ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int bt_hci_cmd_send_sync(int,int,void*);
extern void bt_id_addr_update_thunk(uint32_t,int,void*);
extern int memcmp(int,uint32_t,int);
extern void bt_addr_copy(int,int);
extern void net_buf_unref(int);
uint32_t ble_privacy_request_random_address(uint8_t* param_1){
  struct {
    uint32_t pad;
    int local_34[5];
    struct { uint32_t kind, site; } log;
    uint32_t tail[2];
  } frame;
  if(param_1==0){
    frame.log.kind=2; frame.log.site=((unsigned long)&rodata_f3733) /*=0xf3733*/;
    bt_id_addr_update_thunk(((unsigned long)&rodata_88150) /*=0x88150*/,0x1080,&frame.log);
    return 0;
  }
  int iVar1=bt_hci_cmd_send_sync(0x1009,0,frame.local_34);
  if(iVar1!=0){
    frame.log.kind=2; frame.log.site=((unsigned long)&rodata_f374c) /*=0xf374c*/;
    bt_id_addr_update_thunk(((unsigned long)&rodata_88150) /*=0x88150*/,0x1080,&frame.log);
    return 0;
  }
  int iVar2=*(volatile int*)(frame.local_34[0]+0xc)+1;
  int r=memcmp(iVar2,((unsigned long)&rodata_f2b47) /*=0xf2b47*/,6);
  if(r!=0){
    r=memcmp(iVar2,((unsigned long)&rodata_f2b41) /*=0xf2b41*/,6);
    if(r!=0){
      bt_addr_copy((int)param_1+1,iVar2);
      *param_1=0;
      net_buf_unref(frame.local_34[0]);
      return 1;
    }
  }
  net_buf_unref(frame.local_34[0]);
  return 0;
}
