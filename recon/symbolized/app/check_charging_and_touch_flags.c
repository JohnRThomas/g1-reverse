#include "g1_app_symbols.h"
/* named: check_charging_and_touch_flags */
/* globals referenced:
//   0x20018d91  g_box_lid_or_charge_state    
*/
/* Reconstructed check_charging_and_touch_flags @ 0x26c28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
extern int FUN_00019b2c(void);
int check_charging_and_touch_flags(void){
  int iVar2 = get_device_info();
  int iVar3 = get_device_info();
  int cVar1 = FUN_00019b2c();
  if(*(volatile uint8_t*)((uintptr_t)&g_box_lid_or_charge_state) /*=0x20018d91*/ == 3 && (uint8_t)cVar1 != 0){
    int pcVar4 = get_device_info();
    int v = *(volatile uint8_t*)pcVar4;
    uint8_t r3b = *(volatile uint8_t*)(iVar3+0x6de);
    if(v != 1){
      *(volatile uint8_t*)(iVar3+0x6de) = r3b | 1;
    } else {
      if(r3b & 1){
        *(volatile uint8_t*)(iVar2+0xe4) = *(volatile uint8_t*)(iVar2+0xe4) | 3;
      }
    }
  }
  return (*(volatile uint8_t*)(iVar2+0xe4) & 3) == 3;
}

