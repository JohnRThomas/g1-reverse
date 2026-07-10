/* named: pt_comm_transport_write */
/* Reconstructed pt_comm_transport_write @ 0x30cd0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int ipc_ept_op_a_locked_retry(int,...);
extern int ipc_send_len_prefixed_packet_locked_retry(int,...);
extern int FUN_00074844(int,...);
unsigned int pt_comm_transport_write(int param_1,int param_2,unsigned char *param_3,int param_4)
{
  int iVar1,iVar2;
  unsigned int uVar3;
  unsigned int uStack_14;
  if ((((param_2==0)||(param_3==(unsigned char*)0))||(param_4==0))||(param_1==2)) {
    DEBUG_PRINT(0xa6589);
    return 0xffffffff;
  }
  if (param_1 != 0) {
    if (param_1 != 1) return 0;
    if (((param_2==0)||(param_3==(unsigned char*)0))||(param_4==0)) {
      uVar3 = 0xffffffff;
    } else {
      iVar2 = (**(int(**)(int,...))(*(int*)(param_2+8)+4))(0);
      if (iVar2 == 0) {
        FUN_00074844(0x4000,0);
        (**(int(**)(int,...))(*(int*)(param_2+8)+0x1c))(param_2,*param_3);
        FUN_00074844(0xccd,0);
        uVar3 = 0;
      } else {
        DEBUG_PRINT(0xa65b0);
        uVar3 = 0xfffffffe;
      }
    }
    return uVar3;
  }
  if (((param_2!=0)&&(param_3!=(unsigned char*)0))&&(param_4!=0)) {
    uStack_14 = (unsigned int)param_3 & 0xffffff;
    iVar2 = param_2;
    iVar1 = ipc_send_len_prefixed_packet_locked_retry(param_2,0x2006,(int)&uStack_14+3,1,param_2);
    if (iVar1 == 0) {
      uVar3 = 0x111;
      if (((uStack_14 & 0x6000000) != 0) ||
         (iVar1 = ipc_ept_op_a_locked_retry(param_2,0x2008,param_3,param_4), uVar3 = 0x222, iVar1 != 0)) {
        DEBUG_PRINT(uVar3);
        return 0xfffffffd;
      }
      iVar2 = ipc_send_len_prefixed_packet_locked_retry(param_2,0x2006,(int)&uStack_14+3,1,iVar2);
      if (iVar2 == 0) return 0;
    }
    DEBUG_PRINT(0x333);
    return 0xfffffffe;
  }
  return 0xffffffff;
}

