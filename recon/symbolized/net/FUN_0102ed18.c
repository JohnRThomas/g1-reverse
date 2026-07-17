#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102ed18 @ 0x0102ed18
 * public-name: FUN_0102ed18
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ipc_shm_pool_desc_ptr              @ 0x21004b30
 */
/* net-core FUN_0102ed18 @ 0x102ed18  (parity 300 trials PROVEN) */

unsigned int FUN_0102ed18(unsigned int param_1, unsigned int param_2)
{
  volatile unsigned int *p = (volatile unsigned int*)((unsigned long)&g_net_ipc_shm_pool_desc_ptr) /*=0x21004b30*/;
  unsigned int uVar1 = *p;

  if (uVar1 != 0) {
    uVar1 = *(volatile unsigned int*)(uVar1 + 0x78);
    if ((param_1 == 0xffffffea) || ((param_1 <= uVar1 - 0x40) == 0 ? 0 : (param_1 < uVar1))) {
      if (uVar1 <= param_2) {
        uVar1 = 0;
      }
      return uVar1;
    }
    uVar1 = 0;
  }
  return uVar1;
}
