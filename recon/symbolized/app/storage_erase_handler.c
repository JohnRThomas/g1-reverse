#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00052604 @ 0x00052604
 * public-name: storage_erase_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   smp_add_cmd_err                          <= FUN_0005160c @ 0x0005160c
 *   storage_erase_handler                    <= FUN_00052604 @ 0x00052604
 *   nullsub_3                                <= FUN_0007ef7e @ 0x0007ef7e
 *   flash_area_erase                         <= FUN_0007efd4 @ 0x0007efd4
 *   storage_ctx_get_field0c                  <= FUN_0007f00e @ 0x0007f00e
 * address symbols (name @ address):
 *   rodata_88220                             @ 0x00088220
 *   rodata_f289a                             @ 0x000f289a
 *   rodata_f28b4                             @ 0x000f28b4
 *   rodata_f28d4                             @ 0x000f28d4
 */
/* Reconstructed FUN_00052604 @ 0x52604  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void z_log_msg_runtime_create(uint32_t,int,void*,...);
extern int flash_area_open(int, void*);
extern int smp_add_cmd_err(int,int,uint32_t);
extern void nullsub_3(int);
extern int flash_area_erase(int,int,uint32_t,int);
extern unsigned int storage_ctx_get_field0c(char *);

uint32_t storage_erase_handler(int param_1){
  int iVar1;
  uint32_t uVar2;
  int iVar3;
  volatile int local_2c[5];
  volatile uint32_t local_18;
  void * volatile local_14;
  iVar3 = *(int*)(param_1+8);
  iVar1 = flash_area_open(9, (void*)local_2c);
  if (iVar1 < 0){
    uVar2 = 2;
    local_18 = 2;
    local_14 = (void*)((unsigned long)&rodata_f289a) /*=0xf289a*/;
    z_log_msg_runtime_create(((unsigned long)&rodata_88220) /*=0x88220*/, 0x1040, (void*)&local_18, 0);
  } else {
    iVar1 = storage_ctx_get_field0c(local_2c[0]);
    if (iVar1 == 0){
      local_14 = (void*)((unsigned long)&rodata_f28b4) /*=0xf28b4*/;
      local_18 = 2;
      z_log_msg_runtime_create(((unsigned long)&rodata_88220) /*=0x88220*/, 0x1040, (void*)&local_18, 0);
      nullsub_3(local_2c[0]);
      uVar2 = 3;
    } else {
      uVar2 = (uint32_t)flash_area_erase(local_2c[0], 0, *(uint32_t*)(local_2c[0]+8), iVar1);
      if ((int)uVar2 < 0){
        local_14 = (void*)((unsigned long)&rodata_f28d4) /*=0xf28d4*/;
        local_18 = 2;
        z_log_msg_runtime_create(((unsigned long)&rodata_88220) /*=0x88220*/, 0x1040, (void*)&local_18, 0);
        nullsub_3(local_2c[0]);
        uVar2 = 4;
      } else {
        nullsub_3(local_2c[0]);
        if (uVar2 == 0) return 0;
      }
    }
  }
  iVar1 = smp_add_cmd_err(iVar3+4, 0x3f, uVar2 & 0xffff);
  if (iVar1 != 0) return 0;
  return 7;
}
