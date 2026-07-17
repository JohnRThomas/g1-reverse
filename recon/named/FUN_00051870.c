/* readable reconstruction; identity: FUN_00051870 @ 0x00051870
 * public-name: FUN_00051870
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_img_mgmt_flash_area                    @ 0x2000a954
 *   g_img_mgmt_active_slot                   @ 0x2000ab7c
 */
/* Reconstructed FUN_00051870 @ 0x51870  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0007f150(uint32_t, uint8_t);
extern int FUN_0007f110(uint32_t, uint32_t, uint32_t, uint32_t);

int FUN_00051870(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
  int iVar1;
  if (param_1 == 0) {
    iVar1 = FUN_0007f150(0x2000a954UL, *(volatile uint8_t*)0x2000ab7cUL);
    if (iVar1 != 0) {
      return 10;
    }
  }
  iVar1 = FUN_0007f110(0x2000a954UL, param_2, param_3, param_4);
  if (iVar1 != 0) {
    iVar1 = 0xc;
  }
  return iVar1;
}
