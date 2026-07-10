#include "g1_app_symbols.h"
/* named: enqueue_bt_data */
/* globals referenced:
//   0x200038f8  g_bt_data_pipe               
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed enqueue_bt_data @ 0x17eec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t);
extern void debug_print(void);
extern void k_msgq_put(void);
extern int FUN_000720d0_i(uint32_t,void*,int,int);
extern void k_msgq_get(uint32_t,void*,int,int);
extern void memcpy(void*,uint32_t,int);
extern void memset_bytes(void*,int,int);
int enqueue_bt_data(uint32_t param_1, uint8_t param_2){
  uint8_t local_114[0x101];
  memset_bytes(local_114,0,0x101);
  if(*(volatile int*)(((uintptr_t)&g_bt_data_pipe) /*=0x200038f8*/+0x24)==0x30){
    k_msgq_get(((uintptr_t)&g_bt_data_pipe) /*=0x200038f8*/,local_114,0,0);
    if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/==0) DEBUG_PRINT("enqueue_bt_data drop package! \n" /*=0x9a18e*/);
    else debug_print();
  }
  local_114[0]=param_2;
  memcpy(local_114+1,param_1,0x100);
  int iVar1=FUN_000720d0_i(((uintptr_t)&g_bt_data_pipe) /*=0x200038f8*/,local_114,0,0);
  if(iVar1!=0){
    if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/==0) DEBUG_PRINT("enqueue_bt_data failed !\n" /*=0x9a1ae*/);
    else debug_print();
  }
  return iVar1;
}

