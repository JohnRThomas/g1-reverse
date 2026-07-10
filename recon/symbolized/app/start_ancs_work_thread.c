#include "g1_app_symbols.h"
/* named: start_ancs_work_thread */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed start_ancs_work_thread @ 0x198cc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int,...);
extern int get_device_info(void);
extern int debug_print(void);
extern int is_battery_critical(void);
extern int FUN_00071eac(unsigned,unsigned,int,unsigned,unsigned,int,int,int,int);
void start_ancs_work_thread(unsigned param_1){
  char* pcVar1; int iVar2;
  pcVar1 = (char*)get_device_info();
  if((*(unsigned char*)pcVar1==2) && (iVar2=is_battery_critical(), iVar2!=1)){
    FUN_00071eac(((uintptr_t)&g_ancs_work_thread) /*=0x20003c50*/, ((uintptr_t)&g_ancs_work_thread_stack) /*=0x2001d568*/, 0x1400, ((uintptr_t)&tbl_19704) /*=0x19719*/, param_1, 0,0,0xfffffff5,0);
    if(2 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/){
      if(*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ != 0){
        debug_print();
        return;
      }
      DEBUG_PRINT("%s(): exit\n\n" /*=0x9af2e*/, "start_ancs_work_thread" /*=0x9b0f1*/);
      return;
    }
  }
  return;
}

