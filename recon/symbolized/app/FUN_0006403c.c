#include "g1_app_symbols.h"
/* named: FUN_0006403c */
/* Reconstructed FUN_0006403c @ 0x6403c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int flash_area_read(int, int, void*, ...);
extern int flash_region_is_erased(int, void*, int);
extern int memcmp(void*, uint32_t, int);
extern uint32_t flash_calc_prev_ate_offset(int);
extern int flash_write_byte_and_verify(int, void*, int);
extern uint32_t flash_verify_write_at_current_offset(int, void*);

uint32_t FUN_0006403c(int param_1, uint8_t *param_2){
  int iVar1;
  uint32_t uVar2;
  uint8_t uVar3;
  volatile uint8_t local_21;
  uint8_t auStack_20[20];
  iVar1 = flash_area_read(param_1, *(int*)(param_1+8) - 0x10, auStack_20);
  if (iVar1 >= 0){
    iVar1 = flash_region_is_erased(param_1, auStack_20, 0x10);
    if (iVar1 == 0){
      iVar1 = memcmp(auStack_20, ((uintptr_t)&tbl_98fbc) /*=0x9907c*/, 0x10);
      uVar3 = (iVar1 == 0) ? 1 : 2;
    } else {
      uVar3 = 3;
    }
    *param_2 = uVar3;
    uVar2 = flash_calc_prev_ate_offset(param_1);
    iVar1 = flash_area_read(param_1, (int)uVar2, (void*)&local_21, 1);
    if (iVar1 >= 0){
      param_2[1] = local_21 & 0xf;
      param_2[4] = local_21 >> 4;
      iVar1 = flash_region_is_erased(param_1, (void*)&local_21, 1);
      if (iVar1 != 0 || param_2[1] > 4){
        param_2[1] = 1;
        param_2[4] = 0;
      }
      iVar1 = flash_write_byte_and_verify(param_1, param_2 + 2, ((*(int*)(param_1+8) - 0x18) & 0xfffffff8) - 8);
      if (iVar1 == 0){
        uVar2 = flash_verify_write_at_current_offset(param_1, param_2 + 3);
        return uVar2;
      }
    }
  }
  return 1;
}

