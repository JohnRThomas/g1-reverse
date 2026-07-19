#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d248 @ 0x0007d248
 * public-name: check_dashboard_device_status_range
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   check_dashboard_device_status_range      <= FUN_0007d248 @ 0x0007d248
 */
/* Reconstructed FUN_0007d248 @ 0x7d248  (parity: 300/300 trials, PROVEN) */

extern char *get_device_info(void);

int check_dashboard_device_status_range(void)
{
  char *iVar1;
  int uVar2;
  iVar1 = get_device_info();
  if ((unsigned char)iVar1[0xfc0] < 0x15) {
    uVar2 = 0;
  } else {
    iVar1 = get_device_info();
    if ((unsigned char)iVar1[0xfc1] < 0x15) {
      iVar1 = get_device_info();
      uVar2 = -1;
      if (2 < (unsigned char)iVar1[0xfc1]) uVar2 = 0;
    } else {
      uVar2 = -1;
    }
  }
  return uVar2;
}
