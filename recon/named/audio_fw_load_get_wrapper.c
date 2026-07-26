/* readable reconstruction; identity: FUN_00019b54 @ 0x00019b54
 * public-name: audio_fw_load_get_wrapper
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_fw_load_get_wrapper                <= FUN_00019b54 @ 0x00019b54
 *   master_process_audio_fw_load_req         <= FUN_0002af4c @ 0x0002af4c
 * address symbols (name @ address):
 *   rodata_9b2ba                             @ 0x0009b2ba   [INLINED -- G6 literal batch]
 *   rodata_9b2f5                             @ 0x0009b2f5   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 */
/* Reconstructed FUN_00019b54 @ 0x19b54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
typedef unsigned int uint;
extern uint32_t master_process_audio_fw_load_req(int,uint32_t,uint8_t*,uint32_t);
uint32_t audio_fw_load_get_wrapper(int param_1,uint8_t* param_2,uint32_t param_3){
  if(*(volatile int*)0x2000230cUL==5){
    volatile uint8_t* pbVar3=*(volatile uint8_t* volatile*)(param_1+0x10);
    log_message(((unsigned long)"spim tx(len=%d): %02x,%02x,%02x,%02x, %02x,%02x,%02x,%02x\n"),*(volatile uint32_t*)(param_1+0x14),pbVar3[0],pbVar3[1],pbVar3[2],pbVar3[3],pbVar3[0],pbVar3[1],pbVar3[2],pbVar3[3]);
  }
  uint32_t uVar2=master_process_audio_fw_load_req(param_1-0x77c,*(volatile uint32_t*)(param_1+0x10),param_2,param_3);
  if(*(volatile int*)0x2000230cUL==5){
    log_message(((unsigned long)"spim ret(len=%d): %02x,%02x,%02x,%02x, %02x,%02x,%02x,%02x\n"),param_3,param_2[0],param_2[1],param_2[2],param_2[3],param_2[0],param_2[1],param_2[2],param_2[3]);
  }
  return uVar2;
}
