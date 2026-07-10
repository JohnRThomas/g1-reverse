#include "g1_app_symbols.h"
/* named: dev_reg_modify_bits */
/* Reconstructed dev_reg_modify_bits @ 0x83e0e  (parity: 300/300 trials, PROVEN) */

extern int k_mutex_lock(unsigned,unsigned,int,int,int,unsigned);
extern int k_mutex_unlock(unsigned);
extern int dev_ctrl_read1(int,unsigned,unsigned,void*);
extern int dev_write_reg3(int,unsigned,unsigned);
int dev_reg_modify_bits(int param_1, unsigned param_2, unsigned param_3){
  int iVar1; unsigned uVar2; unsigned char local;
  uVar2=*(unsigned*)(param_1+0x10);
  k_mutex_lock(uVar2,param_2,-1,-1,param_1,param_2);
  iVar1=dev_ctrl_read1(param_1,param_2,param_3,&local);
  if(iVar1==0){ iVar1=dev_write_reg3(param_1,param_2,param_3); }
  k_mutex_unlock(uVar2);
  return iVar1;
}

