#include "g1_app_symbols.h"
/* named: adjust_owner_prio.isra.0 */
/* Reconstructed adjust_owner_prio.isra.0 @ 0x864b2  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00074060(void);
unsigned int adjust_owner_prio_isra_0(int param_1,int param_2) __asm__("adjust_owner_prio.isra.0");
unsigned int adjust_owner_prio_isra_0(int param_1,int param_2)
{
  if (*(signed char *)(param_1 + 0xe) != param_2) {
    return FUN_00074060();
  }
  return 0;
}

