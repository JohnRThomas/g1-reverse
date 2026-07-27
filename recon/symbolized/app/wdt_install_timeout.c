#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00063984 @ 0x00063984
 * public-name: wdt_install_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   wdt_install_timeout                      <= FUN_00063984 @ 0x00063984
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   dev_set_threshold_and_arm                <= FUN_00083e70 @ 0x00083e70
 * address symbols (name @ address):
 *   rodata_f66c1                             @ 0x000f66c1
 */
/* Reconstructed FUN_00063984 @ 0x63984  (parity: 300/300 trials, PROVEN) */

extern int dev_set_threshold_and_arm(unsigned int a, int b, unsigned int c, unsigned int d, unsigned int e);
extern int dev_write_reg3(unsigned int, unsigned int, unsigned int, unsigned int);

int wdt_install_timeout(int param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  volatile char *pcVar2;
  volatile unsigned int *puVar3;

  pcVar2 = *(volatile char **)(param_1 + 0x10);
  puVar3 = *(volatile unsigned int **)(param_1 + 4);
  if (*pcVar2 != 0) {
    return -0xc;
  }
  if (*param_2 == 0) {
    iVar1 = dev_set_threshold_and_arm(*puVar3, param_2[1], param_3, 0, param_4);
    if (iVar1 < 0) {
      return iVar1;
    }
    if ((*(volatile unsigned char *)((char*)param_2 + 0xc) & 3) != 3) {
      unsigned char idx = *(volatile unsigned char *)((char*)param_2 + 0xc) & 3;
      iVar1 = dev_write_reg3(*puVar3, 7, 5, *(volatile unsigned char *)(((unsigned long)&rodata_f66c1) /*=0xf66c1*/ + idx));
      if (iVar1 < 0) {
        return iVar1;
      }
      *pcVar2 = 1;
      return 0;
    }
  }
  return -0x16;
}
