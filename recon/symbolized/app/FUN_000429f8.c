#include "g1_app_symbols.h"
/* named: FUN_000429f8 */
/* globals referenced:
//   0x2001cdce  onboarding_secondary_reset_flag 
//   0x2001cdd1  onboarding_retry_counter     
*/
/* Reconstructed FUN_000429f8 @ 0x429f8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_device_info(void);
void FUN_000429f8(void){
  int iVar1;
  iVar1=get_device_info();
  if(((((*(char*)(*(int*)(iVar1+0x1014)+2)==5) ||
       (iVar1=get_device_info(), *(char*)(*(int*)(iVar1+0x1014)+2)==0x13)) ||
      (iVar1=get_device_info(), *(char*)(*(int*)(iVar1+0x1014)+2)==0x14)) ||
     (iVar1=get_device_info(), *(char*)(*(int*)(iVar1+0x1014)+2)==0x15)) &&
    ((*(volatile char*)((uintptr_t)&onboarding_secondary_reset_flag) /*=0x2001cdce*/==2) &&
     (iVar1=get_device_info(), *(char*)(*(int*)(iVar1+0x1014)+3)==1))){
    *(volatile char*)((uintptr_t)&onboarding_retry_counter) /*=0x2001cdd1*/=1;
  }
  return;
}

