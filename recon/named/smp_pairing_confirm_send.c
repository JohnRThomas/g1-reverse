/* readable reconstruction; identity: FUN_000832f0 @ 0x000832f0
 * public-name: smp_pairing_confirm_send
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_smp_send_pdu                          <= FUN_0005cb38 @ 0x0005cb38
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   atomic_test_bit                          <= FUN_00082ff6 @ 0x00082ff6
 *   atomic_clear_bit_1                       <= FUN_0008304c @ 0x0008304c
 *   atomic_set_bit                           <= FUN_00083090 @ 0x00083090
 *   smp_create_pdu                           <= FUN_000830b0 @ 0x000830b0
 *   smp_c1                                   <= FUN_0008323a @ 0x0008323a
 *   smp_pairing_confirm_send                 <= FUN_000832f0 @ 0x000832f0
 */
/* Reconstructed FUN_000832f0 @ 0x832f0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int bt_smp_send_pdu(int,...);
extern int net_buf_unref(int,...);
extern int net_buf_simple_add(int,...);
extern int atomic_test_bit(int,...);
extern int atomic_clear_bit_1(int,...);
extern int atomic_set_bit(int,...);
extern int smp_create_pdu(int,...);
extern int smp_c1(int,...);
unsigned smp_pairing_confirm_send(int param_1){
  int iVar4 = param_1+4;
  int iVar1 = atomic_test_bit(iVar4,10);
  unsigned uVar2;
  if(iVar1==0){
    uVar2 = atomic_set_bit(param_1,4);
    int iVar3 = *(volatile int*)(param_1+0xf0);
    iVar1 = smp_create_pdu(uVar2,3);
    if(iVar1!=0){
      uVar2 = net_buf_simple_add(iVar1+0xc,0x10);
      iVar3 = smp_c1(param_1+0x47,param_1+0x27,param_1+9,param_1+0x10,iVar3+0x97,iVar3+0x9e,uVar2);
      if(iVar3==0){
        bt_smp_send_pdu(param_1,iVar1,0);
        atomic_clear_bit_1(iVar4,0);
        return 0;
      }
      net_buf_unref(iVar1);
    }
    uVar2 = 8;
  } else {
    atomic_set_bit(iVar4,0);
    uVar2 = 0;
  }
  return uVar2;
}
