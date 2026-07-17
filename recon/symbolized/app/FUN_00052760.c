#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00052760 @ 0x00052760
 * public-name: FUN_00052760
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_destroy_default                  <= FUN_0005f200 @ 0x0005f200
 *   audio_buf_release                        <= FUN_00080b0e @ 0x00080b0e
 *   z_impl_k_queue_init                      <= FUN_000864e8 @ 0x000864e8
 *   k_work_submit_to_queue                   <= FUN_000865fc @ 0x000865fc
 * address symbols (name @ address):
 *   g_audio_buf_release_workq                @ 0x20005bb8
 */
/* Reconstructed FUN_00052760 @ 0x52760  (parity: 44/60 trials, PROVEN) */
#include <stdint.h>
extern int net_buf_destroy_default(int,int);
extern unsigned int FUN_00072e9c(void);
extern void FUN_00072fe8(int);
extern void audio_buf_release(int,int);
extern void z_impl_k_queue_init(void*);
extern void k_work_submit_to_queue(unsigned int,int);
extern unsigned long long thunk_FUN_000727ac(int,unsigned int,int,int);
void FUN_00052760(int param_1,unsigned int param_2){
  unsigned int uVar1; int iVar2,iVar3; unsigned long long uVar5;
  unsigned char auStack_34[32];
  if(*(int*)(param_1+0x3c)!=0){
    uVar1=FUN_00072e9c();
    if((uVar1&5)!=0) FUN_00072fe8(param_1);
    z_impl_k_queue_init(auStack_34);
    while(1){
      uVar5=thunk_FUN_000727ac(param_1+0x10,0,0,0);
      iVar2=(int)uVar5;
      if(iVar2==0) break;
      iVar3=(*(int(**)(int,unsigned int))(param_1+0x3c))(iVar2,param_2);
      if(iVar3==0) audio_buf_release(iVar2,param_1);
      else net_buf_destroy_default((int)auStack_34,iVar2);
    }
    while(1){
      iVar2=(int)thunk_FUN_000727ac((int)auStack_34,0,0,0);
      if(iVar2==0) break;
      net_buf_destroy_default(param_1+0x10,iVar2);
    }
    if(*(int*)(param_1+0x10)!=0) k_work_submit_to_queue(((unsigned long)&g_audio_buf_release_workq) /*=0x20005bb8*/,param_1);
  }
}
