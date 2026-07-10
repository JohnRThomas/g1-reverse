#include "g1_app_symbols.h"
/* named: onboarding_retry_watchdog_update */
/* globals referenced:
//   0x200034f5  onboarding_last_step_cache   
//   0x2001cdd1  onboarding_retry_counter     
//   0x2001cdd2  onboarding_attempt_counter   
//   0x2001cdd3  onboarding_watchdog_active_flag 
*/
/* Reconstructed onboarding_retry_watchdog_update @ 0x40708  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
void onboarding_retry_watchdog_update(void){
  char cVar1=*(volatile signed char*)((uintptr_t)&onboarding_last_step_cache) /*=0x200034f5*/;
  int iVar3;
  iVar3=get_device_info();
  if(((int)cVar1!=(unsigned int)*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)) ||
     (((iVar3=get_device_info(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=5)&&
       (iVar3=get_device_info(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=0x13))&&
      (iVar3=get_device_info(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=0x14)&&
      (iVar3=get_device_info(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=0x15))){
    *(volatile unsigned char*)((uintptr_t)&onboarding_attempt_counter) /*=0x2001cdd2*/=0;
    *(volatile unsigned char*)((uintptr_t)&onboarding_retry_counter) /*=0x2001cdd1*/=0;
  }
  *(volatile unsigned char*)((uintptr_t)&onboarding_watchdog_active_flag) /*=0x2001cdd3*/=1;
  iVar3=get_device_info();
  *(volatile char*)((uintptr_t)&onboarding_last_step_cache) /*=0x200034f5*/=*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2);
}

