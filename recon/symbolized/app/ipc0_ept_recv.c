#include "g1_app_symbols.h"
/* named: ipc0_ept_recv */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20007a84  g_ipc0_endpoint              
*/
/* Reconstructed ipc0_ept_recv @ 0x25a48  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int,...);
extern void debug_print(void);
void ipc0_ept_recv(unsigned char *param_1,int param_2){
  int iVar4=0;
  unsigned uVar1=*param_1;
  int *piVar3=(int*)(*(volatile int*)((uintptr_t)&g_ipc0_endpoint) /*=0x20007a84*/ + 4);
  int iVar2=*piVar3;
  unsigned char *pbVar5;
  while(1){
    if(iVar2<=iVar4){
      if(1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/){
        if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
          DEBUG_PRINT("%s(): NOT MATCH(cmd=%x)! ipc_receiver_index: %d, len:%d, received_data: %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\n" /*=0x9f4a1*/,"ipc0_ept_recv" /*=0x9f6e3*/,uVar1,iVar2,param_2,uVar1,(unsigned)param_1[1],(unsigned)param_1[2],(unsigned)param_1[3],(unsigned)param_1[4],(unsigned)param_1[5],(unsigned)param_1[6],(unsigned)param_1[7]);
        } else { debug_print(); }
      }
      return;
    }
    piVar3++;
    pbVar5=(unsigned char*)*piVar3;
    if(pbVar5!=0 && *pbVar5==uVar1) break;
    iVar4++;
  }
  (*(void(*)(int,int,int))*(void**)(pbVar5+8))(*(volatile int*)((uintptr_t)&g_ipc0_endpoint) /*=0x20007a84*/ - 0x714, (int)(param_1+1), param_2-1);
}

