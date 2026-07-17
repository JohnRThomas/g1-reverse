/* readable reconstruction; identity: FUN_00040708 @ 0x00040708
 * public-name: onboarding_retry_watchdog_update
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   onboarding_retry_watchdog_update         <= FUN_00040708 @ 0x00040708
 * address symbols (name @ address):
 *   onboarding_last_step_cache               @ 0x200034f5
 *   onboarding_retry_counter                 @ 0x2001cdd1
 *   onboarding_attempt_counter               @ 0x2001cdd2
 *   onboarding_watchdog_active_flag          @ 0x2001cdd3
 */
/* Reconstructed FUN_00040708 @ 0x40708  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
void onboarding_retry_watchdog_update(void){
  char cVar1=*(volatile signed char*)0x200034f5UL;
  int iVar3;
  iVar3=get_device_info();
  if(((int)cVar1!=(unsigned int)*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)) ||
     (((iVar3=get_device_info(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=5)&&
       (iVar3=get_device_info(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=0x13))&&
      (iVar3=get_device_info(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=0x14)&&
      (iVar3=get_device_info(),*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2)!=0x15))){
    *(volatile unsigned char*)0x2001cdd2UL=0;
    *(volatile unsigned char*)0x2001cdd1UL=0;
  }
  *(volatile unsigned char*)0x2001cdd3UL=1;
  iVar3=get_device_info();
  *(volatile char*)0x200034f5UL=*(volatile unsigned char*)(*(volatile int*)(iVar3+0x1014)+2);
}
