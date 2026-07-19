#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cf70 @ 0x0007cf70
 * public-name: wait_for_attr_0x4410_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_retry_delay                   <= FUN_0003016c @ 0x0003016c
 *   attr_store_get                           <= FUN_000302f8 @ 0x000302f8
 *   wait_for_attr_0x4410_set                 <= FUN_0007cf70 @ 0x0007cf70
 */
/* Reconstructed FUN_0007cf70 @ 0x7cf70  (parity: 300/300 trials, PROVEN) */

extern int attr_store_get(int a, int *b);
extern void attr_store_retry_delay(int a);
int wait_for_attr_0x4410_set(void)
{
  int iVar1;
  unsigned char cVar2 = 0x65;
  int local_c = 0;
  while (1) {
    iVar1 = attr_store_get(0x4410, &local_c);
    if (iVar1 < 0) return -1;
    if ((local_c & 1) != 0) break;
    cVar2 = cVar2 - 1;
    attr_store_retry_delay(1);
    if (cVar2 == 0) return -2;
  }
  return 0;
}
