#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c132 @ 0x0007c132
 * public-name: FUN_0007c132
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   memcmp                                   <= FUN_00086be4 @ 0x00086be4
 */
/* Reconstructed FUN_0007c132 @ 0x7c132  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern int memcmp(int a, void *b, int c);

int FUN_0007c132(unsigned int param_1, unsigned int param_2)
{
  unsigned char buf[8];
  int iVar1;
  int i;
  buf[7] = (unsigned char)(param_2 >> 24);
  for (i = 0; i < 7; i++) buf[i] = 0;
  iVar1 = get_device_info();
  iVar1 = memcmp(iVar1 + 0x1069, buf, 7);
  if (iVar1 != 0) {
    for (i = 0; i < 7; i++) buf[i] = 0xff;
    iVar1 = get_device_info();
    iVar1 = memcmp(iVar1 + 0x1069, buf, 7);
    if (iVar1 != 0) iVar1 = 1;
  }
  return iVar1;
}
