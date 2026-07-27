#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026c28 @ 0x00026c28
 * public-name: check_charging_and_touch_flags
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   get_ancs_conn_handle                     <= FUN_00019b2c @ 0x00019b2c
 *   check_charging_and_touch_flags           <= FUN_00026c28 @ 0x00026c28
 * address symbols (name @ address):
 *   g_box_lid_or_charge_state                @ 0x20018d91
 */
/* Reconstructed FUN_00026c28 @ 0x26c28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_device_info(void);
extern unsigned int get_ancs_conn_handle(void);
int check_charging_and_touch_flags(void){
  int iVar2 = get_device_info();
  int iVar3 = get_device_info();
  int cVar1 = get_ancs_conn_handle();
  if(*(volatile uint8_t*)((unsigned long)&g_box_lid_or_charge_state) /*=0x20018d91*/ == 3 && (uint8_t)cVar1 != 0){
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
