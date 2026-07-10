#include "g1_app_symbols.h"
/* named: change_work_mode */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x200069fc  device_info                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed change_work_mode_to @ 0x1694c  (parity: 296/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned char byte; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...);
extern int enable_ship_mode(int,...);
extern int global_system_resume(int,...);
extern int debug_print(int,...);
extern int global_ipc_service_send(int,...);
extern int app_msleep_thunk_a(int,...);
extern int memset_bytes(int,...);

void change_work_mode_to(uint param_1){
  volatile char *pcVar1 = (volatile char*)((uintptr_t)&g_change_work_mode_busy) /*=0x2000ff4b*/;
  int *piVar2; int iVar4 = 3000; uint uVar3; int i;
  while ((piVar2 = (int*)((uintptr_t)&device_info) /*=0x200069fc*/, *pcVar1 != 0 && (iVar4 = iVar4 - 1, iVar4 != 0))) {
    app_msleep_thunk_a(1);
  }
  *pcVar1 = 1;
  iVar4 = *piVar2;
  if ((uint)*(volatile byte*)(iVar4 + 1) != param_1) {
    *(volatile char*)(iVar4 + 1) = (char)param_1;
    if (0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
      if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) DEBUG_PRINT("%s(): change_work_mode to %d\n" /*=0x9976b*/,"change_work_mode" /*=0x99bb7*/,param_1 & 0xff);
      else debug_print(0);
    }
    uVar3 = *(volatile byte*)(*piVar2 + 1);
    if (uVar3 < 10) {
      switch (uVar3) {
        case 1: for(i=0;i<12;i++) global_system_resume(0,0); break;
        case 2: for(i=0;i<11;i++) global_system_resume(0,0); break;
        case 7: case 9: for(;;) global_system_resume(0,0);
        default: for(i=0;i<10;i++) global_system_resume(0,0); break;
      }
      *pcVar1 = 0;
      return;
    }
  }
  *pcVar1 = 0;
  return;
}

