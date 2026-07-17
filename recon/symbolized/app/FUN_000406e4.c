#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000406e4 @ 0x000406e4
 * public-name: FUN_000406e4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   onboarding_watchdog_active_flag          @ 0x2001cdd3
 */
/* Reconstructed FUN_000406e4 @ 0x406e4  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void memset_bytes(unsigned int, unsigned int, unsigned int);

unsigned int FUN_000406e4(void)
{
  int iVar1;

  iVar1 = get_device_info();
  memset_bytes(*(unsigned int *)(iVar1 + 0x1014),0,0x21);
  *(volatile unsigned char*)((unsigned long)&onboarding_watchdog_active_flag) /*=0x2001cdd3*/ = 1;
  return 0;
}
