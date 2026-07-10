/* Reconstructed display_powerEvent @ 0x49a28  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>

extern int debug_print(void);
extern int FUN_000720d0(void*, void*, int, int);
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
  iVar1 = FUN_000720d0((void*)0x200038c4UL, local_28, 0, 0);
  if (iVar1 == 0) {
    uVar2 = 0;
    if (*(int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */ > 2) {
      if (*(int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
        DEBUG_PRINT(0xf00ea, 0xf0126, param_1);
      } else {
        debug_print();
      }
    }
  } else {
    DEBUG_PRINT(0xef058, 0xf0126);
    uVar2 = -1;
  }
  return uVar2;
}

