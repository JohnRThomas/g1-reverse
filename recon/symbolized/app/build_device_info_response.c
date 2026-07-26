#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00031bd8 @ 0x00031bd8
 * public-name: build_device_info_response
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   build_device_info_response               <= FUN_00031bd8 @ 0x00031bd8
 * address symbols (name @ address):
 *   rodata_a6603                             @ 0x000a6603   [INLINED -- G6 literal batch]
 *   rodata_a704b                             @ 0x000a704b   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00031bd8 @ 0x31bd8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../headers/g1_log.h"
extern int get_device_info(void);
unsigned build_device_info_response(int param_1, unsigned param_2, uint32_t *param_3, uint8_t *param_4){
  int iVar1; uint16_t uVar2; uint8_t *puVar3;
  log_message(((unsigned long)"join in get_mac_info\n") /*=0xa704b*/);
  if(param_3==0 || param_4==0){ log_message(((unsigned long)"get_mac_info para is NULL\n") /*=0xa6603*/); return 0xffffffff; }
  puVar3=(uint8_t*)*param_3;
  *puVar3=5; puVar3[1]=1; puVar3[2]=3; puVar3[3]=6;
  if(*(char*)(param_1+2)==1){ iVar1=get_device_info(); *(uint32_t*)(puVar3+4)=*(uint32_t*)(iVar1+0xfda); uVar2=*(uint16_t*)(iVar1+0xfde); }
  else { if(*(char*)(param_1+2)!=0) goto LAB; iVar1=get_device_info(); *(uint32_t*)(puVar3+4)=*(uint32_t*)(iVar1+0xfe0); uVar2=*(uint16_t*)(iVar1+0xfe4); }
  *(uint16_t*)(puVar3+8)=uVar2;
  LAB: *param_4=10; return 0;
}
