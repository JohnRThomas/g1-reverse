/* named: st25dv_mailbox_send_message */
/* globals referenced:
//   0x20007a44  g_st25dv_dev                 
*/
/* Reconstructed st25dv_mailbox_send_message @ 0x24f78  (parity: 300/300 trials, PROVEN) */

extern int st25dv_write_reg_pair(void*);
extern int ipc_ept_op_a_locked_retry(unsigned,int,void*,...);
int st25dv_mailbox_send_message(void){
  volatile unsigned* puVar2 = (volatile unsigned*)0x20007a14UL;
  unsigned local_18; unsigned short local_12; unsigned char local_19;
  short sVar4; int iVar5;
  local_18 = puVar2[0];
  unsigned char b = *(volatile unsigned char*)((int)0x20007a14+2);
  puVar2[3] = 4;
  if(b==0){
    unsigned h = *(volatile unsigned short*)((int)0x20007a14+6);
    local_12 = (unsigned short)(((h&0xff)<<8) | (h>>8));
    puVar2[3]=8;
  }
  sVar4 = (short)st25dv_write_reg_pair(&local_18);
  volatile unsigned* puVar3 = (volatile unsigned*)0x20007a44UL;
  iVar5 = (int)sVar4;
  if(iVar5==0){
    local_19=3;
    iVar5 = ipc_ept_op_a_locked_retry(puVar3[0], (int)puVar2[3], &local_19, 1);
    if(iVar5==0){
      local_19=0;
      iVar5 = ipc_ept_op_a_locked_retry(puVar3[0], (int)puVar2[3]+1, &local_19);
      if(iVar5!=0) iVar5=1;
      iVar5=-iVar5;
    } else { iVar5=-1; }
  }
  return iVar5;
}

