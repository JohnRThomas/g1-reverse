#include "g1_app_symbols.h"
/* named: display_powerEvent */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed display_powerEvent @ 0x49a28  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>

extern int debug_print(void);
extern int k_msgq_put(void*, void*, int, int);
extern void memset_bytes(void*, int, int);
extern int DEBUG_PRINT(int, ...);

int display_powerEvent(int param_1)
{
  int iVar1;
  int uVar2;
  unsigned char local_28[28];

  memset_bytes(local_28, 0, 0x18);
  if (param_1 == 1) {
    local_28[0] = 7;
  } else {
    local_28[0] = 8;
  }
  iVar1 = k_msgq_put((void*)((uintptr_t)&g_display_msgq) /*=0x200038c4*/, local_28, 0, 0);
  if (iVar1 == 0) {
    uVar2 = 0;
    if (*(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
      if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT("%s(): send display power event command , low_power_en = %d\n" /*=0xf00ea*/, "display_powerEvent" /*=0xf0126*/, param_1);
      } else {
        debug_print();
      }
    }
  } else {
    DEBUG_PRINT("message queue send failed %s\r\n" /*=0xef058*/, "display_powerEvent" /*=0xf0126*/);
    uVar2 = -1;
  }
  return uVar2;
}

