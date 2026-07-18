/* Reconstructed FUN_00051870 @ 0x51870  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
/* Adopted stock callees, with reversible firmware back-map:
 * flash_img_init_id        <= FUN_0007f150 @ 0x0007f150
 * flash_img_buffered_write <= FUN_0007f110 @ 0x0007f110
 */
extern int flash_img_init_id(void *, uint8_t);
extern int flash_img_buffered_write(void *, const void *, uint32_t, uint32_t);

int FUN_00051870(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
  int iVar1;
  if (param_1 == 0) {
    iVar1 = flash_img_init_id((void *)0x2000a954UL,
                              *(volatile uint8_t*)0x2000ab7cUL);
    if (iVar1 != 0) {
      return 10;
    }
  }
  iVar1 = flash_img_buffered_write((void *)0x2000a954UL,
                                   (const void *)(uintptr_t)param_2,
                                   param_3, param_4);
  if (iVar1 != 0) {
    iVar1 = 0xc;
  }
  return iVar1;
}
