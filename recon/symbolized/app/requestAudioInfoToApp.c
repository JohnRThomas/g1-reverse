#include "g1_app_symbols.h"
/* named: requestAudioInfoToApp */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x2000392c  g_dashboard_response_msgq    
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed requestAudioInfoToApp @ 0x48840  (parity: 300/300 trials, PROVEN) */

extern void debug_print(void);
extern int k_msgq_put(void*, void*, int, int);
extern void memset_bytes(void*, int, int);
extern int DEBUG_PRINT(int, ...);

int requestAudioInfoToApp(unsigned char param_1)
{
  int iVar1;
  int uVar2;
  unsigned char buf[24];

  memset_bytes(&buf[1], 0, 0x17);
  buf[0] = 3;
  *(unsigned short*)&buf[2] = 1;
  buf[4] = param_1;
  iVar1 = k_msgq_put((void*)((uintptr_t)&g_dashboard_response_msgq) /*=0x2000392c*/, buf, 0, 0);
  if (iVar1 == 0) {
    uVar2 = 0;
    if (*(int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
      if (*(int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
        DEBUG_PRINT("%s(): requestAudioInfoToApp ...\n" /*=0xef4d9*/, "requestAudioInfoToApp" /*=0xef707*/);
      } else {
        debug_print();
      }
    }
  } else {
    DEBUG_PRINT("message queue send failed %s\r\n" /*=0xef058*/, "requestAudioInfoToApp" /*=0xef707*/);
    uVar2 = -1;
  }
  return uVar2;
}

