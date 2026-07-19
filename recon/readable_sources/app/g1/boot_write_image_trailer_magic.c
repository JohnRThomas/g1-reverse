#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_flash_area__param_0319                 [param_0319; library]
 * Raw function identity: 0x00063ff8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00063ff8 @ 0x00063ff8
 * public-name: boot_write_image_trailer_magic
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   boot_write_image_trailer_magic           <= FUN_00063ff8 @ 0x00063ff8
 *   flash_area_write                         <= FUN_0007efaa @ 0x0007efaa
 *   flash_area_erased_val                    <= FUN_0007f012 @ 0x0007f012
 * address symbols (name @ address):
 *   rodata_9907c                             @ 0x0009907c
 */
/* Reconstructed FUN_00063ff8 @ 0x63ff8  (parity: 300/300 trials, PROVEN) */

extern void flash_area_erased_val(void);
extern int flash_area_write(int a, unsigned int b, void *c, int d);

int boot_write_image_trailer_magic(int param_1)
{
  unsigned int local_28[5];
  unsigned int iVar2 = *(volatile unsigned int*)(param_1+8);
  unsigned int i;
  volatile unsigned int *src = (volatile unsigned int*)((unsigned long)&rodata_9907c) /*=0x9907c*/;
  int r;
  flash_area_erased_val();
  for (i = 0; i < 4; i++) {
    local_28[i] = src[i];
  }
  r = flash_area_write(param_1, (iVar2 - 0x10) & 0xfffffff8, local_28, 0x10);
  if (r != 0) r = 1;
  return r;
}
