#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017eec @ 0x00017eec
 * public-name: enqueue_bt_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   enqueue_bt_data                          <= FUN_00017eec @ 0x00017eec
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9a18e                             @ 0x0009a18e   [INLINED -- G6 literal batch]
 *   rodata_9a1ae                             @ 0x0009a1ae   [INLINED -- G6 literal batch]
 *   g_bt_data_pipe                           @ 0x200038f8
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_00017eec @ 0x17eec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int k_msgq_put(unsigned int, void*, int, int);
extern int FUN_000720d0_i(uint32_t,void*,int,int);
extern int k_msgq_get(int, unsigned int, int, int);
extern void memcpy(int, int, int);
extern void memset_bytes(void*,int,int);
int enqueue_bt_data(uint32_t param_1, uint8_t param_2){
  uint8_t local_114[0x101];
  memset_bytes(local_114,0,0x101);
  if(*(volatile int*)(((unsigned long)&g_bt_data_pipe) /*=0x200038f8*/+0x24)==0x30){
    k_msgq_get(((unsigned long)&g_bt_data_pipe) /*=0x200038f8*/,local_114,0,0);
    if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0) log_message(((unsigned long)"enqueue_bt_data drop package! \n") /*=0x9a18e*/);
    else debug_print(((unsigned long)"enqueue_bt_data drop package! \n") /*=0x9a18e*/);
  }
  local_114[0]=param_2;
  memcpy(local_114+1,param_1,0x100);
  int iVar1=FUN_000720d0_i(((unsigned long)&g_bt_data_pipe) /*=0x200038f8*/,local_114,0,0);
  if(iVar1!=0){
    if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0) log_message(((unsigned long)"enqueue_bt_data failed !\n") /*=0x9a1ae*/);
    else debug_print(((unsigned long)"enqueue_bt_data failed !\n") /*=0x9a1ae*/);
  }
  return iVar1;
}
