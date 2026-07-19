#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000235dc @ 0x000235dc
 * public-name: crc32_table_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   crc32_table_init                         <= FUN_000235dc @ 0x000235dc
 * address symbols (name @ address):
 *   g_crc32_table                            @ 0x200075a0
 */
/* Reconstructed FUN_000235dc @ 0x235dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void crc32_table_init(void)
{
  volatile uint32_t *puVar2 = (volatile uint32_t *)((unsigned long)&g_crc32_table) /*=0x200075a0*/;
  unsigned int uVar1 = 0xedb88320UL;
  unsigned int uVar4 = 0;
  do {
    int iVar3 = 8;
    unsigned int uVar5 = uVar4;
    do {
      unsigned int uVar6 = uVar5 & 1;
      uVar5 = uVar5 >> 1;
      if (uVar6 != 0) uVar5 = uVar5 ^ uVar1;
      iVar3 = iVar3 - 1;
    } while (iVar3 != 0);
    uVar4 = uVar4 + 1;
    *puVar2 = uVar5;
    puVar2 = puVar2 + 1;
  } while (uVar4 != 0x100);
}
