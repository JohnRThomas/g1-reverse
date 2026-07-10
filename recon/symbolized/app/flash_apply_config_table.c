#include "g1_app_symbols.h"
/* named: flash_apply_config_table */
/* Reconstructed flash_apply_config_table @ 0x30224  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int attr_store_set(int,...);
int flash_apply_config_table(void){
  volatile uint32_t *puVar1 = (volatile uint32_t*)((uintptr_t)&g_pt_nfc_link_attr_0x4414_cache) /*=0x20007bc4*/;
  volatile uint32_t *puVar2 = (volatile uint32_t*)((uintptr_t)&tbl_8a0a8) /*=0x8a0a8*/;
  int iVar3 = 0;
  do {
    uint32_t v0 = puVar2[0];
    uint32_t v1 = puVar2[1];
    if(v0 == 0x4414){
      *puVar1 = v1;
    } else {
      attr_store_set(v0 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/);
    }
    iVar3 += 2;
    puVar2 += 2;
  } while(iVar3 != 0x58);
  iVar3 = attr_store_set(0x4408, 1);
  if(iVar3 != 0){
    return -1;
  }
  *(volatile uint32_t*)((uintptr_t)&g_pt_nfc_link_ready_flag) /*=0x20007bc8*/ = 1;
  iVar3 = attr_store_set(0x4414, (int)*puVar1);
  return (iVar3 != 0) ? -1 : 0;
}

