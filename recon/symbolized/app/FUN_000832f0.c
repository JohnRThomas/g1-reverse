#include "g1_app_symbols.h"
/* named: FUN_000832f0 */
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
unsigned FUN_000832f0(int param_1){
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

