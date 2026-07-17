#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083e0e @ 0x00083e0e
 * public-name: dev_reg_modify_bits
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 *   dev_ctrl_read1                           <= FUN_00083dba @ 0x00083dba
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   dev_reg_modify_bits                      <= FUN_00083e0e @ 0x00083e0e
 */
/* Reconstructed FUN_00083e0e @ 0x83e0e  (parity: 300/300 trials, PROVEN) */

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
