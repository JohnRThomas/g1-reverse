#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004790c @ 0x0004790c
 * public-name: expand_bytes_via_lut32
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   expand_bytes_via_lut32                   <= FUN_0004790c @ 0x0004790c
 * address symbols (name @ address):
 *   rodata_d753a                             @ 0x000d753a
 */
/* Reconstructed FUN_0004790c @ 0x4790c  (parity: 300/300 trials, PROVEN) */

void expand_bytes_via_lut32(int param_1,int param_2,int param_3)
{
  unsigned int *base = (unsigned int *)((unsigned long)&rodata_d753a) /*=0xd753a*/;
  int iVar2;
  unsigned char b;
  for (iVar2 = 0; iVar2 < param_2; iVar2 = iVar2 + 1) {
    b = *(volatile unsigned char *)(param_1 + iVar2);
    *(volatile unsigned int *)(param_3 + iVar2 * 4) = *(volatile unsigned int *)((char*)base + b * 4);
  }
}
