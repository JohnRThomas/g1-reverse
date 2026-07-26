#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00031b60 @ 0x00031b60
 * public-name: build_str_response_frame
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 *   get_device_serial_buf                    <= FUN_000232b0 @ 0x000232b0
 *   build_str_response_frame                 <= FUN_00031b60 @ 0x00031b60
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   vdprintf_to_fd                           <= FUN_00086f00 @ 0x00086f00
 * address symbols (name @ address):
 *   rodata_a701c                             @ 0x000a701c   [INLINED -- G6 literal batch]
 *   rodata_a7031                             @ 0x000a7031   [INLINED -- G6 literal batch]
 *   rodata_a8c37                             @ 0x000a8c37
 */
/* Reconstructed FUN_00031b60 @ 0x31b60  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern int strlen(void*);
extern int get_device_serial_buf(void);
extern void memcpy(void*,void*,int);
extern void memset_bytes(void*,int,int);
extern void vdprintf_to_fd(void*,int,int,uint32_t,int);
uint32_t build_str_response_frame(int param_1,uint32_t param_2,uint32_t *param_3,char *param_4){
  uint32_t uVar2=0;
  struct {
    uint32_t payload;
    uint8_t scratch[28];
  } workspace;
  workspace.payload = 0;
  memset_bytes(workspace.scratch,0,0x1c);
  log_message(((unsigned long)"join in get_sn_info\n") /*=0xa701c*/);
  if(param_3==0 || param_4==0){
    log_message(((unsigned long)"get_sn_info para is NULL\n") /*=0xa7031*/);
    uVar2=0xffffffff;
  } else {
    volatile uint8_t *puVar3=(volatile uint8_t*)(uintptr_t)*param_3;
    puVar3[0]=0x22;
    puVar3[1]=*(volatile uint8_t*)(param_1+1);
    puVar3[2]=3;
    int uVar1=get_device_serial_buf();
    vdprintf_to_fd(&workspace.payload,0,0x20,((unsigned long)&rodata_a8c37) /*=0xa8c37*/,uVar1);
    uVar1=strlen(&workspace.payload);
    puVar3[3]=(uint8_t)uVar1;
    memcpy((void*)(puVar3+4),&workspace.payload,uVar1);
    *param_4=(char)uVar1+4;
  }
  return uVar2;
}
