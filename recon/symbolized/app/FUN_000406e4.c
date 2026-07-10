#include "g1_app_symbols.h"
/* named: FUN_000406e4 */
/* globals referenced:
//   0x2001cdd3  onboarding_watchdog_active_flag 
*/
/* Reconstructed FUN_000406e4 @ 0x406e4  (parity: 300/300 trials, PROVEN) */

extern int get_device_info(void);
extern void memset_bytes(unsigned int, unsigned int, unsigned int);

unsigned int FUN_000406e4(void)
{
  int iVar1;

  iVar1 = get_device_info();
  memset_bytes(*(unsigned int *)(iVar1 + 0x1014),0,0x21);
  *(volatile unsigned char*)((uintptr_t)&onboarding_watchdog_active_flag) /*=0x2001cdd3*/ = 1;
  return 0;
}

