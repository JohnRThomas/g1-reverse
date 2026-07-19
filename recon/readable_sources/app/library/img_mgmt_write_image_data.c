#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051870 @ 0x00051870
 * public-name: img_mgmt_write_image_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_write_image_data                <= FUN_00051870 @ 0x00051870
 * address symbols (name @ address):
 *   g_img_mgmt_flash_area                    @ 0x2000a954
 *   g_img_mgmt_active_slot                   @ 0x2000ab7c
 */
/* Reconstructed FUN_00051870 @ 0x51870  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
/* Adopted stock callees, with reversible firmware back-map:
 * flash_img_init_id        <= FUN_0007f150 @ 0x0007f150
 * flash_img_buffered_write <= FUN_0007f110 @ 0x0007f110
 */
extern int flash_img_init_id(void *, uint8_t);
extern int flash_img_buffered_write(void *, const void *, uint32_t, uint32_t);

int img_mgmt_write_image_data(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
  int iVar1;
  if (param_1 == 0) {
    iVar1 = flash_img_init_id((void *)((unsigned long)&g_img_mgmt_flash_area) /*=0x2000a954*/,
                              *(volatile uint8_t*)((unsigned long)&g_img_mgmt_active_slot) /*=0x2000ab7c*/);
    if (iVar1 != 0) {
      return 10;
    }
  }
  iVar1 = flash_img_buffered_write((void *)((unsigned long)&g_img_mgmt_flash_area) /*=0x2000a954*/,
                                   (const void *)(uintptr_t)param_2,
                                   param_3, param_4);
  if (iVar1 != 0) {
    iVar1 = 0xc;
  }
  return iVar1;
}
