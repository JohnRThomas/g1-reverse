#include "g1_app_symbols.h"
/* named: audio_fw_load_get_wrapper */
/* globals referenced:
//   0x2000230c  g_log_level                  
*/
/* Reconstructed audio_fw_load_get_wrapper @ 0x19b54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void DEBUG_PRINT(uint32_t,uint32_t,uint,uint,uint,uint,uint,uint,uint,uint);
extern uint32_t master_process_audio_fw_load_req(int,uint32_t,uint8_t*,uint32_t);
uint32_t audio_fw_load_get_wrapper(int param_1,uint8_t* param_2,uint32_t param_3){
  if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/==5){
    volatile uint8_t* pbVar3=*(volatile uint8_t* volatile*)(param_1+0x10);
    DEBUG_PRINT("spim tx(len=%d): %02x,%02x,%02x,%02x, %02x,%02x,%02x,%02x\n" /*=0x9b2ba*/,*(volatile uint32_t*)(param_1+0x14),pbVar3[0],pbVar3[1],pbVar3[2],pbVar3[3],pbVar3[0],pbVar3[1],pbVar3[2],pbVar3[3]);
  }
  uint32_t uVar2=master_process_audio_fw_load_req(param_1-0x77c,*(volatile uint32_t*)(param_1+0x10),param_2,param_3);
  if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/==5){
    DEBUG_PRINT("spim ret(len=%d): %02x,%02x,%02x,%02x, %02x,%02x,%02x,%02x\n" /*=0x9b2f5*/,param_3,param_2[0],param_2[1],param_2[2],param_2[3],param_2[0],param_2[1],param_2[2],param_2[3]);
  }
  return uVar2;
}

