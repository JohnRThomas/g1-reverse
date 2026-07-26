#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00025a48 @ 0x00025a48
 * public-name: ipc0_ept_recv
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9f4a1                             @ 0x0009f4a1   [INLINED -- G6 literal batch]
 *   rodata_9f6e3                             @ 0x0009f6e3   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ipc0_endpoint                          @ 0x20007a84
 */
/* Reconstructed ipc0_ept_recv @ 0x25a48  (parity: 300/300 trials, PROVEN) */

void ipc0_ept_recv(unsigned char *param_1,int param_2){
  int iVar4=0;
  unsigned uVar1=*param_1;
  int *piVar3=(int*)(*(volatile int*)((unsigned long)&g_ipc0_endpoint) /*=0x20007a84*/ + 4);
  int iVar2=*piVar3;
  unsigned char *pbVar5;
  while(1){
    if(iVar2<=iVar4){
      if(1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/){
        if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
          log_message(((unsigned long)"%s(): NOT MATCH(cmd=%x)! ipc_receiver_index: %d, len:%d, received_data: %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\n") /*=0x9f4a1*/,((unsigned long)"ipc0_ept_recv") /*=0x9f6e3*/,uVar1,iVar2,param_2,uVar1,(unsigned)param_1[1],(unsigned)param_1[2],(unsigned)param_1[3],(unsigned)param_1[4],(unsigned)param_1[5],(unsigned)param_1[6],(unsigned)param_1[7]);
        } else {
          debug_print(((unsigned long)"%s(): NOT MATCH(cmd=%x)! ipc_receiver_index: %d, len:%d, received_data: %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\n") /*=0x9f4a1*/,((unsigned long)"ipc0_ept_recv") /*=0x9f6e3*/,uVar1,iVar2,param_2,uVar1,
                       (unsigned)param_1[1],(unsigned)param_1[2],
                       (unsigned)param_1[3],(unsigned)param_1[4],
                       (unsigned)param_1[5],(unsigned)param_1[6],
                       (unsigned)param_1[7]);
        }
      }
      return;
    }
    piVar3++;
    pbVar5=(unsigned char*)*piVar3;
    if(pbVar5!=0 && *pbVar5==uVar1) break;
    iVar4++;
  }
  (*(void(*)(int,int,int))*(void**)(pbVar5+8))(*(volatile int*)((unsigned long)&g_ipc0_endpoint) /*=0x20007a84*/ - 0x714, (int)(param_1+1), param_2-1);
}
