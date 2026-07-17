#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000429f8 @ 0x000429f8
 * public-name: FUN_000429f8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 * address symbols (name @ address):
 *   onboarding_secondary_reset_flag          @ 0x2001cdce
 *   onboarding_retry_counter                 @ 0x2001cdd1
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
    ((*(volatile char*)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/==2) &&
     (iVar1=get_device_info(), *(char*)(*(int*)(iVar1+0x1014)+3)==1))){
    *(volatile char*)((unsigned long)&onboarding_retry_counter) /*=0x2001cdd1*/=1;
  }
  return;
}
