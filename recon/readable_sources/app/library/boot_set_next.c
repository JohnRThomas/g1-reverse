#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_flash_area__param_0319                 [param_0319; library]
 * Raw function identity: 0x000641e4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000641e4 @ 0x000641e4
 * public-name: boot_set_next
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   boot_write_image_trailer_magic           <= FUN_00063ff8 @ 0x00063ff8
 *   flash_read_boot_swap_ate                 <= FUN_0006403c @ 0x0006403c
 *   boot_write_swap_info                     <= FUN_000640e8 @ 0x000640e8
 *   boot_set_next                            <= FUN_000641e4 @ 0x000641e4
 *   __assert_func                            <= FUN_00076a94 @ 0x00076a94
 *   flash_area_erase                         <= FUN_0007efd4 @ 0x0007efd4
 *   nvs_flush_close_ate                      <= FUN_00084e58 @ 0x00084e58
 * address symbols (name @ address):
 *   rodata_f68d7                             @ 0x000f68d7
 *   rodata_f692c                             @ 0x000f692c
 *   rodata_f7a30                             @ 0x000f7a30
 */
/* Reconstructed FUN_000641e4 @ 0x641e4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int boot_write_image_trailer_magic(char*);
extern int flash_read_boot_swap_ate(char*, void*);
extern int boot_write_swap_info(char*, uint32_t, int);
extern void __assert_func(uint32_t,int,uint32_t,uint32_t);
extern void flash_area_erase(char*, int, uint32_t);
extern int nvs_flush_close_ate(char*);

int boot_set_next(char *param_1, int param_2, int param_3){
  volatile uint8_t local[12];
  *(char * volatile *)local = param_1;
  *(volatile int*)(local+4) = param_2;
  *(volatile int*)(local+8) = param_3;
  int iVar3 = param_3;
  if (param_2 != 0) iVar3 = param_2;
  int iVar2 = flash_read_boot_swap_ate(param_1, (void*)local);
  if (iVar2 != 0) return iVar2;
  uint32_t uVar4 = local[0];
  if (uVar4 == 2){
    if (param_2 == 0){
      flash_area_erase(param_1, 0, *(uint32_t*)(param_1+8));
      return 3;
    }
  } else {
    if (uVar4 == 3){
      if (param_2 != 0) return 0;
      iVar2 = boot_write_image_trailer_magic(param_1);
      if (iVar2 != 0) return iVar2;
      uint32_t uVar5;
      if (iVar3 == 0){ uVar5 = 2; }
      else {
        iVar3 = nvs_flush_close_ate(param_1);
        uVar5 = 3;
        if (iVar3 != 0) return iVar3;
      }
      char cVar1 = *param_1;
      int bVar6 = 0;
      if (cVar1 != 4 && cVar1 != 2){
        if (cVar1 == 1) bVar6 = 1;
        else bVar6 = (cVar1 == 8);
      }
      return boot_write_swap_info(param_1, uVar5, bVar6);
    }
    if (uVar4 == 1){
      if (param_2 == 0) return 0;
      if (local[3] != 3) return 0;
      return nvs_flush_close_ate(param_1);
    }
    __assert_func(((unsigned long)&rodata_f68d7) /*=0xf68d7*/, 0x22e, ((unsigned long)&rodata_f692c) /*=0xf692c*/, ((unsigned long)&rodata_f7a30) /*=0xf7a30*/);
  }
  return 4;
}
