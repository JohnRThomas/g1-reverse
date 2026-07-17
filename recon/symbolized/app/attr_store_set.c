#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00030178 @ 0x00030178
 * public-name: attr_store_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_retry_delay                   <= FUN_0003016c @ 0x0003016c
 *   attr_store_set                           <= FUN_00030178 @ 0x00030178
 * address symbols (name @ address):
 *   g_pt_nfc_link_cfg                        @ 0x20007bc0
 */
/* Reconstructed FUN_00030178 @ 0x30178  (parity: 300/300 trials, PROVEN) */

extern void attr_store_retry_delay(int a);
typedef int (*fp_t)(void*,int);

unsigned int attr_store_set(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned char buf[12];
  unsigned char cVar3 = 3;
  int iVar2;

  *(unsigned short*)(buf+0) = (unsigned short)(((param_1 & 0xff) << 8) | ((param_1 >> 8) & 0xff));
  buf[2] = (unsigned char)(param_2 >> 24);
  buf[3] = (unsigned char)(param_2 >> 16);
  *(unsigned short*)(buf+4) = (unsigned short)(((param_2 & 0xff) << 8) | ((param_2 >> 8) & 0xff));
  *(unsigned int*)(buf+8) = param_3;

  do {
    int *piVar1 = *(volatile int **)((unsigned long)&g_pt_nfc_link_cfg) /*=0x20007bc0*/;
    fp_t fn = *(volatile fp_t*)((char*)piVar1 + 4);
    iVar2 = fn(buf, 6);
    if (iVar2 == 0) return 0;
    cVar3 = cVar3 - 1;
    attr_store_retry_delay(1);
  } while (cVar3 != 0);
  return 0xffffffff;
}
