#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004bb64 @ 0x0004bb64
 * public-name: extract_decimal
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   extract_decimal                          <= FUN_0004bb64 @ 0x0004bb64
 * address symbols (name @ address):
 *   rodata_f8a6b                             @ 0x000f8a6b
 */
/* Reconstructed FUN_0004bb64 @ 0x4bb64  (parity: 300/300 trials, PROVEN) */

int extract_decimal(unsigned int *param_1)
{
  int iVar1 = 0;
  unsigned char *pbVar2 = (unsigned char *)*param_1;
  while (1) {
    unsigned char c = *pbVar2;
    unsigned char tbl = *(volatile unsigned char *)(((unsigned long)&rodata_f8a6b) /*=0xf8a6b*/ + c);
    if ((int)((unsigned int)tbl << 0x1d) >= 0) break;
    iVar1 = iVar1*10 + (int)c - 0x30;
    pbVar2 = pbVar2 + 1;
  }
  *param_1 = (unsigned int)pbVar2;
  return iVar1;
}
